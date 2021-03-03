/*
 * Copyright (c) 2018-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ASSERT_H
#define ASSERT_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/libc/cdefs.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/platform_def.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/common/debug.h>

#ifndef PLAT_LOG_LEVEL_ASSERT
#define PLAT_LOG_LEVEL_ASSERT	__UBERSPARK_UOBJCOLL_CONFIGDEF_LOG_LEVEL__
#endif

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_ENABLE_ASSERTIONS__
# if PLAT_LOG_LEVEL_ASSERT >= LOG_LEVEL_VERBOSE
#  define assert(e)	((e) ? (void)0 : __assert(__FILE__, __LINE__, #e))
# elif PLAT_LOG_LEVEL_ASSERT >= LOG_LEVEL_INFO
#  define assert(e)	((e) ? (void)0 : __assert(__FILE__, __LINE__))
# else
#  define assert(e)	((e) ? (void)0 : __assert())
# endif
#else
#define assert(e)	((void)0)
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_ENABLE_ASSERTIONS__ */

#if PLAT_LOG_LEVEL_ASSERT >= LOG_LEVEL_VERBOSE
void __dead2 __assert(const char *file, unsigned int line,
		      const char *assertion);
#elif PLAT_LOG_LEVEL_ASSERT >= LOG_LEVEL_INFO
void __dead2 __assert(const char *file, unsigned int line);
#else
void __dead2 __assert(void);
#endif

#endif /* ASSERT_H */
