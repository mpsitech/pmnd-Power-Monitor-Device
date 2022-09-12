/**
	* \file Imeas.c
	* Imeas easy model controller (implementation)
	* \copyright (C) 2019-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "Imeas.h"

#define IXRXBUF_setFir 0

#define shrdat shrdatImeas

// IP define.cust --- INSERT

/******************************************************************************
 constants and variables
 ******************************************************************************/

struct ShrdatImeas shrdatImeas = {0}; // IP shrdat --- LINE

// IP vars.oth --- INSERT

/******************************************************************************
 initialization
 ******************************************************************************/

void imeasInit() {
	// IP init --- INSERT
}

/******************************************************************************
 execution
 ******************************************************************************/

bool imeasRun() {
	bool sns;

	// IP run.cust1 --- INSERT
	
	UNSET_SENSITIVE_IMEAS();

	// IP run.cust2 --- INSERT
	
	return sns;
}

/******************************************************************************
 other
 ******************************************************************************/

// IP oth --- INSERT
