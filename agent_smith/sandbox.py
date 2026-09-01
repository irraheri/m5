from typing import Any, List, Literal
import resource
import signal
from types import FrameType
from pydantic import BaseModel, Field
import json
import argparse


class SecurityError(Exception):
    pass


class SpecificSandboxError(Exception):
    pass


class TimeOut(Exception):
    pass


class SandboxConfig(BaseModel):
    """Sandbox configuration for student solutions.
    Uses allowlist approach: only imports in authorized_imports are allowed.
    Everything else is blocked by default.
    """
    authorized_imports: List[str] = Field(default_factory=lambda: [
        "math", "math.*", "collections", "collections.*", "itertools", "re",
        "json", "typing", "typing.*", "functools", "operator", "heapq",
        "bisect", "copy", "string", "random", "datetime", "datetime.*",
        "array", "cmath",])
    allowed_directories: List[str] = Field(default_factory=lambda: [
        "/testbed", "/tmp/agent"
    ])
    max_execution_time_seconds: int = Field(ge=10, default=15)
    max_memory_mb: int = Field(ge=64, default=512)


class SandboxConfiguration:
    def __init__(self, s_conf: SandboxConfig) -> None:
        self.all_functions = {
                    'print': print,
                    'len': len,
                    'range': range,
                    'sum': sum,
                    'max': max,
                    'min': min,
                    'sorted': sorted,
                    'type': type,
                    'str': str,
                    'int': int,
                    'float': float,
                    'bool': bool,
                    'dict': dict,
                    'tuple': tuple,
                    'set': set,
                    'list': list,
                    '__import__': __import__,
                    '__build_class__': __build_class__,
                    '__name__': '__main__',
                    '__qualname__': '',
                    '__module__': '__main__',
                    'Exception': Exception
        }
        self.authorized_import = ['__builtins__']
        self.authorized_import.extend(s_conf.authorized_imports)
        next_modules = []
        decompressed_modules = []
        for module in self.authorized_import:
            if module.endswith('.*'):
                mod = __import__(module[:-2])
                modules = [a for a in dir(mod) if not a.startswith('_')]
                next_modules.extend(modules)
                decompressed_modules.append(module)
        for module in next_modules:
            self.authorized_import.append(module)
        for module in decompressed_modules:
            self.authorized_import.remove(module)
        self.max_execution_time_seconds = s_conf.max_execution_time_seconds
        self.max_memory_mb = s_conf.max_memory_mb
        self.authorized_path = s_conf.allowed_directories


class SandboxSample:
    def __init__(self, sandbox_configuration: SandboxConfiguration) -> None:
        self.sandbox_configuration = sandbox_configuration
        self.sandbox_configuration.all_functions.update({
            "final_answer": self.final_answer})
        self.property: dict[str, Any] = {
            '__builtins__': sandbox_configuration.all_functions}
        self.code: list[str] = []
        self.input_sign = ">>> "
        self.decal_sign = "... "
        self.level = 0
        self.construct = False
        self.inrun = True
        self.result: str = "None"
        signal.signal(signal.SIGALRM, self.signal_end)

    def interact(self, prompt: str) -> None:
        if self.level == 100:
            self.level = 0
            self.interact("EOF")
            return
        if '__init__' in prompt or '__doc__' in prompt:
            self.construct = True
        if '__' in prompt:
            if not self.construct:
                raise SecurityError(
                    "For secutity reason, don't use '__' in the sandbox!"
                    " Except for a statement using '__init__, __doc__,' "
                    "Please instead use f'{'_'*2}' if necessary")
            else:
                self.construct = False
                if '__' in prompt.replace('__init__', ''):
                    if '__' in prompt.replace('__doc__', ''):
                        raise SecurityError(
                            "For secutity reason, don't use '__' in the "
                            "sandbox! Except for a statement using '__init__,"
                            " __doc__', "
                            "Please instead use f'{'_'*2}' if necessary")
        if 'import' in prompt:
            old = self.property.copy()
            if ';' in prompt:
                raise SecurityError("To avoid any security flaw, never write "
                                    "';' and 'import' on the same line.")
            try:
                exec(prompt, self.property)
            except IndentationError:
                raise SpecificSandboxError("Importing outside the main "
                                           "context is not good practice"
                                           " and is not allowed in the "
                                           "sandbox.")
            new_imported: set[str] = set(self.property.keys()) - set(
                old.keys())
            for module in new_imported:
                if module not in self.sandbox_configuration.authorized_import:
                    self.property.pop(module)
                    print(f"You can't use {module} in this sandbox!")
                    print("Please note that using the word 'import' may "
                          "cause this message to be displayed "
                          "indefinitely.")
        else:
            if prompt.strip() == 'EOF':
                self.level = 0
            if not prompt.strip():
                self.level -= 1
                if self.level < 0:
                    self.level = 0

            continuation_chars = ('(', '{', '[')
            if ((prompt.strip().endswith(':')
                    or self.level != 0 or any([
                        i in prompt for i in continuation_chars]))
                    and prompt.strip() != 'EOF'):
                if prompt.strip().endswith(':') or any([
                        i in prompt for i in continuation_chars]):
                    self.level += 1
                self.code.append(prompt)
                self.interact(input(self.decal_sign))
            else:
                if self.code and self.level == 0:
                    exec('\n'.join(self.code), self.property)
                    self.code = []
                if prompt.strip() != "EOF":
                    exec(prompt, self.property)

    @staticmethod
    def set_memory_limit(max_memory_mb: int = 512) -> None:
        max_memory_bytes = max_memory_mb * 1024 * 1024
        resource.setrlimit(
            resource.RLIMIT_AS, (max_memory_bytes, max_memory_bytes))

    def use_sandbox(self) -> None:
        self.set_memory_limit(self.sandbox_configuration.max_memory_mb)
        signal.alarm(self.sandbox_configuration.max_execution_time_seconds)
        while True:
            try:
                prompt = input(self.input_sign)
            except TimeOut:
                print('\n',
                      self.sandbox_configuration.max_execution_time_seconds,
                      " seconds max time exceeded (sandbox timeout)", sep='')
                break
            try:
                if prompt == "EOF":
                    break
                self.interact(prompt)
            except TimeOut:
                print(self.sandbox_configuration.max_execution_time_seconds,
                      "max time exceeded (sandbox timeout)")
                break

    def signal_end(self, signum: int, frame: FrameType | None) -> None:
        raise TimeOut("Time is up, max time is",
                      self.sandbox_configuration.max_execution_time_seconds)

    def final_answer(self, result: str) -> None:
        self.result = result
        self.inrun = False


