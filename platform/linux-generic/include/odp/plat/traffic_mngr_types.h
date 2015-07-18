/* Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

/**
 * @file
 *
 * ODP traffic mngr
 */

#ifndef ODP_TRAFFIC_MNGR_TYPES_H_
#define ODP_TRAFFIC_MNGR_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <odp/std_types.h>
#include <odp/plat/strong_types.h>

/** @addtogroup odp_traffic_mngr
 *  Macros and operations on a TM system.
 *  @{
 */

/**> @todo Fill this in with what it's supposed to be */
#define ODP_CYCLES_PER_SEC 1000000000

/** The ODP_TM_MAX_NUM_SYSTEMS constant specifies the maximum number of TM
 * systems that may be created.  On some platforms this might be much more
 * limited to as little as one hardware TM system.
 */
#define ODP_TM_MAX_NUM_SYSTEMS   64

/** The ODP_TM_MAX_PRIORITIES constant specifies the largest range of
 * priorities that any TM system can support.  All strict priority values MUST
 * in the range 0..ODP_TM_MAX_PRIORITIES-1.
 */
#define ODP_TM_MAX_PRIORITIES  16

/** The ODP_TM MAX_LEVELS constant specifies the largest range of
 * tm_node levels that any TM system can support.  Hence all tm_node level
 * values MUST be in the range 0..ODP_TM_MAX_LEVELS-1.  Smaller tm_node
 * levels are associated with tm_nodes closer to the TM system egress.
 */
#define ODP_TM_MAX_LEVELS  8

/**
 * The smallest SCHED weight is 1 (i.e. 0 is not a legal WFQ/WRR value).
 */
#define ODP_TM_MIN_SCHED_WEIGHT  1

/** The ODP_TM_MAX_SCHED_WEIGHT constant is the largest weight any TM system
 * can support (at least from a configuration standpoint).  A given TM system
 * could have a smaller value.
 */
#define ODP_TM_MAX_SCHED_WEIGHT  255

/** The ODP_TM_MAX_TM_QUEUES constant is the largest number of tm_queues
 * that can handled by any one TM system.
 */
#define ODP_TM_MAX_TM_QUEUES  (64 * 1024 * 1024)

/** The ODP_TM_MAX_NUM_OUTPUTS constant is the largest number of outputs that
 * can be configured for any one TM system.
 */
#define ODP_TM_MAX_NUM_OUTPUTS  256

/** The ODP_TM_MAX_NUM_TM_NODES constant is the largest number of tm_nodes that
 * can be in existence for any one TM system.
 */
#define ODP_TM_MAX_NUM_TM_NODES  (1024 * 1024)

/** The ODP_TM_MAX_TM_NODE_FANIN constant is the largest number of fan-in
 * "inputs" that can be simultaneously connected to a single tm_node.
 * *TBD* Does this need to be as large as ODP_TM_MAX_TM_QUEUES? *TBD*
 */
#define ODP_TM_MAX_TM_NODE_FANIN  (1024 * 1024)

/** The ODP_TM_MIN_SHAPER_BW constant is the smallest amount of bandwidth that
 * can a shaper's peak or commit rate can be set to.  It is in units of
 * 1000 bytes/second so that it and the ODP_TM_MAX_SHAPER_BW can both fit in
 * 32 bits.
 */
#define ODP_TM_MIN_SHAPER_BW  1

/** The ODP_TM_MAX_SHAPER_BW constant is the largest amound of bandwidth that
 * any shaper's peak or commit rate can be set to.  It is in units of
 * 1000 bytes/second so that it and the ODP_TM_MIN_SHAPER_BW can both fit in
 * 32 bits.
 */
#define ODP_TM_MAX_SHAPER_BW  12500000

/** The ODP_NUM_SHAPER_COLORS constant just counts the number of enumeration
 * values defined in the odp_tm_shaper_color_t type.
 */
#define ODP_NUM_SHAPER_COLORS  3

/** The INVALID_PRIORITY constant is used when one needs to indicate an
 * invalid priority value.
 */
#define ODP_TM_INVALID_PRIORITY  255

/** The odp_tm_percent_t type is used when specifying fields that are
 * percentages.  It is a fixed point integer whose units are 1/100 of a
 * percent.  Hence 100% is represented as the integer value 10000.  Note
 * that because it is often used as a ratio of the current queue value and
 * maximum queue threshold, it can be > 100%, but in any event will never
 * be larger than 500% (i.e. it MUST be capped at 50000).
 */
typedef uint16_t odp_tm_percent_t;

/** The odp_tm_handle_t type is a generic type that can stand for any of the
 * other ODP_TM handle types.
 */
typedef uint64_t odp_tm_handle_t;

/** Each odp_tm_t value represents a specific TM system.  Almost all
 * functions in this API require a odp_tm_t value - either directly
 * as a function parameter or indirectly by having another ODP TM handle value
 * as a function parameter.
 */
typedef odp_tm_handle_t odp_tm_t;

/** Each odp_tm_queue_t value is an opaque ODP handle representing a specific
 * tm_queue within a specific TM system.
 */
typedef odp_tm_handle_t odp_tm_queue_t;

/** Each odp_tm_node_t value is an opaque ODP handle representing a specific
 * tm_node within a specific TM system.
 */
typedef odp_tm_handle_t odp_tm_node_t;

/** Each odp_tm_shaper_t value is an opaque ODP handle representing a specific
 * shaper profile usable across all TM systems described by this API.  A given
 * shaper profile can then be attached to any tm_queue or tm_node.
 */
typedef odp_tm_handle_t odp_tm_shaper_t;

/** Each odp_tm_sched_t value is an opaque ODP handle representing a specific
 * tm_node scheduler profile usable across all TM systems described by this
 * API.  A given tm_node scheduler profile can then be attached to any tm_node.
 */
typedef odp_tm_handle_t odp_tm_sched_t;

/** Each odp_tm_threshold_t value is an opaque ODP handle representing a
 * specific queue threshold profile usable across all TM systems described by
 * this API.  A given queue threshold profile can then be attached to any
 * tm_queue or tm_node.
 */
typedef odp_tm_handle_t odp_tm_threshold_t;

/** Each odp_tm_wred_t value is an opaque ODP handle representing a specific
 * WRED profile usable across all TM systems described by this API.  A given
 * WRED profile can then be attached to any tm_queue or tm_node.
 */
typedef odp_tm_handle_t odp_tm_wred_t;

/** The ODP_TM_INVALID constant can be used with any ODP TM handle type and
 * indicates that this value does NOT represent a valid TM object.
 */
#define ODP_TM_INVALID  0

/** Get printable format of odp_queue_t */
static inline uint64_t odp_tm_handle_to_u64(odp_tm_handle_t hdl)
{
	return hdl;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
