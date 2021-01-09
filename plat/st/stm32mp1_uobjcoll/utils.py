import os, sys
import glob
import re
from tqdm import tqdm

STD_HEADERS = [
    "assert.h",
    "complex.h",
    "ctype.h",
    "errno.h",
    "fenv.h",
    "float.h",
    "inttypes.h",
    "iso646.h",
    "limits.h",
    "locale.h",
    "math.h",
    "setjmp.h",
    "signal.h",
    "stdalign.h",
    "stdarg.h",
    "stdatomic.h",
    "stdbool.h",
    "stddef.h",
    "stdint.h",
    "stdio.h",
    "stdlib.h",
    "stdnoreturn.h",
    "string.h",
    "tgmath.h",
    "threads.h",
    "time.h",
    "uchar.h",
    "wchar.h",
    "wctype.h",
]

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

def modify_includes():
    files = []
    stdh_reg = '|'.join([re.escape(x) for x in STD_HEADERS])
    for root, dir, file in os.walk("."):
        for x in file:
            if x.endswith(('.h', '.c', '.S')):
                files.append(os.path.join(root, x))
    for path in tqdm(files):
        with open(path, "r") as f:
            replace = re.sub(r"(?<=#include <)(.*)(?=>\n)", r"uberspark/uobjcoll/platform/st/stm32mp1/main/include/\1", f.read())
        with open(path, "w") as f:
            f.write(replace)
    
    for path in tqdm(files):
        with open(path, "r") as f:
            replace = re.sub(r"(?<=#include <).*(" + stdh_reg + r").*(?=>\n)", r"uberspark/uobjrtl/crt/include/\1", f.read())
        with open(path, "w") as f:
            f.write(replace)


if __name__ == "__main__":
    # print("\n".join(get_includes()))
    modify_includes()