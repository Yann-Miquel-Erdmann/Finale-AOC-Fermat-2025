import appscript
import sys
import time
import os

if len(sys.argv) != 2 and len(sys.argv) != 3:
    print("Argument required\n")
    print(sys.argv)
    exit(1)

s = os.getcwd().replace(" ", "\\ ")

if len(sys.argv) == 3 and sys.argv[2] == "exit":
    appscript.app('Terminal').do_script(f'cd {s} && python3 {sys.argv[1]} && osascript -e \'tell app "Xcode" to activate\' && exit').activate()
else:
    appscript.app('Terminal').do_script(f'cd {s} && python3 {sys.argv[1]} && osascript -e \'tell app "Xcode" to activate\'').activate()

