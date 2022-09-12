/**
	* \file Ubdk.h
	* Ubdk global functionality (declarations)
	* \copyright (C) 2019-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef UBDK_H
#define	UBDK_H

/*
	peripherals:
		imeas: adc0
		disp: spi0 (mosi@22, sclk@24)
		chrono: tmr0
		hostif: usb0
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
	* ubdk constants
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
// IP pins --- END

/**
	* data structures and definitions for event-driven execution
	*/
// - flags
extern bdata struct Flags {
	// handshake
	unsigned char reqHostifToUsbrxtxSend:1;
	unsigned char ackHostifToUsbrxtxSend:1;
	unsigned char dneHostifToUsbrxtxSend:1;

	unsigned char reqHostifToUsbrxtxRecv:1;
	unsigned char ackHostifToUsbrxtxRecv:1;
	unsigned char dneHostifToUsbrxtxRecv:1;

	unsigned char reqInvChronoSetHhst:1;
	unsigned char ackInvChronoSetHhst:1;

	unsigned char reqInvImeasSet:1;
	unsigned char ackInvImeasSet:1;
} flags;

// - events
extern unsigned char evts0, evts1;

// interrupts

#define EVTS0_TIMER0_IRQn 0x01
#define SET_EVT_TIMER0_IRQn() \
	{evts0 |= EVTS0_TIMER0_IRQn; \
	snss0 |= SNSS0_chrono;}
#define IS_SET_EVT_TIMER0_IRQn() ((evts0 & EVTS0_TIMER0_IRQn) != 0)

// handshake

#define EVTS0_reqHostifToUsbrxtxSend 0x02
#define SET_EVT_reqHostifToUsbrxtxSend() \
	{evts0 |= EVTS0_reqHostifToUsbrxtxSend; \
	acts0 |= ACTS0_hostif; \
	snss0 |= SNSS0_usbrxtx;}
#define IS_SET_EVT_reqHostifToUsbrxtxSend() ((evts0 & EVTS0_reqHostifToUsbrxtxSend) != 0)
#define EVTS0_ackHostifToUsbrxtxSend 0x04
#define SET_EVT_ackHostifToUsbrxtxSend() \
	{evts0 |= EVTS0_ackHostifToUsbrxtxSend; \
	acts0 |= ACTS0_usbrxtx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_ackHostifToUsbrxtxSend() ((evts0 & EVTS0_ackHostifToUsbrxtxSend) != 0)
#define EVTS0_dneHostifToUsbrxtxSend 0x08
#define SET_EVT_dneHostifToUsbrxtxSend() \
	{evts0 |= EVTS0_dneHostifToUsbrxtxSend; \
	acts0 |= ACTS0_usbrxtx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_dneHostifToUsbrxtxSend() ((evts0 & EVTS0_dneHostifToUsbrxtxSend) != 0)

#define EVTS0_reqHostifToUsbrxtxRecv 0x10
#define SET_EVT_reqHostifToUsbrxtxRecv() \
	{evts0 |= EVTS0_reqHostifToUsbrxtxRecv; \
	acts0 |= ACTS0_hostif; \
	snss0 |= SNSS0_usbrxtx;}
#define IS_SET_EVT_reqHostifToUsbrxtxRecv() ((evts0 & EVTS0_reqHostifToUsbrxtxRecv) != 0)
#define EVTS0_ackHostifToUsbrxtxRecv 0x20
#define SET_EVT_ackHostifToUsbrxtxRecv() \
	{evts0 |= EVTS0_ackHostifToUsbrxtxRecv; \
	acts0 |= ACTS0_usbrxtx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_ackHostifToUsbrxtxRecv() ((evts0 & EVTS0_ackHostifToUsbrxtxRecv) != 0)
#define EVTS0_dneHostifToUsbrxtxRecv 0x40
#define SET_EVT_dneHostifToUsbrxtxRecv() \
	{evts0 |= EVTS0_dneHostifToUsbrxtxRecv; \
	acts0 |= ACTS0_usbrxtx; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_dneHostifToUsbrxtxRecv() ((evts0 & EVTS0_dneHostifToUsbrxtxRecv) != 0)

#define EVTS0_reqInvChronoSetHhst 0x80
#define SET_EVT_reqInvChronoSetHhst() \
	{evts0 |= EVTS0_reqInvChronoSetHhst; \
	acts0 |= ACTS0_hostif; \
	snss0 |= SNSS0_chrono;}
#define IS_SET_EVT_reqInvChronoSetHhst() ((evts0 & EVTS0_reqInvChronoSetHhst) != 0)
#define EVTS1_ackInvChronoSetHhst 0x01
#define SET_EVT_ackInvChronoSetHhst() \
	{evts1 |= EVTS1_ackInvChronoSetHhst; \
	acts0 |= ACTS0_chrono; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_ackInvChronoSetHhst() ((evts1 & EVTS1_ackInvChronoSetHhst) != 0)

#define EVTS1_reqInvImeasSet 0x02
#define SET_EVT_reqInvImeasSet() \
	{evts1 |= EVTS1_reqInvImeasSet; \
	acts0 |= ACTS0_hostif; \
	snss0 |= SNSS0_imeas;}
#define IS_SET_EVT_reqInvImeasSet() ((evts1 & EVTS1_reqInvImeasSet) != 0)
#define EVTS1_ackInvImeasSet 0x04
#define SET_EVT_ackInvImeasSet() \
	{evts1 |= EVTS1_ackInvImeasSet; \
	acts0 |= ACTS0_imeas; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_ackInvImeasSet() ((evts1 & EVTS1_ackInvImeasSet) != 0)

// strobes including statsng command shared data updates

#define EVTS1_chronoGetHhst 0x08
#define SET_EVT_chronoGetHhst() \
	{evts1 |= EVTS1_chronoGetHhst; \
	acts0 |= ACTS0_chrono; \
	snss0 |= SNSS0_hostif;}
#define IS_SET_EVT_chronoGetHhst() ((evts1 & EVTS1_chronoGetHhst) != 0)
#define EVTS1_imeasGet 0x10
#define SET_EVT_imeasGet() \
	{evts1 |= EVTS1_imeasGet; \
	acts0 |= ACTS0_imeas;}
#define IS_SET_EVT_imeasGet() ((evts1 & EVTS1_imeasGet) != 0)
#define EVTS1_stateGet 0x20
#define SET_EVT_stateGet() \
	{evts1 |= EVTS1_stateGet; \
	acts0 |= ACTS0_state;}
#define IS_SET_EVT_stateGet() ((evts1 & EVTS1_stateGet) != 0)

#define HAVE_NO_EVTS() ((evts0 | evts1) == 0)

#define CLEAR_EVTS_ISR() \
	evts0 &= ~(EVTS0_TIMER0_IRQn);

#define CLEAR_EVTS_FROM_CHRONO() \
	evts1 &= ~(EVTS1_ackInvChronoSetHhst | EVTS1_chronoGetHhst); \
	acts0 &= ~ACTS0_chrono;

#define HAVE_EVTS_FOR_CHRONO() (( \
		(evts0 & (EVTS0_TIMER0_IRQn | EVTS0_reqInvChronoSetHhst)) \
	!= 0))

#define CLEAR_EVTS_FROM_DISP() \
	acts0 &= ~ACTS0_disp;

#define HAVE_EVTS_FOR_DISP() ((false))

#define CLEAR_EVTS_FROM_HOSTIF() \
	evts0 &= ~(EVTS0_reqHostifToUsbrxtxSend | EVTS0_reqHostifToUsbrxtxRecv | EVTS0_reqInvChronoSetHhst); \
	evts1 &= ~(EVTS1_reqInvImeasSet); \
	acts0 &= ~ACTS0_hostif;

#define HAVE_EVTS_FOR_HOSTIF() (( \
		(evts0 & (EVTS0_ackHostifToUsbrxtxSend | EVTS0_dneHostifToUsbrxtxSend | EVTS0_ackHostifToUsbrxtxRecv | EVTS0_dneHostifToUsbrxtxRecv)) \
		| (evts1 & (EVTS1_ackInvChronoSetHhst | EVTS1_ackInvImeasSet | EVTS1_chronoGetHhst)) \
	!= 0))

#define CLEAR_EVTS_FROM_IMEAS() \
	evts1 &= ~(EVTS1_ackInvImeasSet | EVTS1_imeasGet); \
	acts0 &= ~ACTS0_imeas;

#define HAVE_EVTS_FOR_IMEAS() (( \
		(evts1 & (EVTS1_reqInvImeasSet)) \
	!= 0))

