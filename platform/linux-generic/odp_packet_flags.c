/* Copyright (c) 2014, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#include <odp/packet_flags.h>
#include <odp_packet_internal.h>

#define retflag(p, x) do {			       \
	odp_packet_hdr_t *pkt_hdr = odp_packet_hdr(p); \
	if (pkt_hdr->input_flags.unparsed)	       \
		_odp_packet_parse(pkt_hdr);	       \
	return pkt_hdr->x;			       \
	} while (0)

#define setflag(p, x, v) do {			       \
	odp_packet_hdr_t *pkt_hdr = odp_packet_hdr(p); \
	if (pkt_hdr->input_flags.unparsed)	       \
		_odp_packet_parse(pkt_hdr);	       \
	pkt_hdr->x = v & 1;			       \
	} while (0)

int odp_packet_has_error(odp_packet_t pkt)
{
	odp_packet_hdr_t *pkt_hdr = odp_packet_hdr(pkt);
	if (pkt_hdr->input_flags.unparsed)
		_odp_packet_parse(pkt_hdr);
	return odp_packet_hdr(pkt)->error_flags.all != 0;
}

/* Get Input Flags */

int odp_packet_has_l2(odp_packet_t pkt)
{
	retflag(pkt, input_flags.l2);
}

int odp_packet_has_l3(odp_packet_t pkt)
{
	retflag(pkt, input_flags.l3);
}

int odp_packet_has_l4(odp_packet_t pkt)
{
	retflag(pkt, input_flags.l4);
}

int odp_packet_has_eth(odp_packet_t pkt)
{
	retflag(pkt, input_flags.eth);
}

int odp_packet_has_jumbo(odp_packet_t pkt)
{
	retflag(pkt, input_flags.jumbo);
}

int odp_packet_has_vlan(odp_packet_t pkt)
{
	retflag(pkt, input_flags.vlan);
}

int odp_packet_has_vlan_qinq(odp_packet_t pkt)
{
	retflag(pkt, input_flags.vlan_qinq);
}

int odp_packet_has_arp(odp_packet_t pkt)
{
	retflag(pkt, input_flags.arp);
}

int odp_packet_has_ipv4(odp_packet_t pkt)
{
	retflag(pkt, input_flags.ipv4);
}

int odp_packet_has_ipv6(odp_packet_t pkt)
{
	retflag(pkt, input_flags.ipv6);
}

int odp_packet_has_ipfrag(odp_packet_t pkt)
{
	retflag(pkt, input_flags.ipfrag);
}

int odp_packet_has_ipopt(odp_packet_t pkt)
{
	retflag(pkt, input_flags.ipopt);
}

int odp_packet_has_ipsec(odp_packet_t pkt)
{
	retflag(pkt, input_flags.ipsec);
}

int odp_packet_has_udp(odp_packet_t pkt)
{
	retflag(pkt, input_flags.udp);
}

int odp_packet_has_tcp(odp_packet_t pkt)
{
	retflag(pkt, input_flags.tcp);
}

int odp_packet_has_sctp(odp_packet_t pkt)
{
	retflag(pkt, input_flags.sctp);
}

int odp_packet_has_icmp(odp_packet_t pkt)
{
	retflag(pkt, input_flags.icmp);
}

int odp_packet_has_flow_hash(odp_packet_t pkt)
{
	odp_packet_hdr_t *pkt_hdr = odp_packet_hdr(pkt);

	return pkt_hdr->has_hash;
}

/* Set Input Flags */

void odp_packet_has_l2_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.l2, val);
}

void odp_packet_has_l3_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.l3, val);
}

void odp_packet_has_l4_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.l4, val);
}

void odp_packet_has_eth_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.eth, val);
}

void odp_packet_has_jumbo_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.jumbo, val);
}

void odp_packet_has_vlan_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.vlan, val);
}

void odp_packet_has_vlan_qinq_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.vlan_qinq, val);
}

void odp_packet_has_arp_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.arp, val);
}

void odp_packet_has_ipv4_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.ipv4, val);
}

void odp_packet_has_ipv6_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.ipv6, val);
}

void odp_packet_has_ipfrag_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.ipfrag, val);
}

void odp_packet_has_ipopt_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.ipopt, val);
}

void odp_packet_has_ipsec_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.ipsec, val);
}

void odp_packet_has_udp_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.udp, val);
}

void odp_packet_has_tcp_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.tcp, val);
}

void odp_packet_has_sctp_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.sctp, val);
}

void odp_packet_has_icmp_set(odp_packet_t pkt, int val)
{
	setflag(pkt, input_flags.icmp, val);
}

void odp_packet_has_flow_hash_clr(odp_packet_t pkt)
{
	odp_packet_hdr_t *pkt_hdr = odp_packet_hdr(pkt);

	pkt_hdr->has_hash = 0;
}

odp_pkt_color_t odp_packet_color(odp_packet_t pkt)
{
	retflag(pkt, input_flags.color);
}

void odp_packet_color_set(odp_packet_t pkt, odp_pkt_color_t color)
{
	odp_packet_hdr_t *pkt_hdr = odp_packet_hdr(pkt);

	if (pkt_hdr->input_flags.unparsed)
		_odp_packet_parse(pkt_hdr);

	pkt_hdr->input_flags.color = color;
}

odp_bool_t odp_packet_drop_eligible(odp_packet_t pkt)
{
	odp_packet_hdr_t *pkt_hdr = odp_packet_hdr(pkt);

	if (pkt_hdr->input_flags.unparsed)
		_odp_packet_parse(pkt_hdr);

	return !pkt_hdr->input_flags.nodrop;
}

void odp_packet_drop_eligible_set(odp_packet_t pkt, odp_bool_t drop)
{
	setflag(pkt, input_flags.nodrop, !drop);
}

int8_t odp_packet_shaper_len_adjust(odp_packet_t pkt)
{
	retflag(pkt, output_flags.shaper_len_adj);
}

void odp_packet_shaper_len_adjust_set(odp_packet_t pkt, int8_t adj)
{
	odp_packet_hdr_t *pkt_hdr = odp_packet_hdr(pkt);

	if (pkt_hdr->input_flags.unparsed)
		_odp_packet_parse(pkt_hdr);

	pkt_hdr->output_flags.shaper_len_adj = adj;
}
