/**
	* \file Udua_exe.c
	* Pmnd main (implementation)
	* \copyright (C) 2019-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "Udua.h"

#include "Chrono.h"
#include "Disp.h"
#include "Hostif.h"
#include "Imeas.h"
#include "State.h"
#include "Uartrx.h"
#include "Uarttx.h"

bdata volatile struct Flags flags = {0};

volatile unsigned char evts0 = 0, evts1 = 0, evts2 = 0;

volatile unsigned char acts0 = 0;
volatile unsigned char snss0 = 0;

// IP cust1 --- INSERT

/******************************************************************************
 main program
 ******************************************************************************/

void init() {
	// IP init.cust --- INSERT

	chronoInit();
	dispInit();
	hostifInit();
	imeasInit();
	stateInit();
	uartrxInit();
	uarttxInit();
}

void run() {
	// after initialization, this method is invoked from isr's only

	while (1) {
		// IP run.cust --- INSERT

		if (IS_ACTIVE_CHRONO()) CLEAR_EVTS_FROM_CHRONO();
		if (IS_SENSITIVE_CHRONO()) if (!chronoRun()) if (HAVE_NO_SNSS()) if (HAVE_NO_ACTS()) break;

		if (IS_ACTIVE_DISP()) CLEAR_EVTS_FROM_DISP();
		if (IS_SENSITIVE_DISP()) if (!dispRun()) if (HAVE_NO_SNSS()) if (HAVE_NO_ACTS()) break;

		if (IS_ACTIVE_HOSTIF()) CLEAR_EVTS_FROM_HOSTIF();
		if (IS_SENSITIVE_HOSTIF()) if (!hostifRun()) if (HAVE_NO_SNSS()) if (HAVE_NO_ACTS()) break;

		if (IS_ACTIVE_IMEAS()) CLEAR_EVTS_FROM_IMEAS();
		if (IS_SENSITIVE_IMEAS()) if (!imeasRun()) if (HAVE_NO_SNSS()) if (HAVE_NO_ACTS()) break;

		if (IS_ACTIVE_STATE()) CLEAR_EVTS_FROM_STATE();
		if (IS_SENSITIVE_STATE()) if (!stateRun()) if (HAVE_NO_SNSS()) if (HAVE_NO_ACTS()) break;

		if (IS_ACTIVE_UARTRX()) CLEAR_EVTS_FROM_UARTRX();
		if (IS_SENSITIVE_UARTRX()) if (!uartrxRun()) if (HAVE_NO_SNSS()) if (HAVE_NO_ACTS()) break;

		if (IS_ACTIVE_UARTTX()) CLEAR_EVTS_FROM_UARTTX();
		if (IS_SENSITIVE_UARTTX()) if (!uarttxRun()) if (HAVE_NO_SNSS()) if (HAVE_NO_ACTS()) break;

		CLEAR_EVTS_ISR();
		if (HAVE_NO_SNSS()) if (HAVE_NO_ACTS()) break;
	};
}

// IP cust2 --- INSERT

void main(void) {
	init();

	// IP main --- INSERT

	while (1) {
		// IP main.loop --- INSERT
	};
}
