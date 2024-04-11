import json
import subprocess

# Path to the JSON file
json_file = 'testing/tests.json'

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

    res = subprocess.run(f"""build/interpreter testing/python_test.FC""", shell=True, capture_output=True, text=True)
    if (res.stdout == line["output"]):
        passed += 1
        print(f"Test {line['name']} passed")
    else:
        print(f"\033[91mTest {line['name']} failed\033[0m")
        print(f"\033[91mExpected: '{line['output']}'\033[0m")
        print(f"\033[91mGot: '{res.stdout}'\033[0m")

    
    total += 1

print(f"Passed {passed}/{total} tests")