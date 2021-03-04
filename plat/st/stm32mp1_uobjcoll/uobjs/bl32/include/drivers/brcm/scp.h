/*
 * Copyright (c) 2017 - 2020, Broadcom
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SCP_H
#define SCP_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libc/stdint.h>

int download_scp_patch(void *image, unsigned int image_size);

#endif /* SCP_H */
