/**
	* \file UntPmndUbdk_vecs.h
	* SiLabs EFM8UB10 Development Kit unit vectors (declarations)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef UNTPMNDUBDK_VECS_H
#define UNTPMNDUBDK_VECS_H

#include <sbecore/Xmlio.h>

/**
	* VecVPmndUbdkController
	*/
namespace VecVPmndUbdkController {
	constexpr uint8_t CHRONO = 0x01;
	constexpr uint8_t DISP = 0x02;
	constexpr uint8_t IMEAS = 0x03;
	constexpr uint8_t STATE = 0x04;

	uint8_t getTix(const std::string& sref);
	std::string getSref(const uint8_t tix);

	void fillFeed(Sbecore::Feed& feed);
};

/**
	* VecVPmndUbdkState
	*/
namespace VecVPmndUbdkState {
	constexpr uint8_t NC = 0x00;
	constexpr uint8_t READY = 0x01;
	constexpr uint8_t ACTIVE = 0x02;

	uint8_t getTix(const std::string& sref);
	std::string getSref(const uint8_t tix);

	std::string getTitle(const uint8_t tix);

	void fillFeed(Sbecore::Feed& feed);
};

/**
	* VecWPmndUbdkBuffer
	*/
namespace VecWPmndUbdkBuffer {
	constexpr uint8_t CMDRETTOHOSTIF = 0x01;
	constexpr uint8_t HOSTIFTOCMDINV = 0x02;

	uint8_t getTix(const std::string& sref);
	std::string getSref(const uint8_t tix);

	void fillFeed(Sbecore::Feed& feed);
};

#endif
