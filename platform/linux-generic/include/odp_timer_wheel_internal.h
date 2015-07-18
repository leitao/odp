/* Copyright 2015 EZchip Semiconductor Ltd. All Rights Reserved.
 *
 * Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ODP_INT_TIMER_WHEEL_H_
#define ODP_INT_TIMER_WHEEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <odp.h>

/* Note that ALL times in this API are in units of processor/cpu clock
 * cycles!
 */
typedef uint64_t odp_timer_wheel_t;

#define ODP_INT_TIMER_WHEEL_INVALID  0

odp_timer_wheel_t odp_timer_wheel_create(uint32_t max_concurrent_timers,
					 uint64_t current_time);

/* odp_int_timer_wheel_curr_time_update should be called before the first
 * call to odp_int_timer_wheel_insert, odp_int_timer_wheel_next, etc..
 * It returns > 0 if there are timers expired.
 *
 */
uint32_t odp_timer_wheel_curr_time_update(odp_timer_wheel_t timer_wheel,
					  uint64_t          current_time);

/* Maximum wakeup_time is 100 seconds in the future (though a wakeup time
 * greater than a dozen seconds or so is of questionable value), and in
 * addition the wakeup_time MUST represent a time in the future.  Note that
 * the user_ptr cannot be NULL and must be aligned to an 4-byte boundary
 * (i.e. the bottom 2 bits of this ptr must be 0).  AGAIN THIS MUST BE
 * STRESSED - user_ptr is not an arbitrary 64-bit pointer, BUT MUST be
 * non-zero and have its bottom two bits being 0!
 */
int odp_timer_wheel_insert(odp_timer_wheel_t timer_wheel,
			   uint64_t          wakeup_time,
			   void             *user_ptr);

/* Returns the exact same user_ptr value as was passed to
 * odp_int_timer_wheel_insert().
 */
void *odp_timer_wheel_next_expired(odp_timer_wheel_t timer_wheel);

void odp_timer_wheel_stats_print(odp_timer_wheel_t timer_wheel);

void odp_timer_wheel_destroy(odp_timer_wheel_t timer_wheel);

#ifdef __cplusplus
}
#endif

#endif
