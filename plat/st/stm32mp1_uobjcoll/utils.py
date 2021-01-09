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

# ORIG_INCLUDES = [
#     "arch/arch.h",
#     "arch/arch_helpers.h",
#     "arch/asm_macros.S",
#     "bl32/sp_min/platform_sp_min.h",
#     "boot_api.h",
#     "common/bl_common.h",
#     "common/debug.h",
#     "common/desc_image_load.h",
#     "common/runtime_svc.h",
#     "common/tbbr/tbbr_img_def.h",
#     "lib/el3_runtime/aarch32/context.h",
#     "drivers/arm/gic_common.h",
#     "drivers/arm/gicv2.h",
#     "drivers/arm/tzc400.h",
#     "drivers/delay_timer.h",
#     "drivers/generic_delay_timer.h",
#     "drivers/nand.h",
#     "drivers/raw_nand.h",
#     "drivers/spi_nand.h",
#     "drivers/spi_nor.h",
#     "drivers/st/bsec.h",
#     "drivers/st/etzpc.h",
#     "drivers/st/scmi-msg.h",
#     "drivers/st/scmi.h",
#     "drivers/st/stm32_console.h",
#     "drivers/st/stm32_gpio.h",
#     "drivers/st/stm32_iwdg.h",
#     "drivers/st/stm32mp1_clk.h",
#     "drivers/st/stm32mp1_pwr.h",
#     "drivers/st/stm32mp1_ram.h",
#     "drivers/st/stm32mp1_rcc.h",
#     "drivers/st/stm32mp_pmic.h",
#     "drivers/st/stm32mp_reset.h",
#     "drivers/st/stpmic1.h",
#     "dt-bindings/clock/stm32mp1-clks.h",
#     "dt-bindings/interrupt-controller/arm-gic.h",
#     "dt-bindings/reset/stm32mp1-resets.h",
#     # "errno.h",
#     "lib/el3_runtime/context_mgmt.h",
#     "lib/mmio.h",
#     "lib/optee_utils.h",
#     "lib/psci/psci.h",
#     "lib/utils.h",
#     "lib/utils_def.h",
#     "lib/xlat_tables/xlat_tables_defs.h",
#     "lib/xlat_tables/xlat_tables_v2.h",
#     "lib/libfdt/libfdt.h",
#     "plat/common/common_def.h",
#     "plat/common/platform.h",
#     "platform_def.h",
#     # "platform_sp_min.h",
#     # "stdbool.h",
#     # "stdint.h",
#     # "stdio.h",
#     "stm32mp1_context.h",
#     "stm32mp1_dbgmcu.h",
#     "stm32mp1_private.h",
#     "stm32mp1_shared_resources.h",
#     "stm32mp1_smc.h",
#     "plat/st/common/stm32mp_auth.h",
#     "plat/st/common/stm32mp_common.h",
#     "plat/st/common/stm32mp_dt.h",
#     "plat/st/common/stm32mp_shared_resources.h",
#     "plat/st/common/stm32mp_shres_helpers.h",
#     "tools_share/uuid.h",
#     # "assert.h",
#     # "string.h",
# ]

def get_files():
    files = []
    for root, dir, file in os.walk("."):
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

def modify_includes():
    files = get_files()
    stdh_reg = '|'.join([re.escape(x) for x in STD_HEADERS])
    
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

# def get_all_includes(start_includes, itr):
#     if itr == 0:
#         return start_includes
#     includes = set(start_includes)
#     files = [os.path.join(os.getcwd(), "main/include/" + x) for x in start_includes]
#     for path in tqdm(files):
#         try:
#             with open(path, "r") as f:
#                 match = re.findall(r"(?<=include\/).*(?=>\n)", f.read())
#                 includes |= set(match)
#         except:
#             print(path)
    
#     includes = list(includes)
#     includes.sort()
#     return get_all_includes(includes, itr-1)

if __name__ == "__main__":
    print("\n".join(get_includes()))
    # modify_includes()
    # print("\n".join(get_all_includes(ORIG_INCLUDES, 4)))