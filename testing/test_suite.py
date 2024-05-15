import json
import subprocess
import platform

# Path to the JSON file
json_file = 'testing/tests.json'

# build the executable if erwan
if platform.system() == "Darwin":
    print("Building interpreter...")
    subprocess.run("""gcc -g -o build/interpreter src/*.c src/*/*/*.c src/*/*.c""", shell=True, capture_output=True, text=True)
    print("Interpreter built, starting tests...")

# Read the contents of the JSON file
with open(json_file, 'r') as file:
    json_contents = file.read()

# Parse the JSON contents
data = json.loads(json_contents)
passed = 0
total = 0
for line in data:

    with open('testing/python_test.FC', 'w') as f:
        f.write(line["code"])
    if platform.system() == "Darwin" : # pour que erwan puisse faire les tests
        
        res = subprocess.run(f"""/usr/local/bin/valgrind --error-exitcode=1 --leak-check=full --suppressions=testing/minimal.supp build/interpreter testing/python_test.FC """,
                         shell=True, capture_output=True, text=True)
    else:
        res = subprocess.run(f"""valgrind --error-exitcode=1 --leak-check=full build/interpreter testing/python_test.FC """,
                         shell=True, capture_output=True, text=True)
    if res.returncode != 0:
        print("\033[91mMemory errors detected by Valgrind\033[0m")
        print(f"err:\n{res.stderr}")
        print(f"err:\n{res.stdout}")
    else:
        # res = subprocess.run(f"""build/interpreter testing/python_test.FC""", shell=True, capture_output=True, text=True)
        
        if (res.stdout == line["output"]):
            passed += 1
            print(f"\033[92mTest {line['name']} passed\033[0m")
        else:
            print(f"\033[91mTest {line['name']} failed\033[0m")
            print(f"\033[91mExpected: '{line['output']}'\033[0m")
            print(f"\033[91mGot: '{res.stdout}'\033[0m")



    total += 1

print(f"Passed {passed}/{total} tests")
