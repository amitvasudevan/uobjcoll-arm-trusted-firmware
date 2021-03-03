#   trustzone firmware Makefile refactored to use the überSpark next-gen toolkit for stm32mp1
#   
#   author: ethan joseph <ethanj217@gmail.com>
#

.DEFAULT_GOAL := everything
REPO_ROOT = ../../../
MAKE_HELPERS_DIRECTORY := ${REPO_ROOT}make_helpers/
TF_PLATFORM_ROOT = ${REPO_ROOT}plat/
BUILD_PLAT = ./_build
CROSS_COMPILE := arm-linux-gnueabihf-
export CROSS_COMPILE

DOCKER_TAG := stm32mp1:build
SRCROOTDIR := $(abspath ${REPO_ROOT})
SRCDIR_MOUNT := /home/uberspark/uobjcoll-arm-trusted-firmware/

include ${MAKE_HELPERS_DIRECTORY}build_macros.mk
include ${MAKE_HELPERS_DIRECTORY}build_env.mk

include ${MAKE_HELPERS_DIRECTORY}defaults.mk
PLAT := stm32mp1
ARCH := aarch32
ARM_ARCH_MAJOR := 7
AARCH32_SP := sp_min
STM32MP_SDMMC := 1
STM32MP_EMMC := 1
STM32MP_RAW_NAND := 1
STM32MP_SPI_NAND := 1
STM32MP_SPI_NOR := 1
DTB_FILE_NAME := stm32mp157c-ev1.dtb
#############################################

include ${REPO_ROOT}lib/compiler-rt/compiler-rt.mk

BL_COMMON_SOURCES	+= common/bl_common.c			\
				common/tf_log.c				\
				common/${ARCH}/debug.S			\
				drivers/console/multi_console.c		\
				lib/${ARCH}/cache_helpers.S		\
				lib/${ARCH}/misc_helpers.S		\
				plat/common/plat_bl_common.c		\
				plat/common/plat_log_common.c		\
				plat/common/${ARCH}/plat_common.c	\
				plat/common/${ARCH}/platform_helpers.S	\
				${COMPILER_RT_SRCS}

INCLUDES		+=	-I${REPO_ROOT}include				\
				-I${REPO_ROOT}include/arch/${ARCH}			\
				-I${REPO_ROOT}include/lib/cpus/${ARCH}		\
				-I${REPO_ROOT}include/lib/el3_runtime/${ARCH}	\
				${PLAT_INCLUDES}			

##############################

include ${MAKE_HELPERS_DIRECTORY}plat_helpers.mk
include ./uobjs/bl32/platform.mk
include ${MAKE_HELPERS_DIRECTORY}armv7-a-cpus.mk
include ${REPO_ROOT}lib/cpus/cpu-ops.mk

include ${REPO_ROOT}lib/stack_protector/stack_protector.mk

# include ${REPO_ROOT}lib/libc/libc.mk
LIBC_SRCS	:=	$(addprefix ${REPO_ROOT}lib/libc/,		\
			abort.c				\
			assert.c			\
			exit.c				\
			memchr.c			\
			memcmp.c			\
			memcpy.c			\
			memmove.c			\
			memrchr.c			\
			memset.c			\
			printf.c			\
			putchar.c			\
			puts.c				\
			snprintf.c			\
			strchr.c			\
			strcmp.c			\
			strlcpy.c			\
			strlen.c			\
			strncmp.c			\
			strnlen.c			\
			strrchr.c)

INCLUDES	+=	-I${REPO_ROOT}include/lib/libc		\
			-I${REPO_ROOT}include/lib/libc/$(ARCH)	\


include ${REPO_ROOT}bl2/bl2.mk

########

Q:=@
ECHO:=@echo
CHECKCODE_ARGS	+=	--no-summary --terse

export Q ECHO

################################################################################
# Native build toolchain
################################################################################

HOSTCC			:=	gcc
export HOSTCC

