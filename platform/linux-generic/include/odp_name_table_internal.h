/* Copyright 2015 EZchip Semiconductor Ltd. All Rights Reserved.
 *
 * Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ODP_INT_NAME_TABLE_H_
#define ODP_INT_NAME_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <odp.h>

typedef enum {
	ODP_COS_HANDLE,
	ODP_PKTIO_HANDLE,
	ODP_POOL_HANDLE,
	ODP_QUEUE_HANDLE,
	ODPH_RING_HANDLE,
	ODP_SHM_HANDLE,
	ODP_TIMER_POOL_HANDLE,
	ODP_TM_HANDLE,
	ODP_TM_SHAPER_PROFILE_HANDLE,
	ODP_TM_SCHED_PROFILE_HANDLE,
	ODP_TM_THRESHOLD_PROFILE_HANDLE,
	ODP_TM_WRED_PROFILE_HANDLE,
	ODP_TM_NODE_HANDLE
} odp_int_name_kind_t;

typedef uint32_t odp_int_name_t;
#define ODP_INVALID_NAME   0

#define ODP_INT_NAME_LEN 32

odp_int_name_t odp_int_name_tbl_add(char *name,
				    uint8_t     name_kind,
				    uint64_t    user_data);

odp_int_name_t odp_int_name_tbl_lookup(char *name,
				       uint8_t     name_kind);

int odp_int_name_tbl_delete(odp_int_name_t odp_name);

const char *odp_int_name_tbl_name(odp_int_name_t odp_name);

uint64_t odp_int_name_tbl_user_data(odp_int_name_t odp_name);

void odp_int_name_tbl_stats_print(void);

void odp_int_name_tbl_init(void);

#ifdef __cplusplus
}
#endif

#endif
