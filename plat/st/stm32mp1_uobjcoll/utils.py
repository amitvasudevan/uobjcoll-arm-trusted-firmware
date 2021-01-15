import os, sys
import glob
import re
from tqdm import tqdm
import json
from jsoncomment import JsonComment

STD_HEADERS = [
"assert.h",
"cdefs.h",
"endian.h",
"errno.h",
"fcntl.h",
"features.h",
"limits.h",
"setjmp.h",
"stdarg.h",
"stdbool.h",
"stddef.h",
"stdint.h",
"stdio.h",
"stdlib.h",
"string.h",
"time.h",
"unistd.h",
]

def get_files(path="."):
    files = []
    for root, dir, file in os.walk(path):
        for x in file:
            if x.endswith(('.h', '.c', '.S')):
                files.append(os.path.join(root, x))
    return files

def get_includes():
    files = get_files()
    includes = set()
    for path in files:
        with open(path, "r") as f:
            match = re.findall(r"(?<=#include <).*(?=>\n)", f.read())
            includes |= set(match)

    includes = list(includes)
    includes.sort()
    return includes

def modify_includes(path="."):
    files = get_files(path=path)
    stdh_reg = '|'.join([re.escape(x) for x in STD_HEADERS])
    
    for path in tqdm(files):
        with open(path, "r") as f:
            replace = re.sub(r"(?<=#include <)(.*)(?=>\n)", r"uberspark/uobjcoll/platform/st/stm32mp1/main/include/\1", f.read())
        with open(path, "w") as f:
            f.write(replace)

    for path in tqdm(files):
        with open(path, "r") as f:
            replace = re.sub(r"(?<=#include <).*(" + stdh_reg + r").*(?=>\n)", r"uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/\1", f.read())
        with open(path, "w") as f:
            f.write(replace)

    

def get_include_refs():
    with open("main/uberspark.json", "r") as f:
        parser = JsonComment(json)
        manifest = parser.loads(f.read())
    
    include_reg = '|'.join([re.escape(x) for x in manifest["uberspark.uobj.source_h_files"][10:]])
    files = get_files()

    sources = set()
    for path in tqdm(files):
        if path.endswith(('.c')):
            with open(path, "r") as f:
                match = re.findall(r"(?<=include\/).*" + include_reg + ".*(?=>\n)", f.read())
            if match:
                sources.add(path[7:])
    
    sources = list(sources)
    sources.sort()
    return sources

# def modify_configdefs(path="."):
#     with open("uberspark.json", "r") as f:
#         parser = JsonComment(json)
#         manifest = parser.loads(f.read())
#     keys = [x['name'] for x in manifest["uberspark.uobjcoll.configdefs"]]
#     keys_reg = '|'.join([re.escape(x) for x in keys])

#     files = get_files(path=path)
    
#     for path in tqdm(files):
#         with open(path, "r") as f:
#             replace = re.sub(r"\b(" + keys_reg + r")\b", lambda match: "__UBERSPARK_UOBJCOLL_CONFIGDEF_" + match.group(1).upper() + "__", f.read())
#         with open(path, "w") as f:
#             f.write(replace)

def modify_configdefs(path="."):
    with open("uberspark.json", "r") as f:
        parser = JsonComment(json)
        manifest = parser.loads(f.read())
    keys = [x['name'] for x in manifest["uberspark.uobjcoll.configdefs"]]
    keys_reg = '|'.join([re.escape(x) for x in keys])

    files = get_files(path=path)
    
    for path in tqdm(files):
        with open(path, "r") as f:
            replace = re.sub(r"\b(" + keys_reg + r")\b", lambda match: "__UBERSPARK_UOBJCOLL_CONFIGDEF_" + match.group(1).upper() + "__", f.read())
            replace = re.sub(r"(#include <.*>)", lambda match: "#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>\n"+ match.group(1), replace, 1)
        with open(path, "w") as f:
            f.write(replace)

if __name__ == "__main__":
    # print("\n".join(get_includes()))
    # modify_includes(path="main/services/std_svc")
    # print("\n".join(get_include_refs()))
    modify_includes(path="main/drivers/auth")