#!/bin/bash

VFILE="include/odp/api/version.h"

GEN=`grep "define ODP_VERSION_API_GENERATION"	${VFILE} | cut -d ' ' -f 3`
MAJ=`grep "define ODP_VERSION_API_MAJOR"	${VFILE} | cut -d ' ' -f 3`
MIN=`grep "define ODP_VERSION_API_MINOR"	${VFILE} | cut -d ' ' -f 3`

IMPL_FILE="platform/linux-generic/odp_impl.c"
IMPL=`grep "define ODP_VERSION_IMPL "		${IMPL_FILE} | cut -d ' ' -f 3`

echo -n $GEN.$MAJ.$MIN.$IMPL
