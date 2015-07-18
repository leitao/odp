/* Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/**
 * @file
 *
 * ODP packet descriptor
 */

#ifndef ODP_PACKET_TYPES_H_
#define ODP_PACKET_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <odp/std_types.h>
#include <odp/plat/strong_types.h>

/** @addtogroup odp_packet ODP PACKET
 *  Operations on a packet.
 *  @{
 */

typedef ODP_HANDLE_T(odp_packet_t);

#define ODP_PACKET_INVALID _odp_cast_scalar(odp_packet_t, 0xffffffff)

#define ODP_PACKET_OFFSET_INVALID (0x0fffffff)

typedef ODP_HANDLE_T(odp_packet_seg_t);

#define ODP_PACKET_SEG_INVALID _odp_cast_scalar(odp_packet_seg_t, 0xffffffff)

/** odp_pkt_color_t assigns names to the various pkt "colors" */
typedef enum {
	PKT_GREEN = 0,
	PKT_YELLOW = 1,
	PKT_RED = 2,
	PKT_ALL_COLORS = 3,
} odp_pkt_color_t;

/** Sets the maximum number of pkt "colors" */
#define ODP_NUM_PKT_COLORS 3

/** Get printable format of odp_packet_t */
static inline uint64_t odp_packet_to_u64(odp_packet_t hdl)
{
	return _odp_pri(hdl);
}

/** Get printable format of odp_packet_seg_t */
static inline uint64_t odp_packet_seg_to_u64(odp_packet_seg_t hdl)
{
	return _odp_pri(hdl);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