CC			:=	${CROSS_COMPILE}gcc
CPP			:=	${CROSS_COMPILE}cpp
AS			:=	${CROSS_COMPILE}gcc
AR			:=	${CROSS_COMPILE}ar
LINKER		:=	${CROSS_COMPILE}ld
OC			:=	${CROSS_COMPILE}objcopy
OD			:=	${CROSS_COMPILE}objdump
NM			:=	${CROSS_COMPILE}nm
PP			:=	${CROSS_COMPILE}gcc -E
DTC			:=	dtc

target32-directive	= 	-target arm-none-eabi

TF_CFLAGS_aarch32	=	$(march32-directive)
TF_CFLAGS_aarch64	=	$(march64-directive)
LD					=	$(LINKER)
TF_CFLAGS_aarch32	+=	-mthumb -mno-unaligned-access
ASFLAGS_aarch32		=	$(march32-directive)

#######################################################
# Warnings and debug:
#######################################################

# Process Debug flag
$(eval $(call add_define,DEBUG))
ifneq (${DEBUG}, 0)
        BUILD_TYPE	:=	debug
        TF_CFLAGS	+= 	-g
        ASFLAGS		+= 	-g

        # Use LOG_LEVEL_INFO by default for debug builds
        LOG_LEVEL	:=	40

        # General warnings
        WARNINGS    :=	-Wall -Wmissing-include-dirs -Wunused	\
                        -Wdisabled-optimization	-Wvla -Wshadow	\
                        -Wno-unused-parameter -Wredundant-decls

        # Additional warnings
        # Level 1
        WARNING1 := -Wextra
        WARNING1 += -Wmissing-format-attribute
        WARNING1 += -Wmissing-prototypes
        WARNING1 += -Wold-style-definition

        # Level 2
        WARNING2 := -Waggregate-return
        WARNING2 += -Wcast-align
        WARNING2 += -Wnested-externs

        WARNING3 := -Wbad-function-cast
        WARNING3 += -Wcast-qual
        WARNING3 += -Wconversion
        WARNING3 += -Wpacked
        WARNING3 += -Wpointer-arith
        WARNING3 += -Wswitch-default

        ifeq (${W},1)
        WARNINGS += $(WARNING1)
        else ifeq (${W},2)
        WARNINGS += $(WARNING1) $(WARNING2)
        else ifeq (${W},3)
        WARNINGS += $(WARNING1) $(WARNING2) $(WARNING3)
        endif

        # not using clang
        WARNINGS	+= -Wunused-but-set-variable -Wmaybe-uninitialized \
                        -Wpacked-bitfield-compat -Wshift-overflow=2 \
                        -Wlogical-op

        ifneq (${E},0)
        ERRORS := -Werror
        endif
else
        BUILD_TYPE	:=	release
        # Use LOG_LEVEL_NOTICE by default for release builds
        LOG_LEVEL	:=	20
endif


CPPFLAGS		=	${DEFINES} ${INCLUDES} ${MBEDTLS_INC} -nostdinc	\
				$(ERRORS) $(WARNINGS)
ASFLAGS			+=	$(CPPFLAGS) $(ASFLAGS_$(ARCH))			\
				-ffreestanding -Wa,--fatal-warnings
TF_CFLAGS		+=	$(CPPFLAGS) $(TF_CFLAGS_$(ARCH))		\
				-ffunction-sections -fdata-sections		\
				-ffreestanding -fno-builtin -fno-common		\
				-Os -std=gnu99

TF_LDFLAGS		+=	--fatal-warnings -O1
TF_LDFLAGS		+=	--gc-sections

DTC_FLAGS		+=	-I dts -O dtb
DTC_CPPFLAGS		+=	-P -nostdinc -Iinclude -Ifdts -undef \
				-x assembler-with-cpp $(DEFINES)

################################################################################
# Build options checks
################################################################################

