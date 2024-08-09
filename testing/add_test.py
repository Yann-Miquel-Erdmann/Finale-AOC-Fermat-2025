import json
import subprocess
import platform

# Path to the JSON file
json_file = 'testing/tests.json'

# Read the contents of the JSON file
with open(json_file, 'r', encoding="utf-8") as file:
    json_contents = file.read()

# Parse the JSON contents
data = json.loads(json_contents)

# make data the contents of testing/test.FC
with open('testing/test.FC', 'r', encoding="utf-8") as file:
    code = file.read()

# code.replace('\n', ' ')   

# build the executable if erwan
if platform.system() == "Darwin":
    print("Building interpreter...")
    subprocess.run("""make clean""", shell=True, capture_output=True, text=True)
    subprocess.run("""make""", shell=True, capture_output=True, text=True)
    print("Interpreter built, starting tests...")


res = subprocess.run(f"""build/interpreter testing/test.FC""",
                     shell=True, capture_output=True, text=True)
                     
if platform.system() == "Darwin":
    name = "<Put name here>" # xcode ne supporte pas le input car python est pas de base dessus, flemme d'utiliser autre chose
    
else:
    name = input("Enter the name of the test: ")
data.append({"name": name, "code": code, "output": res.stdout})

# Write the updated data back to the JSON file
with open(json_file, 'w', encoding='utf-8') as file:
    file.write(json.dumps(data, indent=4, ensure_ascii=False).encode('utf-8').decode())
