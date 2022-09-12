/**
	* \file Hostif.c
	* Hostif uarthostif_Easy_v1_1_Mcu easy model host interface (implementation)
	* \copyright (C) 2019-2021 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 26 Apr 2021
	*/
// IP header --- ABOVE

#include "Hostif.h"

#define shrdat shrdatHostif

/******************************************************************************
 constants and variables
 ******************************************************************************/

struct ShrdatHostif shrdatHostif; // IP shrdat --- LINE

// --- main operation (op)
enum StateOp {
	stateOpInit,
	stateOpIdle,
	stateOpRxopA, stateOpRxopB, stateOpRxopC,
	stateOpVoidinv,
	stateOpTxA, stateOpTxB, stateOpTxC,
	stateOpRxA, stateOpRxB, stateOpRxC,
	stateOpInv,
	stateOpTxackA, stateOpTxackB
};

static enum StateOp stateOp = stateOpInit;

/******************************************************************************
 initialization
 ******************************************************************************/

void hostifInit() {
	// IP hostifInit --- INSERT
}

/******************************************************************************
 execution
 ******************************************************************************/

bool hostifRun() {
	// IP hostifRun.vars --- BEGIN
	bool sns;

	static const int sizeOpbuf = 7;
	static uint8_t opbuf[7];

	static uint8_t txbuf[6];

	static uint32_t hhstLast;
	static const uint8_t deltaHhst = 2; // 20ms timeout

	static uint16_t crc;
	static uint16_t i, icrc;
	// IP hostifRun.vars --- END

	UNSET_SENSITIVE_HOSTIF();

	// IP hostifRun.cust1 --- INSERT

	// IP hostifRun.op --- BEGIN
	switch (stateOp) {
		case stateOpInit:
			// IP syncrst --- BEGIN
			flags.reqHostifToUartrx = 0;
			SET_EVT_reqHostifToUartrx();
			flags.reqHostifToUarttx = 0;
			SET_EVT_reqHostifToUarttx();
			flags.reqInvChronoSetHhst = 0;
			SET_EVT_reqInvChronoSetHhst();
			flags.reqInvImeasSet = 0;
			SET_EVT_reqInvImeasSet();
			// IP syncrst --- END

			stateOp = stateOpIdle;

			SET_SENSITIVE_HOSTIF();

			break;

		case stateOpIdle:
			if (flags.ackHostifToUartrx == 0) {
				shrdatUartrx.len = sizeOpbuf;

				flags.reqHostifToUartrx = 1;
				SET_EVT_reqHostifToUartrx();
				
				stateOp = stateOpRxopA;
			};

			break;

		case stateOpRxopA:
			if (flags.ackHostifToUartrx == 1) {
				crcReset(&crc);

				i = 0;

				stateOp = stateOpRxopB;
			};

			break;

		case stateOpRxopB:
			if (IS_SET_EVT_strbUartrxD()) {
				opbuf[i] = shrdatUartrx.d;
				
				crcIncludeByte(&crc, shrdatUartrx.d);
				
				if ((i == 0) && (shrdatUartrx.d == 0xFF)) {
					// IP op.rxopB.reset --- BEGIN
					stateOp = stateOpInit;

					SET_SENSITIVE_HOSTIF();
					// IP op.rxopB.reset --- END
				};

				hhstLast = shrdatChrono.getHhstHhst;

				i++;

			} else if (flags.dneHostifToUartrx == 1) {
				flags.reqHostifToUartrx = 0;
				SET_EVT_reqHostifToUartrx();
				
				crcFinalize(&crc, false);
				
				if (crc == 0x0000) stateOp = stateOpRxopC;
				else stateOp = stateOpIdle;

			} else if ((i != 0) && IS_SET_EVT_chronoGetHhst() && ((shrdatChrono.getHhstHhst - hhstLast) >= deltaHhst)) {
				stateOp = stateOpInit;

				SET_SENSITIVE_HOSTIF();
			};

			break;

		case stateOpRxopC:
			stateOp = stateOpIdle; // default

			if (opbuf[IXOPBUF_buffer] == VECWBUFFER_cmdretToHostif) {
				if ((opbuf[IXOPBUF_controller] == VECVCONTROLLER_chrono) && (opbuf[IXOPBUF_command] == VECVCHRONOCOMMAND_getHhst)) {
					memcpy(txbuf, (unsigned char*) &shrdatChrono.getHhstHhst, 5);
					stateOp = stateOpTxA;
				} else if ((opbuf[IXOPBUF_controller] == VECVCONTROLLER_imeas) && (opbuf[IXOPBUF_command] == VECVIMEASCOMMAND_get)) {
					memcpy(txbuf, (unsigned char*) &shrdatImeas.getVs, 3);
					stateOp = stateOpTxA;
				} else if ((opbuf[IXOPBUF_controller] == VECVCONTROLLER_state) && (opbuf[IXOPBUF_command] == VECVSTATECOMMAND_get)) {
					memcpy(txbuf, (unsigned char*) &shrdatState.getTixVUduaState, 2);
					stateOp = stateOpTxA;
				};

			} else if (opbuf[IXOPBUF_buffer] == VECWBUFFER_hostifToCmdinv) {
				// return type: void
				shrdatUartrx.len = (opbuf[IXOPBUF_length] << 8) + opbuf[IXOPBUF_length+1]; // 2 bytes of CRC included

				stateOp = stateOpRxA;

			};

			SET_SENSITIVE_HOSTIF();
			
			break;

		case stateOpVoidinv:

			break;
			
		case stateOpTxA:
			shrdatUarttx.len = (opbuf[IXOPBUF_length] << 8) + opbuf[IXOPBUF_length+1];
			icrc = shrdatUarttx.len - 2;

			i = 0;
			shrdatUarttx.d = txbuf[i];

			crcReset(&crc);
			crcIncludeByte(&crc, txbuf[i]);

			flags.reqHostifToUarttx = 1;
			SET_EVT_reqHostifToUarttx();

			stateOp = stateOpTxB;

			break;

		case stateOpTxB:
			if (IS_SET_EVT_strbUarttxD()) {
				i++;
				
				if (i == icrc) {
					crcFinalize(&crc, true);
					shrdatUarttx.d = ((uint8_t*) &crc)[0];

					stateOp = stateOpTxC;

				} else {
					shrdatUarttx.d = txbuf[i];
					crcIncludeByte(&crc, txbuf[i]);
				};
			};
			
			break;

		case stateOpTxC:
			if (IS_SET_EVT_strbUarttxD()) {
				shrdatUarttx.d = ((uint8_t*) &crc)[1];

			} else if (flags.dneHostifToUarttx == 1) {
				stateOp = stateOpInit;

				SET_SENSITIVE_HOSTIF();
			};

			break;

		case stateOpRxA:
			if (flags.ackHostifToUartrx == 0) {
				flags.reqHostifToUartrx = 1;
				SET_EVT_reqHostifToUartrx();

				crcReset(&crc);

				i = 0;

				stateOp = stateOpRxB;
			};

			break;

		case stateOpRxB:
			if (flags.ackHostifToUartrx == 1) {
				hhstLast = shrdatChrono.getHhstHhst;

				stateOp = stateOpRxC;
			};

			break;

		case stateOpRxC:
			if (IS_SET_EVT_strbUartrxD()) {
				shrdat.rxbuf[i] = shrdatUartrx.d;
				
				crcIncludeByte(&crc, shrdatUartrx.d);

				hhstLast = shrdatChrono.getHhstHhst;

				i++;

			} else if (flags.dneHostifToUartrx == 1) {
				flags.reqHostifToUartrx = 0;
				SET_EVT_reqHostifToUartrx();

				crcFinalize(&crc, false);

				if (crc == 0x0000) stateOp = stateOpRxD;
				else stateOp = stateOpIdle;

				SET_SENSITIVE_HOSTIF();

			} else if (IS_SET_EVT_chronoGetHhst() && ((shrdatChrono.getHhstHhst - hhstLast) >= deltaHhst)) {
				stateOp = stateOpInit;

				SET_SENSITIVE_HOSTIF();
			};

			break;

		case stateOpRxD:
			stateOp = stateOpIdle; // default

			if ((opbuf[IXOPBUF_controller] == VECVCONTROLLER_chrono) && (opbuf[IXOPBUF_command] == VECVCHRONOCOMMAND_setHhst)) {
				flags.reqInvChronoSetHhst = 1;
				SET_EVT_reqInvChronoSetHhst();
				stateOp = stateOpInv;
			} else if ((opbuf[IXOPBUF_controller] == VECVCONTROLLER_imeas) && (opbuf[IXOPBUF_command] == VECVIMEASCOMMAND_set)) {
				flags.reqInvImeasSet = 1;
				SET_EVT_reqInvImeasSet();
				stateOp = stateOpInv;
			};
			
			break;

		case stateOpInv:
			if (flags.ackInvChronoSetHhst == 1) {
				flags.reqInvChronoSetHhst = 0;
				SET_EVT_reqInvChronoSetHhst();
				stateOp = stateOpTxackA;
			} else if (flags.ackInvImeasSet == 1) {
				flags.reqInvImeasSet = 0;
				SET_EVT_reqInvImeasSet();
				stateOp = stateOpTxackA;
			};

			break;

		case stateOpTxackA:
			if (flags.ackHostifToUarttx == 0) {
				shrdatUarttx.len = 2;
				shrdatUarttx.d = 0xAA;

				flags.reqHostifToUarttx = 1;
				SET_EVT_reqHostifToUarttx();

				stateOp = stateOpTxackB;
			};

			break;

		case stateOpTxackB:
			if (flags.dneHostifToUarttx == 1) {
				stateOp = stateOpInit;

				SET_SENSITIVE_HOSTIF();
			};

			break;
	};
	// IP hostifRun.op --- END

	// IP hostifRun.cust2 --- INSERT

	return sns;
}

/******************************************************************************
 other
 ******************************************************************************/

// IP oth --- INSERT
