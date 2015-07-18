/* Copyright 2015 EZchip Semiconductor Ltd. All Rights Reserved.
 *
 * Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ODP_INT_PKT_QUEUE_H_
#define ODP_INT_PKT_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <odp.h>

typedef uint64_t odp_int_queue_pool_t;
typedef uint32_t odp_int_pkt_queue_t;

#define ODP_INT_QUEUE_POOL_INVALID  0
#define ODP_INT_PKT_QUEUE_INVALID   0

/* None of the functions in this file do any locking.  Thats because the
 * expected usage model is that each TM system will create its own
 * odp_int_queue_pool, and then only call odp_int_pkt_queue_append and
 * odp_int_pkt_queue_remove from a single thread associated/dedicated to this
 * same TM system/odp_int_queue_pool.  The main difficulty that this file
 * tries to deal with is the possibility of a huge number of queues (e.g. 16
 * million), where each such queue could have a huge range in the number of
 * pkts queued (say 0 to > 1,000) - yet the total "peak" number of pkts queued
 * is many orders of magnitude smaller than the product of max_num_queues
 * times max_queue_cnt.  In particular, it is assumed that even at peak usage,
 * only a small fraction of max_num_queues will be "active" - i.e. have any
 * pkts queued, yet over time it is expected that most every queue will have
 * some sort of backlog.
 */

/* max_num_queues must be <= 16 * 1024 * 1024. */
odp_int_queue_pool_t odp_queue_pool_create(uint32_t max_num_queues,
					   uint32_t max_queued_pkts);

odp_int_pkt_queue_t odp_pkt_queue_create(odp_int_queue_pool_t queue_pool);

int odp_pkt_queue_append(odp_int_queue_pool_t queue_pool,
			 odp_int_pkt_queue_t  pkt_queue,
			 odp_packet_t         pkt);

int odp_pkt_queue_remove(odp_int_queue_pool_t queue_pool,
			 odp_int_pkt_queue_t  pkt_queue,
			 odp_packet_t        *pkt);

void odp_pkt_queue_stats_print(odp_int_queue_pool_t queue_pool);

void odp_queue_pool_destroy(odp_int_queue_pool_t queue_pool);

#ifdef __cplusplus
}
#endif

#endif
