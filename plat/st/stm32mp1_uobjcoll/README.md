# Build guide for stm32mp1 uber object collection

## Prerequisites:
  * Install the next-gen uberspark toolkit (https://docs.uberspark.org/nextgen-toolkit/genuser-guide/install.html).
  * If using WSL, requires WSL v2.

## Building uobjcoll:
Run the following commands from this folder.
```sh
make clean
make
```

Note: If we just want to build the uobjcoll without
building u-boot, then we just use make uobjcoll above
instead of make

## Building native:
Run the following commands from this folder.
```sh
make clean
make native
```
