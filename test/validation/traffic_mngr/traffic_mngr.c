/* Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:	BSD-3-Clause
 */

#include <odp.h>
#include "odp_cunit_common.h"
#include "traffic_mngr.h"

static void traffic_mngr_test_lookup_info_print(void)
{
	/* dummy stub */
}

#define _CU_TEST_INFO(test_func) {#test_func, test_func}

static CU_TestInfo traffic_mngr_suite[] = {
	_CU_TEST_INFO(traffic_mngr_test_lookup_info_print),
	CU_TEST_INFO_NULL,
};

static CU_SuiteInfo traffic_mngr_suites[] = {
	{ .pName = "traffic_mngr tests",
			.pTests = traffic_mngr_suite,
	},
	CU_SUITE_INFO_NULL,
};

int traffic_mngr_main(void)
{
	return odp_cunit_run(traffic_mngr_suites);
}
