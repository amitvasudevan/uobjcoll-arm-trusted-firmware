/*
 * Copyright (c) 2014-2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/platform_def.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/assert.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/el3_runtime/cpu_data.h>

/* The per_cpu_ptr_cache_t space allocation */
cpu_data_t percpu_data[PLATFORM_CORE_COUNT];
