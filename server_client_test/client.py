import sys
import subprocess

def cli_http():
    print("zany ary ny http!")


def cli_stdio():
    p = subprocess.Popen(["python", "server_stdio.py"],
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         text=True,)
    while True:
        try:
            print("\r[C]: ", end="")
            msg = input()
            p.stdin.write(msg + "\n")
            p.stdin.flush()
        except (EOFError, KeyboardInterrupt):
            msg = "STOP"
        if msg == "STOP":
            p.terminate()
            try:
                p.wait(timeout=5)
            except subprocess.TimeoutExpired:
                p.kill()
                p.wait()
            break
        answer = p.stdout.readline()
        print(f"\r[S]: {answer.rstrip()}")


if __name__ == "__main__":
    if not len(sys.argv) == 2:
        print("ERROR!")
    else:
        if sys.argv[1] == 'http':
            cli_http()
        elif sys.argv[1] == 'stdio':
            cli_stdio()
        else:
            print("ERR")
