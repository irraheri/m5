from typing import Any
import resource
import signal
from types import FrameType


class SecurityError(Exception):
    pass


class SpecificSandboxError(Exception):
    pass


class TimeOut(Exception):
    pass


class SandboxConfiguration:
    def __init__(self) -> None:
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
                    '__import__': __import__,
                    '__build_class__': __build_class__,
                    '__name__': '__main__',
                    '__qualname__': '',
                    '__module__': '__main__'
        }
        self.authorized_import = ['__builtins__']  # key 1
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
        self.max_execution_time_seconds = 230  # key 2
        self.max_memory_mb = 512  # key 3
        self.authorized_path = []  # key 4


class Sandbox:
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
        self.result: None | str = None

        signal.signal(signal.SIGALRM, self.signal_end)
        signal.alarm(self.sandbox_configuration.max_execution_time_seconds)

    def interact(self, prompt: str) -> None:
        if self.level == 100:
            self.level = 0
            self.interact("EOF")
            return
        if '__init__' in prompt:
            self.construct = True
        if '__' in prompt:
            if not self.construct:
                raise SecurityError(
                    "For secutity reason, don't use '__' in the sandbox!"
                    " Except for a statement using '__init__'")
            else:
                self.construct = False
                if '__' in prompt.replace('__init__', ''):
                    raise SecurityError(
                        "For secutity reason, don't use '__' in the "
                        "sandbox! Except for a statement using '__init__'")
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
                    print("Please note that using the word 'import' will "
                          "cause the above message to be displayed "
                          "indefinitely.")
        else:
            if prompt.strip() == 'EOF':
                self.level = 0
            if not prompt.strip():
                self.level -= 1
                if self.level < 0:
                    self.level = 0

            if ((prompt.endswith(':') or self.level != 0)
                    and prompt != 'EOF'):
                if prompt.endswith(':'):
                    self.level += 1
                self.code.append(prompt)
                self.interact(input(self.decal_sign))
            else:
                if self.code and self.level == 0:
                    exec('\n'.join(self.code), self.property)
                    self.code = []
                if prompt != "EOF":
                    exec(prompt, self.property)

    @staticmethod
    def set_memory_limit(max_memory_mb: int = 512) -> None:
        max_memory_bytes = max_memory_mb * 1024 * 1024
        resource.setrlimit(
            resource.RLIMIT_AS, (max_memory_bytes, max_memory_bytes))
        resource.setrlimit(
            resource.RLIMIT_DATA, (max_memory_bytes, max_memory_bytes))
        resource.setrlimit(
            resource.RLIMIT_STACK, (max_memory_bytes, max_memory_bytes))

    def use_sandbox(self) -> None:
        self.set_memory_limit(self.sandbox_configuration.max_memory_mb)
        while True:
            try:
                prompt = input(self.input_sign)
            except TimeOut:
                print('\n',
                      self.sandbox_configuration.max_execution_time_seconds,
                      " seconds max time exceeded", sep='')
                break
            try:
                if prompt == "EOF":
                    break
                self.interact(prompt)
            except TimeOut:
                print(self.sandbox_configuration.max_execution_time_seconds,
                      "max time exceeded")
                break

    def final_answer(self, result: str) -> None:
        self.result = result
        self.inrun = False

    @staticmethod
    def signal_end(signum: int, frame: FrameType | None) -> None:
        raise TimeOut("TOO MUCH")


# CONFIGS IMPORT


if __name__ == "__main__":
    sandbox_config = SandboxConfiguration()
    sandbox = Sandbox(sandbox_config)
    try:
        sandbox.use_sandbox()
    except EOFError:
        print("\r=== SOFT END OF SANDBOX PROGRAM (after Ctrl+D) ===")
    except KeyboardInterrupt:
        print("\r=== SOFT END OF SANDBOX PROGRAM (after Ctrl+C) ===")
    except Exception as e:
        print(f"Error occured! {e}")
