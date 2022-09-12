/**
	* \file Udua.h
	* Udua global functionality (declarations)
	* \copyright (C) 2019-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef UDUA_H
#define	UDUA_H

/*
	peripherals:
		imeas: adc0
		disp: spi0 (mosi@22, sclk@24)
		chrono: tmr0
		uartrx: tmr1
		uartrx, uarttx: uart1
	input pins:
		(none)
	output pins:
		disp: dispen@11, dispcs@1
		state: ledr@18, ledg@17, ledb@16
*/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// IP include.cust --- INSERT

// IP define.cust --- INSERT

/**
	* dbecore constants
	*/
#define FLS8 0xAA
#define TRU8 0x55

#define IXOPBUF_buffer 0
#define IXOPBUF_controller 1
#define IXOPBUF_command 2
#define IXOPBUF_length 3
#define IXOPBUF_crc 5

/**
	* udua constants
	*/
#define VECVCONTROLLER_chrono 0x01
#define VECVCONTROLLER_disp 0x02
#define VECVCONTROLLER_imeas 0x03
#define VECVCONTROLLER_state 0x04

#define VECVSTATE_nc 0x00
#define VECVSTATE_ready 0x01
#define VECVSTATE_active 0x02

#define VECWBUFFER_cmdretToHostif 0x01
#define VECWBUFFER_hostifToCmdinv 0x02

#define VECVCHRONOCOMMAND_getHhst 0x00
#define VECVCHRONOCOMMAND_setHhst 0x01

#define VECVIMEASCOMMAND_set 0x00
#define VECVIMEASCOMMAND_get 0x01

#define VECVSTATECOMMAND_get 0x00

/**
	* global constants
	*/
// IP define.gbl --- INSERT

/**
	* global functionality
	*/
// IP gbl --- INSERT

/**
	* pin declarations
	*/
// IP pins --- BEGIN
sbit ADCVS = SFR_P0^0;
sbit DISPCS = SFR_P0^1;
sbit SCLK = SFR_P0^6;
sbit LEDB = SFR_P1^6;
sbit LEDG = SFR_P1^5;
sbit LEDR = SFR_P1^4;
sbit MOSI = SFR_P1^0;
sbit DISPEN = SFR_P2^3;
sbit RXD = SFR_P2^2;
sbit TXD = SFR_P2^1;
// IP pins --- END

/**
	* data structures and definitions for event-driven execution
	*/
// - flags
extern bdata struct Flags {
	// handshake
	unsigned char reqHostifToUartrx:1;

	unsigned char reqHostifToUarttx:1;

	unsigned char ackHostifToUartrx:1;

	unsigned char ackHostifToUarttx:1;

	unsigned char dneHostifToUartrx:1;

	unsigned char dneHostifToUarttx:1;

	unsigned char reqInvChronoSetHhst:1;
	unsigned char ackInvChronoSetHhst:1;

	unsigned char reqInvImeasSet:1;
	unsigned char ackInvImeasSet:1;
} flags;

// - events
extern unsigned char evts0, evts1, evts2;

// interrupts

#define EVTS0_TIMER0_IRQn 0x01
#define SET_EVT_TIMER0_IRQn() \
	{evts0 |= EVTS0_TIMER0_IRQn; \
	snss0 |= SNSS0_chrono;}
#define IS_SET_EVT_TIMER0_IRQn() ((evts0 & EVTS0_TIMER0_IRQn) != 0)

#define EVTS0_UART1_IRQn 0x02
#define SET_EVT_UART1_IRQn() \
	{evts0 |= EVTS0_UART1_IRQn; \
	snss0 |= SNSS0_uartrx; \
	snss0 |= SNSS0_uarttx;}
#define IS_SET_EVT_UART1_IRQn() ((evts0 & EVTS0_UART1_IRQn) != 0)

// handshake

#define EVTS0_reqHostifToUartrx 0x04
#define SET_EVT_reqHostifToUartrx() \
	{evts0 |= EVTS0_reqHostifToUartrx; \
	acts0 |= ACTS0_hostif; \
	snss0 |= SNSS0_uartrx;}
#define IS_SET_EVT_reqHostifToUartrx() ((evts0 & EVTS0_reqHostifToUartrx) != 0)

#define EVTS0_reqHostifToUarttx 0x08
#define SET_EVT_reqHostifToUarttx() \
	{evts0 |= EVTS0_reqHostifToUarttx; \
	acts0 |= ACTS0_hostif; \
	snss0 |= SNSS0_uarttx;}
#define IS_SET_EVT_reqHostifToUarttx() ((evts0 & EVTS0_reqHostifToUarttx) != 0)

