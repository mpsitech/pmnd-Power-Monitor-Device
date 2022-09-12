/**
	* \file Uarttx.c
	* Uarttx uarttx_v1_0_Mcu (implementation)
	* \copyright (C) 2019-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 26 Apr 2021
	*/
// IP header --- ABOVE

#include "Uarttx.h"

#define shrdat shrdatUarttx

/******************************************************************************
 constants and variables
 ******************************************************************************/

struct ShrdatUarttx shrdatUarttx; // IP shrdat --- LINE

enum StateOp {
	stateOpInit,
	stateOpIdle,
	stateOpSendA, stateOpSendB,
	stateOpDone
};

static enum StateOp stateOp = stateOpInit;

// IP vars.oth --- INSERT

/******************************************************************************
 initialization
 ******************************************************************************/

void uarttxInit() {
	// IP uarttxInit --- INSERT
}

/******************************************************************************
 execution
 ******************************************************************************/

bool uarttxRun() {
	// IP uarttxRun.vars --- BEGIN
	bool sns;

	static uint16_t i;
	// IP uarttxRun.vars --- END

	UNSET_SENSITIVE_UARTTX();

	// IP uarttxRun.cust1 --- INSERT

	// IP uarttxRun.op --- BEGIN
	switch (stateOp) {
		case stateOpInit:
			// IP syncrst --- INSERT

			stateOp = stateOpIdle;

			SET_SENSITIVE_UARTTX();

			break;

		case stateOpIdle:
			if (flags.reqHostifToUarttx == 1) {
				flags.ackHostifToUarttx = 1;
				SET_EVT_ackHostifToUarttx();

				if (shrdat.len == 0) {
					flags.dneHostifToUarttx = 1;
					SET_EVT_dneHostifToUarttx();

					stateOp = stateOpDone;

				} else {
					// reset transmitter
					// IP op.idle.flush --- INSERT

					i = 0;

					stateOp = stateOpSendB;

					SET_SENSITIVE_UARTTX();
				};
			};

			break;

		case stateOpSendA:
			if (false) { // IP op.sendA.trigger --- LINE

				i++;

				if (i == shrdat.len) {
					flags.dneHostifToUarttx = 1;
					SET_EVT_dneHostifToUarttx();

					stateOp = stateOpDone;

				} else {
					SET_EVT_strbUarttxD();

					stateOp = stateOpSendB;

					SET_SENSITIVE_UARTTX();
				};
			};

			break;

		case stateOpSendB:
			// copy byte to be transmitted
			// IP op.sendB.copy --- INSERT

			stateOp = stateOpSendA;

			break;

		case stateOpDone:
			if (flags.reqHostifToUarttx == 0) {
				stateOp = stateOpInit;

				SET_SENSITIVE_UARTTX();
			};

			break;
	};
	// IP uarttxRun.op --- END

	return sns;
}

/******************************************************************************
 other
 ******************************************************************************/

// IP oth --- INSERT
