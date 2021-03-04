/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef IO_STM32IMAGE_H
#define IO_STM32IMAGE_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/drivers/io/io_driver.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/drivers/partition/partition.h>

#define MAX_LBA_SIZE		512
#define MAX_PART_NAME_SIZE	(EFI_NAMELEN + 1)
#define STM32_PART_NUM		(__UBERSPARK_UOBJCOLL_CONFIGDEF_PLAT_PARTITION_MAX_ENTRIES__ - __UBERSPARK_UOBJCOLL_CONFIGDEF_STM32_TF_A_COPIES__)

struct stm32image_part_info {
	char name[MAX_PART_NAME_SIZE];
	uint32_t binary_type;
	uintptr_t part_offset;
	uint32_t bkp_offset;
};

struct stm32image_device_info {
	struct stm32image_part_info part_info[STM32_PART_NUM];
	unsigned long long device_size;
	uint32_t lba_size;
};

int register_io_dev_stm32image(const io_dev_connector_t **dev_con);

#endif /* IO_STM32IMAGE_H */