#define EVTS0_ackHostifToUartrx 0x10
#define SET_EVT_ackHostifToUartrx() \
	{evts0 |= EVTS0_ackHostifToUartrx; \
	acts0 |= ACTS0_uartrx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_ackHostifToUartrx() ((evts0 & EVTS0_ackHostifToUartrx) != 0)

#define EVTS0_ackHostifToUarttx 0x20
#define SET_EVT_ackHostifToUarttx() \
	{evts0 |= EVTS0_ackHostifToUarttx; \
	acts0 |= ACTS0_uarttx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_ackHostifToUarttx() ((evts0 & EVTS0_ackHostifToUarttx) != 0)

#define EVTS0_dneHostifToUartrx 0x40
#define SET_EVT_dneHostifToUartrx() \
	{evts0 |= EVTS0_dneHostifToUartrx; \
	acts0 |= ACTS0_uartrx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_dneHostifToUartrx() ((evts0 & EVTS0_dneHostifToUartrx) != 0)

#define EVTS0_dneHostifToUarttx 0x80
#define SET_EVT_dneHostifToUarttx() \
	{evts0 |= EVTS0_dneHostifToUarttx; \
	acts0 |= ACTS0_uarttx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_dneHostifToUarttx() ((evts0 & EVTS0_dneHostifToUarttx) != 0)

#define EVTS1_reqInvChronoSetHhst 0x01
#define SET_EVT_reqInvChronoSetHhst() \
	{evts1 |= EVTS1_reqInvChronoSetHhst; \
	acts0 |= ACTS0_hostif; \
	snss0 |= SNSS0_chrono;}
#define IS_SET_EVT_reqInvChronoSetHhst() ((evts1 & EVTS1_reqInvChronoSetHhst) != 0)
#define EVTS1_ackInvChronoSetHhst 0x02
#define SET_EVT_ackInvChronoSetHhst() \
	{evts1 |= EVTS1_ackInvChronoSetHhst; \
	acts0 |= ACTS0_chrono; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_ackInvChronoSetHhst() ((evts1 & EVTS1_ackInvChronoSetHhst) != 0)

#define EVTS1_reqInvImeasSet 0x04
#define SET_EVT_reqInvImeasSet() \
	{evts1 |= EVTS1_reqInvImeasSet; \
	acts0 |= ACTS0_hostif; \
	snss0 |= SNSS0_imeas;}
#define IS_SET_EVT_reqInvImeasSet() ((evts1 & EVTS1_reqInvImeasSet) != 0)
#define EVTS1_ackInvImeasSet 0x08
#define SET_EVT_ackInvImeasSet() \
	{evts1 |= EVTS1_ackInvImeasSet; \
	acts0 |= ACTS0_imeas; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_ackInvImeasSet() ((evts1 & EVTS1_ackInvImeasSet) != 0)

// strobes including statsng command shared data updates

#define EVTS1_strbUartrxD 0x10
#define SET_EVT_strbUartrxD() \
	{evts1 |= EVTS1_strbUartrxD; \
	acts0 |= ACTS0_uartrx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_strbUartrxD() ((evts1 & EVTS1_strbUartrxD) != 0)
#define EVTS1_strbUarttxD 0x20
#define SET_EVT_strbUarttxD() \
	{evts1 |= EVTS1_strbUarttxD; \
	acts0 |= ACTS0_uarttx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_strbUarttxD() ((evts1 & EVTS1_strbUarttxD) != 0)
#define EVTS1_chronoGetHhst 0x40
#define SET_EVT_chronoGetHhst() \
	{evts1 |= EVTS1_chronoGetHhst; \
	acts0 |= ACTS0_chrono; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_chronoGetHhst() ((evts1 & EVTS1_chronoGetHhst) != 0)
#define EVTS1_imeasGet 0x80
#define SET_EVT_imeasGet() \
	{evts1 |= EVTS1_imeasGet; \
	acts0 |= ACTS0_imeas;}
#define IS_SET_EVT_imeasGet() ((evts1 & EVTS1_imeasGet) != 0)
#define EVTS2_stateGet 0x01
#define SET_EVT_stateGet() \
	{evts2 |= EVTS2_stateGet; \
	acts0 |= ACTS0_state;}
#define IS_SET_EVT_stateGet() ((evts2 & EVTS2_stateGet) != 0)

#define HAVE_NO_EVTS() ((evts0 | evts1 | evts2) == 0)

#define CLEAR_EVTS_ISR() \
	evts0 &= ~(EVTS0_TIMER0_IRQn | EVTS0_UART1_IRQn);

#define CLEAR_EVTS_FROM_CHRONO() \
	evts1 &= ~(EVTS1_ackInvChronoSetHhst | EVTS1_chronoGetHhst); \
	acts0 &= ~ACTS0_chrono;

#define HAVE_EVTS_FOR_CHRONO() (( \
		(evts0 & (EVTS0_TIMER0_IRQn)) \
		| (evts1 & (EVTS1_reqInvChronoSetHhst)) \
	!= 0))

#define CLEAR_EVTS_FROM_DISP() \
	acts0 &= ~ACTS0_disp;

#define HAVE_EVTS_FOR_DISP() ((false))

#define CLEAR_EVTS_FROM_HOSTIF() \
	evts0 &= ~(EVTS0_reqHostifToUartrx | EVTS0_reqHostifToUarttx); \
	evts1 &= ~(EVTS1_reqInvChronoSetHhst | EVTS1_reqInvImeasSet); \
	acts0 &= ~ACTS0_hostif;

#define HAVE_EVTS_FOR_HOSTIF() (( \
		(evts0 & (EVTS0_ackHostifToUartrx | EVTS0_ackHostifToUarttx | EVTS0_dneHostifToUartrx | EVTS0_dneHostifToUarttx)) \
		| (evts1 & (EVTS1_ackInvChronoSetHhst | EVTS1_ackInvImeasSet | EVTS1_strbUartrxD | EVTS1_strbUarttxD | EVTS1_chronoGetHhst)) \
	!= 0))

#define CLEAR_EVTS_FROM_IMEAS() \
	evts1 &= ~(EVTS1_ackInvImeasSet | EVTS1_imeasGet); \
	acts0 &= ~ACTS0_imeas;

#define HAVE_EVTS_FOR_IMEAS() (( \
		(evts1 & (EVTS1_reqInvImeasSet)) \
	!= 0))

#define CLEAR_EVTS_FROM_STATE() \
	evts2 &= ~(EVTS2_stateGet); \
	acts0 &= ~ACTS0_state;

#define HAVE_EVTS_FOR_STATE() ((false))

#define CLEAR_EVTS_FROM_UARTRX() \
	evts0 &= ~(EVTS0_ackHostifToUartrx | EVTS0_dneHostifToUartrx); \
	evts1 &= ~(EVTS1_strbUartrxD); \
	acts0 &= ~ACTS0_uartrx;

#define HAVE_EVTS_FOR_UARTRX() (( \
		(evts0 & (EVTS0_UART1_IRQn | EVTS0_reqHostifToUartrx)) \
	!= 0))

#define CLEAR_EVTS_FROM_UARTTX() \
	evts0 &= ~(EVTS0_ackHostifToUarttx | EVTS0_dneHostifToUarttx); \
	evts1 &= ~(EVTS1_strbUarttxD); \
	acts0 &= ~ACTS0_uarttx;

#define HAVE_EVTS_FOR_UARTTX() (( \
		(evts0 & (EVTS0_UART1_IRQn | EVTS0_reqHostifToUarttx)) \
	!= 0))

