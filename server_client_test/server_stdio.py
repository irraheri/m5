import time
import sys

if __name__ == "__main__":
    for line in sys.stdin:          # bloque jusqu'à recevoir une ligne
        msg = line.rstrip("\n")
        if msg == "STOP":
            break
        print(f"received '{msg}' from client", flush=True)
