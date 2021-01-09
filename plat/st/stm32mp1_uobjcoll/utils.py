import os, sys
import glob
import re

def get_includes():
    files = []
    for root, dir, file in os.walk("."):
        for x in file:
            if x.endswith(('.h', '.c', '.S')):
                files.append(os.path.join(root, x))
    includes = set()
    for path in files:
        with open(path, "r") as f:
            match = re.findall(r"(?<=#include <).*(?=>\n)", f.read())
            includes |= set(match)

    includes = list(includes)
    includes.sort()
    return includes
    

if __name__ == "__main__":
    print("\n".join(get_includes()))