// - activities
extern unsigned char acts0;

#define ACTS0_chrono 0x01
#define ACTS0_disp 0x02
#define ACTS0_hostif 0x04
#define ACTS0_imeas 0x08
#define ACTS0_state 0x10
#define ACTS0_uartrx 0x20
#define ACTS0_uarttx 0x40

#define HAVE_NO_ACTS() ((acts0) == 0)

#define SET_ACTIVE_CHRONO() acts0 |= ACTS0_chrono;
#define UNSET_ACTIVE_CHRONO() acts0 &= ~ACTS0_chrono;
#define IS_ACTIVE_CHRONO() ((acts0 & ACTS0_chrono) != 0)

#define SET_ACTIVE_DISP() acts0 |= ACTS0_disp;
#define UNSET_ACTIVE_DISP() acts0 &= ~ACTS0_disp;
#define IS_ACTIVE_DISP() ((acts0 & ACTS0_disp) != 0)

#define SET_ACTIVE_HOSTIF() acts0 |= ACTS0_hostif;
#define UNSET_ACTIVE_HOSTIF() acts0 &= ~ACTS0_hostif;
#define IS_ACTIVE_HOSTIF() ((acts0 & ACTS0_hostif) != 0)

#define SET_ACTIVE_IMEAS() acts0 |= ACTS0_imeas;
#define UNSET_ACTIVE_IMEAS() acts0 &= ~ACTS0_imeas;
#define IS_ACTIVE_IMEAS() ((acts0 & ACTS0_imeas) != 0)

#define SET_ACTIVE_STATE() acts0 |= ACTS0_state;
#define UNSET_ACTIVE_STATE() acts0 &= ~ACTS0_state;
#define IS_ACTIVE_STATE() ((acts0 & ACTS0_state) != 0)

#define SET_ACTIVE_UARTRX() acts0 |= ACTS0_uartrx;
#define UNSET_ACTIVE_UARTRX() acts0 &= ~ACTS0_uartrx;
#define IS_ACTIVE_UARTRX() ((acts0 & ACTS0_uartrx) != 0)

