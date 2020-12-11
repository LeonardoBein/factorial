import re
import sys

number_of_lines = 5

print("factorial;runtime;result")
with open(sys.argv[1], "r") as file:
    for j in range(150):
        data = ""
        for i in range(number_of_lines):

            data += file.readline()
        m1 = re.search(r"(\d+)\! = (.+)", data)
        m2 = re.search(r"user\s+0m(.+)s", data)

        if m1 and m2:
            print(f"{m1.group(1)};{m2.group(1)};{m1.group(2).replace('.',',')}")