$(eval $(call add_defines,\
	$(sort \
		ALLOW_RO_XLAT_TABLES \
		ARM_ARCH_MAJOR \
		ARM_ARCH_MINOR \
		COLD_BOOT_SINGLE_CPU \
		CTX_INCLUDE_AARCH32_REGS \
		CTX_INCLUDE_FPREGS \
		CTX_INCLUDE_PAUTH_REGS \
		EL3_EXCEPTION_HANDLING \
		CTX_INCLUDE_MTE_REGS \
		CTX_INCLUDE_EL2_REGS \
		CTX_INCLUDE_NEVE_REGS \
		DECRYPTION_SUPPORT_none \
		DISABLE_MTPMU \
		ENABLE_AMU \
		ENABLE_ASSERTIONS \
		ENABLE_BTI \
		ENABLE_MPAM_FOR_LOWER_ELS \
		ENABLE_PAUTH \
		ENABLE_PIE \
		ENABLE_PMF \
		ENABLE_PSCI_STAT \
		ENABLE_RUNTIME_INSTRUMENTATION \
		ENABLE_SPE_FOR_LOWER_ELS \
		ENABLE_SVE_FOR_NS \
		ENCRYPT_BL31 \
		ENCRYPT_BL32 \
		ERROR_DEPRECATED \
		FAULT_INJECTION_SUPPORT \
		GICV2_G0_FOR_EL3 \
		HANDLE_EA_EL3_FIRST \
		HW_ASSISTED_COHERENCY \
		LOG_LEVEL \
		MEASURED_BOOT \
		NS_TIMER_SWITCH \
		PL011_GENERIC_UART \
		PLAT_${PLAT} \
		PROGRAMMABLE_RESET_ADDRESS \
		PSCI_EXTENDED_STATE_ID \
		RAS_EXTENSION \
		RESET_TO_BL31 \
		SEPARATE_CODE_AND_RODATA \
		SEPARATE_NOBITS_REGION \
		RECLAIM_INIT_CODE \
		SPD_none \
		SPIN_ON_BL1_EXIT \
		SPM_MM \
		SPMD_SPM_AT_SEL2 \
		TRUSTED_BOARD_BOOT \
		USE_COHERENT_MEM \
		USE_DEBUGFS \
		ARM_IO_IN_DTB \
		SDEI_IN_FCONF \
		SEC_INT_DESC_IN_FCONF \
		USE_ROMLIB \
		USE_TBBR_DEFS \
		WARMBOOT_ENABLE_DCACHE_EARLY \
		BL2_AT_EL3 \
		BL2_IN_XIP_MEM \
		BL2_INV_DCACHE \
		USE_SPINLOCK_CAS \
		ERRATA_SPECULATIVE_AT \
		RAS_TRAP_LOWER_EL_ERR_ACCESS \
		COT_DESC_IN_DTB \
		USE_SP804_TIMER \
)))

DTC_CPPFLAGS		+=	-P -nostdinc -I${REPO_ROOT}include -I${REPO_ROOT}fdts -undef \
				-x assembler-with-cpp $(DEFINES)


$(eval $(call MAKE_LIB_DIRS))
$(eval $(call MAKE_LIB,c))

# DTB
$(eval FDT_SOURCES := $(addprefix $(REPO_ROOT),$(FDT_SOURCES)))
$(eval $(call MAKE_DTBS,$(BUILD_PLAT)/fdts,$(FDT_SOURCES)))
$(eval $(call MAKE_PREREQ_DIR,${BUILD_PLAT}))

# BL2
$(eval BL2_SOURCES := $(addprefix $(REPO_ROOT),$(BL2_SOURCES)))
$(eval BL_COMMON_SOURCES := $(addprefix $(REPO_ROOT),$(BL_COMMON_SOURCES)))
$(eval PLAT_BL_COMMON_SOURCES := $(addprefix $(REPO_ROOT),$(PLAT_BL_COMMON_SOURCES)))
$(eval BL2_LINKERFILE := $(addprefix $(REPO_ROOT),$(BL2_LINKERFILE)))


FIP_BL2_ARGS := tb-fw

$(if ${BL2}, $(eval $(call TOOL_ADD_IMG,bl2,--${FIP_BL2_ARGS})),\
	$(eval $(call MAKE_BL,2,${FIP_BL2_ARGS})))