#define SET_ACTIVE_UARTTX() acts0 |= ACTS0_uarttx;
#define UNSET_ACTIVE_UARTTX() acts0 &= ~ACTS0_uarttx;
#define IS_ACTIVE_UARTTX() ((acts0 & ACTS0_uarttx) != 0)

// - sensitivities
extern unsigned char snss0;

#define SNSS0_chrono 0x01
#define SNSS0_disp 0x02
#define SNSS0_hostif 0x04
#define SNSS0_imeas 0x08
#define SNSS0_state 0x10
#define SNSS0_uartrx 0x20
#define SNSS0_uarttx 0x40

#define HAVE_NO_SNSS() ((snss0) == 0)

#define SET_SENSITIVE_CHRONO() snss0 |= SNSS0_chrono; sns = true;
#define UNSET_SENSITIVE_CHRONO() snss0 &= ~SNSS0_chrono; sns = false;
#define IS_SENSITIVE_CHRONO() ((snss0 & SNSS0_chrono) != 0)

#define SET_SENSITIVE_DISP() snss0 |= SNSS0_disp; sns = true;
#define UNSET_SENSITIVE_DISP() snss0 &= ~SNSS0_disp; sns = false;
#define IS_SENSITIVE_DISP() ((snss0 & SNSS0_disp) != 0)

#define SET_SENSITIVE_HOSTIF() snss0 |= SNSS0_hostif; sns = true;
#define UNSET_SENSITIVE_HOSTIF() snss0 &= ~SNSS0_hostif; sns = false;
#define IS_SENSITIVE_HOSTIF() ((snss0 & SNSS0_hostif) != 0)

#define SET_SENSITIVE_IMEAS() snss0 |= SNSS0_imeas; sns = true;
#define UNSET_SENSITIVE_IMEAS() snss0 &= ~SNSS0_imeas; sns = false;
#define IS_SENSITIVE_IMEAS() ((snss0 & SNSS0_imeas) != 0)

#define SET_SENSITIVE_STATE() snss0 |= SNSS0_state; sns = true;
#define UNSET_SENSITIVE_STATE() snss0 &= ~SNSS0_state; sns = false;
#define IS_SENSITIVE_STATE() ((snss0 & SNSS0_state) != 0)

#define SET_SENSITIVE_UARTRX() snss0 |= SNSS0_uartrx; sns = true;
#define UNSET_SENSITIVE_UARTRX() snss0 &= ~SNSS0_uartrx; sns = false;
#define IS_SENSITIVE_UARTRX() ((snss0 & SNSS0_uartrx) != 0)

#define SET_SENSITIVE_UARTTX() snss0 |= SNSS0_uarttx; sns = true;
#define UNSET_SENSITIVE_UARTTX() snss0 &= ~SNSS0_uarttx; sns = false;
#define IS_SENSITIVE_UARTTX() ((snss0 & SNSS0_uarttx) != 0)

/**
	* chrono controller
	*/

// IP chrono.cust --- INSERT

extern struct ShrdatChrono { // IP ShrdatChrono --- LINE
	uint32_t getHhstHhst;

	// IP ShrdatChrono.cust --- INSERT
} shrdatChrono;

/**
	* disp controller
	*/

// IP disp.cust --- INSERT

extern struct ShrdatDisp { // IP ShrdatDisp --- LINE
	uint8_t dummy; // IP ShrdatDisp.cust --- LINE
} shrdatDisp;

/**
	* hostif module
	*/

// IP hostif.cust --- INSERT

extern struct ShrdatHostif { // IP ShrdatHostif --- LINE
	unsigned char rxbuf[7];

	// IP ShrdatHostif.cust --- INSERT
} shrdatHostif;

/**
	* imeas controller
	*/

// IP imeas.cust --- INSERT

extern struct ShrdatImeas { // IP ShrdatImeas --- LINE
	uint16_t getVs;

	// IP ShrdatImeas.cust --- INSERT
} shrdatImeas;

/**
	* state controller
	*/

// IP state.cust --- INSERT

extern struct ShrdatState { // IP ShrdatState --- LINE
	uint8_t getTixVUduaState;

	// IP ShrdatState.cust --- INSERT
} shrdatState;

/**
	* uartrx module
	*/

// IP uartrx.cust --- INSERT

extern struct ShrdatUartrx { // IP ShrdatUartrx --- LINE
	uint16_t len;
	uint8_t d;

	// IP ShrdatUartrx.cust --- INSERT
} shrdatUartrx;

/**
	* uarttx module
	*/

// IP uarttx.cust --- INSERT

extern struct ShrdatUarttx { // IP ShrdatUarttx --- LINE
	uint16_t len;
	uint8_t d;

	// IP ShrdatUarttx.cust --- INSERT
} shrdatUarttx;

#endif
