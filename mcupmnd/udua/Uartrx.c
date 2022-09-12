/**
	* \file Uartrx.c
	* Uartrx uartrx_v1_0_Mcu (implementation)
	* \copyright (C) 2019-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 26 Apr 2021
	*/
// IP header --- ABOVE

#include "Uartrx.h"

#define shrdat shrdatUartrx

/******************************************************************************
 constants and variables
 ******************************************************************************/

struct ShrdatUartrx shrdatUartrx; // IP shrdat --- LINE

enum StateOp {
	stateOpInit,
	stateOpIdle,
	stateOpRecv,
	stateOpDone
};

static enum StateOp stateOp = stateOpInit;

/******************************************************************************
 initialization
 ******************************************************************************/

void uartrxInit() {
	// IP uartrxInit --- INSERT
}

/******************************************************************************
 execution
 ******************************************************************************/

bool uartrxRun() {
	// IP uartrxRun.vars --- BEGIN
	bool sns;

	static uint16_t i;
	// IP uartrxRun.vars --- END

	UNSET_SENSITIVE_UARTRX();

	// IP uartrxRun.cust1 --- INSERT

	if ((flags.reqHostifToUartrx == 0) && (stateOp != stateOpInit) && (stateOp != stateOpIdle)) {
		// cancel reception, e.g. due to timeout but also regular termination in stateOpDone
		// IP uartrxRun.cancel --- INSERT

		stateOp = stateOpInit;
	};

	// IP uartrxRun.op --- BEGIN
	switch (stateOp) {
		case stateOpInit:
			// IP syncrst --- INSERT

			stateOp = stateOpIdle;

			SET_SENSITIVE_UARTRX();

			break;

		case stateOpIdle:
			if (flags.reqHostifToUartrx == 1) {
				flags.ackHostifToUartrx = 1;
				SET_EVT_ackHostifToUartrx();

				if (shrdat.len == 0) {
					flags.dneHostifToUartrx = 1;
					SET_EVT_dneHostifToUartrx();

					stateOp = stateOpDone;

				} else {
					// enable receiver
					// IP op.idle.start --- INSERT

					i = 0;

					stateOp = stateOpRecv;
				};
			};

			break;

		case stateOpRecv:
			if (false) { // IP op.recv.trigger --- LINE
				// copy received byte
				// IP op.recv.copy --- INSERT

				i++;

				SET_EVT_strbUartrxD();

				if (i == shrdat.len) {
					// stop receiver
					// IP op.recv.stop --- INSERT

					flags.dneHostifToUartrx = 1;
					SET_EVT_dneHostifToUartrx();

					stateOp = stateOpDone;
				};
			};

			break;

		//case stateOpDone:
		//	break;
	};
	// IP uartrxRun.op --- END

	// IP uartrxRun.cust2 --- INSERT

	return sns;
}

/******************************************************************************
 other
 ******************************************************************************/

// IP oth --- INSERT
