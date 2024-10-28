import json
import subprocess
import platform

failed = False

# Path to the JSON file
json_file = 'testing/tests.json'

# build the executable if erwan
if platform.system() == "Darwin":
    print("Building interpreter...")
    subprocess.run("""make clean""", shell=True,
                   capture_output=True, text=True)
    subprocess.run("""make""", shell=True, capture_output=True, text=True)
    print("Interpreter built, starting tests...")

# Read the contents of the JSON file
with open(json_file, 'r') as file:
    json_contents = file.read()

# Parse the JSON contents
data = json.loads(json_contents, strict=False)
passed = 0
total = 0
for line in data:
    if "input" in line.keys():
        with open('testing/input.txt', 'w') as f:
            f.write(line["input"])
    with open('testing/python_test.COCS', 'w') as f:
        f.write(line["code"])
    if platform.system() == "Darwin":  # pour que erwan puisse faire les tests
        command = f"""/usr/local/bin/valgrind --error-exitcode=1 --leak-check=full --suppressions=testing/minimal.supp build/interpreter testing/python_test.COCS """
    else:
        command = f"""valgrind --error-exitcode=1 --leak-check=full build/interpreter testing/python_test.COCS """

    if "input" in line.keys() and line["input"] != "":
        command += "--input testing/input.txt"

    if "errors" in line.keys() and not line["errors"]:
        command += "--ignore_errors"

    res = subprocess.run(command, shell=True, capture_output=True, text=True)
    if res.returncode != 0:
        failed = True
        print(
            f"\033[91mMemory errors detected by Valgrind on test {line['name']}\033[0m")
        print(f"err:\n{res.stderr}")
        print(f"err:\n{res.stdout}")
        with open("testing/last_fail.COCS", 'w+') as f:
            f.write(line["code"])

    else:
        # res = subprocess.run(f"""build/interpreter testing/python_test.COCS""", shell=True, capture_output=True, text=True)

        if (res.stdout == line["output"]):
            passed += 1
            print(f"\033[92mTest {line['name']} passed\033[0m")
        else:
            failed = True
            print(f"\033[91mTest {line['name']} failed\033[0m")
            print(f"\033[91mExpected: '{line['output']}'\033[0m")
            print(f"\033[91mGot: '{res.stdout}'\033[0m")
            with open("testing/last_fail.COCS", 'w+') as f:
                f.write(line["code"])

    total += 1

print(f"Passed {passed}/{total} tests")

exit(1 if failed else 0) # permet de faire fonctionner le script dans un makefile avec github workflow