# Build guide for stm32mp1

## Prerequisites:
Install the required packages:
```sh
sudo apt install build-essential git libssl-dev
```
Then download the `arm-linux-none-gnueabihf` cross compiler from https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads and extract it, then run

```
export CROSS_COMPILE=<path-to-cross-compiler>/bin/arm-none-linux-gnueabihf-
```

## Building TF-A:
Run the following commands from the root of this repository.

To build with SP_min and support for all bootable devices:
```sh
make PLAT=stm32mp1 ARCH=aarch32 ARM_ARCH_MAJOR=7 AARCH32_SP=sp_min STM32MP_SDMMC=1 STM32MP_EMMC=1 STM32MP_RAW_NAND=1 STM32MP_SPI_NAND=1 STM32MP_SPI_NOR=1 DTB_FILE_NAME=stm32mp157c-ev1.dtb
```

To enable stack protection, add `ENABLE_STACK_PROTECTOR=1` to the make command.

Clone the u-boot repository:
```
cd ..
git clone https://github.com/STMicroelectronics/u-boot.git
```

And finally build
```
cd u-boot
make stm32mp15_trusted_defconfig
make DEVICE_TREE=stm32mp157c-ev1 all
```

Guide adapted from https://trustedfirmware-a.readthedocs.io/en/latest/plat/stm32mp1.html