#define CLEAR_EVTS_FROM_STATE() \
	evts1 &= ~(EVTS1_stateGet); \
	acts0 &= ~ACTS0_state;

#define HAVE_EVTS_FOR_STATE() ((false))

#define CLEAR_EVTS_FROM_USBRXTX() \
	evts0 &= ~(EVTS0_ackHostifToUsbrxtxSend | EVTS0_dneHostifToUsbrxtxSend | EVTS0_ackHostifToUsbrxtxRecv | EVTS0_dneHostifToUsbrxtxRecv); \
	acts0 &= ~ACTS0_usbrxtx;

#define HAVE_EVTS_FOR_USBRXTX() (( \
		(evts0 & (EVTS0_reqHostifToUsbrxtxSend | EVTS0_reqHostifToUsbrxtxRecv)) \
	!= 0))

// - activities
extern unsigned char acts0;

#define ACTS0_chrono 0x01
#define ACTS0_disp 0x02
#define ACTS0_hostif 0x04
#define ACTS0_imeas 0x08
#define ACTS0_state 0x10
#define ACTS0_usbrxtx 0x20

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

#define SET_ACTIVE_USBRXTX() acts0 |= ACTS0_usbrxtx;
#define UNSET_ACTIVE_USBRXTX() acts0 &= ~ACTS0_usbrxtx;
#define IS_ACTIVE_USBRXTX() ((acts0 & ACTS0_usbrxtx) != 0)

// - sensitivities
extern unsigned char snss0;

#define SNSS0_chrono 0x01
#define SNSS0_disp 0x02
#define SNSS0_hostif 0x04
#define SNSS0_imeas 0x08
#define SNSS0_state 0x10
#define SNSS0_usbrxtx 0x20

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

#define SET_SENSITIVE_USBRXTX() snss0 |= SNSS0_usbrxtx; sns = true;
#define UNSET_SENSITIVE_USBRXTX() snss0 &= ~SNSS0_usbrxtx; sns = false;
#define IS_SENSITIVE_USBRXTX() ((snss0 & SNSS0_usbrxtx) != 0)

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
	uint8_t getTixVUbdkState;

	// IP ShrdatState.cust --- INSERT
} shrdatState;

/**
	* usbrxtx module
	*/

// IP usbrxtx.cust --- INSERT

extern struct ShrdatUsbrxtx { // IP ShrdatUsbrxtx --- LINE
	uint16_t len;
	unsigned char* ptrBuf;

	// IP ShrdatUsbrxtx.cust --- INSERT
} shrdatUsbrxtx;

#endif
