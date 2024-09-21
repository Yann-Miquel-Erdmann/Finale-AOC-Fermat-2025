import appscript
import sys
import time
import os

if len(sys.argv) != 2:
    print("Argument required\n")
    print(sys.argv)
    exit(0)

s = os.getcwd().replace(" ", "\\ ")

print(os.getcwd())
appscript.app('Terminal').do_script(f'cd {s} && python3 {sys.argv[1]}').activate()
