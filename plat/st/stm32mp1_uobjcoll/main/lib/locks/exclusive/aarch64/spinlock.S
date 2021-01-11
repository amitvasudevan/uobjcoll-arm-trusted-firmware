/*
 * Copyright (c) 2013-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/arch/asm_macros.S>

	.globl	spin_lock
	.globl	spin_unlock

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_USE_SPINLOCK_CAS__
#if !ARM_ARCH_AT_LEAST(8, 1)
#error __UBERSPARK_UOBJCOLL_CONFIGDEF_USE_SPINLOCK_CAS__ option requires at least an ARMv8.1 platform
#endif

/*
 * When compiled for ARMv8.1 or later, choose spin locks based on Compare and
 * Swap instruction.
 */

/*
 * Acquire lock using Compare and Swap instruction.
 *
 * Compare for 0 with acquire semantics, and swap 1. If failed to acquire, use
 * load exclusive semantics to monitor the address and enter WFE.
 *
 * void spin_lock(spinlock_t *lock);
 */
func spin_lock
	mov	w2, #1
1:	mov	w1, wzr
2:	casa	w1, w2, [x0]
	cbz	w1, 3f
	ldxr	w1, [x0]
	cbz	w1, 2b
	wfe
	b	1b
3:
	ret
endfunc spin_lock

#else /* !__UBERSPARK_UOBJCOLL_CONFIGDEF_USE_SPINLOCK_CAS__ */

/*
 * Acquire lock using load-/store-exclusive instruction pair.
 *
 * void spin_lock(spinlock_t *lock);
 */
func spin_lock
	mov	w2, #1
	sevl
l1:	wfe
l2:	ldaxr	w1, [x0]
	cbnz	w1, l1
	stxr	w1, w2, [x0]
	cbnz	w1, l2
	ret
endfunc spin_lock

#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_USE_SPINLOCK_CAS__ */

/*
 * Release lock previously acquired by spin_lock.
 *
 * Use store-release to unconditionally clear the spinlock variable.
 * Store operation generates an event to all cores waiting in WFE
 * when address is monitored by the global monitor.
 *
 * void spin_unlock(spinlock_t *lock);
 */
func spin_unlock
	stlr	wzr, [x0]
	ret
endfunc spin_unlock
