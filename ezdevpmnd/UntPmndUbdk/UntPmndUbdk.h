/**
	* \file UntPmndUbdk.h
	* SiLabs EFM8UB10 Development Kit unit (declarations)
	* \copyright (C) 2017-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef UNTPMNDUBDK_H
#define UNTPMNDUBDK_H

#include "Pmnd.h"

#include "UntPmndUbdk_vecs.h"

#include "CtrPmndUbdkChrono.h"
#include "CtrPmndUbdkDisp.h"
#include "CtrPmndUbdkImeas.h"
#include "CtrPmndUbdkState.h"

// IP include.cust --- IBEGIN
#ifdef __linux__
	#include <fcntl.h>
	#include <errno.h>
	#include <stdio.h>
	#include <string.h>
	#include <termios.h>
	#include <unistd.h>

	#include <linux/serial_core.h>
	#include <sys/ioctl.h>
#endif
// IP include.cust --- IEND

/**
	* UntPmndUbdk
	*/
class UntPmndUbdk : public UntPmnd {

public:
	static constexpr size_t sizeRxbuf = 6;
	static constexpr size_t sizeTxbuf = 7;

public:
	UntPmndUbdk();
	~UntPmndUbdk();

public:
	// IP vars.cust --- IBEGIN
	std::string path;
	unsigned int bpsRx;
	unsigned int bpsTx;

	int fd;
	// IP vars.cust --- IEND

public:
	CtrPmndUbdkChrono* chrono;
	CtrPmndUbdkDisp* disp;
	CtrPmndUbdkImeas* imeas;
	CtrPmndUbdkState* state;

public:
	void init(const std::string& _path, const unsigned int _bpsRx, const unsigned int _bpsTx); // IP init --- RLINE
	void term();

public:
	bool rx(unsigned char* buf, const size_t reqlen);
	bool tx(unsigned char* buf, const size_t reqlen);

	void flush();

public:
	uint8_t getTixVControllerBySref(const std::string& sref);
	std::string getSrefByTixVController(const uint8_t tixVController);
	void fillFeedFController(Sbecore::Feed& feed);

	uint8_t getTixWBufferBySref(const std::string& sref);
	std::string getSrefByTixWBuffer(const uint8_t tixWBuffer);
	void fillFeedFBuffer(Sbecore::Feed& feed);

	uint8_t getTixVCommandBySref(const uint8_t tixVController, const std::string& sref);
	std::string getSrefByTixVCommand(const uint8_t tixVController, const uint8_t tixVCommand);
	void fillFeedFCommand(const uint8_t tixVController, Sbecore::Feed& feed);

	Dbecore::Bufxf* getNewBufxf(const uint8_t tixWBuffer, const size_t reqlen, unsigned char* buf);
	Dbecore::Cmd* getNewCmd(const uint8_t tixVController, const uint8_t tixVCommand);

};

#endif
