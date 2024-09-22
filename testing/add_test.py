import json
import subprocess
import platform
import sys
import threading
import os

name = ""

def read_output(pipe):
    with open('testing/output_capture.txt', 'w') as file:
        while True:
            output = pipe.read(1)
            if output == '' and proc.poll() is not None:
                break
            if output:
                print(output, end='')
                file.write(output)

def write_input(pipe):
    global name
    with open('testing/input_capture.txt', 'w') as file:
        user_input = ""
        try:
            while True:
                sys.stdout.flush()
                user_input = input()
                proc.stdin.write(user_input + "\n")
                proc.stdin.flush()
                file.write(user_input + "\n")
        except (KeyboardInterrupt, EOFError, BrokenPipeError):
            name = user_input
            pass

answer = ""
ignore_errors = False
while answer.lower() != "y" and answer.lower() != "n":
    answer = input("Ignorer les erreurs ? (y/n)")
    
if answer == "y":
    ignore_errors = true;

# Path to the JSON file
json_file = 'testing/tests.json'

# Read the contents of the JSON file
with open(json_file, 'r', encoding="utf-8") as file:
    json_contents = file.read()

# Parse the JSON contents
data = json.loads(json_contents, strict=False)

# make data the contents of testing/test.FC
with open('testing/test.FC', 'r', encoding="utf-8") as file:
    code = file.read()

proc = subprocess.Popen(
    ['build/interpreter', 'testing/test.FC'],
    stdin=subprocess.PIPE,
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True
)

output_thread = threading.Thread(target=read_output, args=(proc.stdout,))
input_thread = threading.Thread(target=write_input, args=(proc.stdin,))
output_thread.start()
input_thread.start()

proc.wait()
output_thread.join()

print("Enter the name of the test: ")
input_thread.join()
    
    
with open('testing/input_capture.txt', 'r') as input_file:
    with open('testing/output_capture.txt', 'r') as output_file:
        input_data = "".join(input_file.readlines())
        output_data = "".join(output_file.readlines())
        data.append({"name": name, "code": code, "output": output_data, "input":input_data, "errors": not ignore_errors})

# Write the updated data back to the JSON file
with open(json_file, 'w', encoding='utf-8') as file:
    file.write(json.dumps(data, indent=4, ensure_ascii=False).encode('utf-8').decode())