######################################################

define docker_run
	docker run --rm \
		-e D_CMD="$(2)" \
		-e D_UID="$(3)" \
		-e D_GID="$(4)" \
		-e MAKE="make" \
		-v $(SRCROOTDIR):$(SRCDIR_MOUNT) \
		-t $(1) 
endef

define NATIVE_BUILD_OPTS
	CROSS_COMPILE=$(CROSS_COMPILE) \
	PLAT=$(PLAT) \
	ARCH=$(ARCH) \
	ARM_ARCH_MAJOR=$(ARM_ARCH_MAJOR) \
	AARCH32_SP=$(AARCH32_SP) \
	STM32MP_SDMMC=$(STM32MP_SDMMC) \
	STM32MP_EMMC=$(STM32MP_EMMC) \
	STM32MP_RAW_NAND=$(STM32MP_RAW_NAND) \
	STM32MP_SPI_NAND=$(STM32MP_SPI_NAND) \
	STM32MP_SPI_NOR=$(STM32MP_SPI_NOR) \
	DTB_FILE_NAME=$(DTB_FILE_NAME)
endef

.PHONY: everything  # can't use all because build_macros.mk adds a prereq to all
everything: docker_build uobjcoll

.PHONY: native
native: build_bridge
	$(call docker_run, $(DOCKER_TAG), cd $(SRCDIR_MOUNT) && make $(NATIVE_BUILD_OPTS), $(shell id -u), $(shell id -g))
	$(call docker_run, $(DOCKER_TAG), cd $(SRCDIR_MOUNT)plat/st/stm32mp1_uobjcoll && make -w _build/u-boot/u-boot.stm32, $(shell id -u), $(shell id -g))
	mv $(REPO_ROOT)build/$(PLAT)/release/* _build/
	rm -rf $(REPO_ROOT)build/

.PHONY: build_bridge
build_bridge: 
	docker build -t $(DOCKER_TAG) .

.PHONY: docker_build
docker_build: build_bridge
	$(call docker_run, $(DOCKER_TAG), cd $(SRCDIR_MOUNT)plat/st/stm32mp1_uobjcoll && make -w docker_targets, $(shell id -u), $(shell id -g))

.PHONY: docker_targets
docker_targets: dtbs bl2 _build/u-boot/u-boot.stm32 # dtbs and bl2 generated above

_build/u-boot/u-boot.stm32:
	rm -rf ${BUILD_PLAT}/u-boot
	git clone https://github.com/STMicroelectronics/u-boot ${BUILD_PLAT}/u-boot
	$(MAKE) -C ${BUILD_PLAT}/u-boot stm32mp15_trusted_defconfig
	$(MAKE) -C ${BUILD_PLAT}/u-boot DEVICE_TREE=stm32mp157c-ev1 all


.PHONY: uobjcoll
uobjcoll: stage
	@echo building stm32 collection...
	uberspark staging switch stm32mp1 
	uberspark build -v 
	@echo built stm32 collection successfully!

.PHONY: stage
stage:
	@echo creating staging
	uberspark staging create stm32mp1 
	# uberspark staging config-set --setting-name=uobjcoll_binary_image_load_address --setting-value=0x06200000
	# uberspark staging config-set --setting-name=uobj_binary_image_size --setting-value=0x14900000
	uberspark staging config-set --setting-name=cc_bridge_namespace --setting-value=uberspark/bridges/container/amd64/cc-bridge/armv7_32/generic/gcc/v10.2
	uberspark staging config-set --setting-name=as_bridge_namespace --setting-value=uberspark/bridges/container/amd64/as-bridge/armv7_32/cortex-a7/gnu-as/v2.34
	uberspark staging config-set --setting-name=ld_bridge_namespace --setting-value=uberspark/bridges/container/amd64/ld-bridge/armv7_32/generic/gnu-ld/v2.34
	@echo staging created successfully!

.PHONY: clean
clean: 
	rm -rf _build
	rm -rf $(REPO_ROOT)build
	uberspark staging switch default
	uberspark staging remove stm32mp1