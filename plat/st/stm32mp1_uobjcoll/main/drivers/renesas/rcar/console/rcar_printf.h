/*
 * Copyright (c) 2015-2019, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RCAR_PRINTF_H
#define RCAR_PRINTF_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/string.h>

int32_t rcar_set_log_data(int32_t c);
int32_t rcar_log_init(void);

#endif /* RCAR_PRINTF_H */