class McpServerConfig(BaseModel):
    bench: Literal['mbpp', 'swebench'] = Field(...)
    connection: Literal['stdio', 'http'] = Field(...)
    arg: str = Field(..., description="eather http_url or stdio intraserver "
                     "tool (python mcp_tools_mbpp.py)")


class Sandbox:
    def __init__(self, config_name: str,
                 mcp_server: McpServerConfig | None = None) -> None:
        try:
            with open(config_name) as f:
                config = json.load(f)
                sandbox_config = SandboxConfig(**config)
        except Exception:
            if config_name != "default":
                print("ERROR WHILE LOADING sandbox_template.json,"
                      " using default")
            sandbox_config = SandboxConfig()
        self.config = SandboxConfiguration(sandbox_config)
        self.mcp_server = mcp_server
        self._update_config()

    def function1(self) -> None:
        if self.mcp_server:
            print(f"using _function1 in {self.mcp_server.bench}, "
                  f"{self.mcp_server.connection} mode,"
                  f" args: {self.mcp_server.arg}")
        else:
            print("calling this function needs a loaded mcp-server")

    def function2(self) -> None:
        if self.mcp_server:
            print(f"using _function2 in {self.mcp_server.bench}, "
                  f"{self.mcp_server.connection} mode,"
                  f" args: {self.mcp_server.arg}")
        else:
            print("calling this function needs a loaded mcp-server")

    def _update_config(self) -> None:
        all_func = [self.function1, self.function2]
        for func in all_func:
            self.config.all_functions.update({func.__name__: func})

    def run_sample(self) -> None:
        sample = SandboxSample(self.config)
        sample.use_sandbox()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='uv run sandbox'
                                     ' --mcp-stdio "python "'
                                     'mcp_tools_mbpp.py" '
                                     'sandbox_template.json or same')
    parser.add_argument("sandbox_template", nargs="?", default="default")
    parser.add_argument("--mcp-stdio", default=None)
    parser.add_argument("--mcp-server", default=None)
    args = parser.parse_args()
    mcp_conf: McpServerConfig | None = None

    if args.mcp_stdio:
        mcp_conf = McpServerConfig(**{
            'bench': 'swebench' if 'swebench' in args.mcp_stdio else 'mbpp',
            'connection': 'stdio', 'arg': args.mcp_stdio})
    elif args.mcp_server:
        mcp_conf = McpServerConfig(**{
            'bench': 'swebench' if 'swebench' in args.mcp_server else 'mbpp',
            'connection': 'http', 'arg': args.mcp_server})
    else:
        pass

    sandbox = Sandbox(args.sandbox_template, mcp_conf)
    try:
        sandbox.run_sample()
    except EOFError:
        print("\r=== SOFT END OF SANDBOX PROGRAM (after Ctrl+D) ===")
    except KeyboardInterrupt:
        print("\r=== SOFT END OF SANDBOX PROGRAM (after Ctrl+C) ===")
    except Exception as e:
        print(f"Error occured! {e}")
