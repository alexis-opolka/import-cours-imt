# !/bin/env python3

from string import ascii_uppercase
from os import getcwd
from pathlib import Path

out_filename = "rick-passwords.log.local"

numeros = list(range(0,10))
uppercase_letters = ascii_uppercase
band_name = ["The", "Flesh", "Curtains"]
supposed_passwords = []

### -------------- First: Generate the entire list of passwords --------------
print("Generating passwords...")

### We start with an uppercase letter
for letter in uppercase_letters:
    ### Then a natural int
    for numero in numeros:
        ### To end with one word of Rick's band name
        for band_word in band_name:
            supposed_passwords.append(f"{letter}{numero}{band_word}\n")

print("Password generated!")

### -------------- Second: Write the entire list onto a file to be later used as a dictionary --------------

with open(f"./{out_filename}", "wt", encoding="utf-8") as fout:
    fout.writelines(supposed_passwords)

if not fout.closed:
    fout.close()

print(f"You can find the dictionary at the root of your current working directory: {Path(getcwd())}/{out_filename}")
