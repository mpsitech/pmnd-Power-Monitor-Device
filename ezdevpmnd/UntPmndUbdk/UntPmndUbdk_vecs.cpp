/**
	* \file UntPmndUbdk_vecs.cpp
	* SiLabs EFM8UB10 Development Kit unit vectors (implementation)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "UntPmndUbdk_vecs.h"

using namespace std;
using namespace Sbecore;
using namespace Xmlio;

/******************************************************************************
 namespace VecVPmndUbdkController
 ******************************************************************************/

uint8_t VecVPmndUbdkController::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "chrono") return CHRONO;
	else if (s == "disp") return DISP;
	else if (s == "imeas") return IMEAS;
	else if (s == "state") return STATE;

	return(0);
};

string VecVPmndUbdkController::getSref(
			const uint8_t tix
		) {
	if (tix == CHRONO) return("chrono");
	else if (tix == DISP) return("disp");
	else if (tix == IMEAS) return("imeas");
	else if (tix == STATE) return("state");

	return("");
};

void VecVPmndUbdkController::fillFeed(
			Feed& feed
		) {
	feed.clear();

	std::set<uint8_t> items = {CHRONO,DISP,IMEAS,STATE};

	for (auto it = items.begin(); it != items.end(); it++) feed.appendIxSrefTitles(*it, getSref(*it), getSref(*it));
};

/******************************************************************************
 namespace VecVPmndUbdkState
 ******************************************************************************/

uint8_t VecVPmndUbdkState::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "nc") return NC;
	else if (s == "ready") return READY;
	else if (s == "active") return ACTIVE;

	return(0);
};

string VecVPmndUbdkState::getSref(
			const uint8_t tix
		) {
	if (tix == NC) return("nc");
	else if (tix == READY) return("ready");
	else if (tix == ACTIVE) return("active");

	return("");
};

string VecVPmndUbdkState::getTitle(
			const uint8_t tix
		) {
	if (tix == NC) return("offline");
	else if (tix == READY) return("ready");
	else if (tix == ACTIVE) return("measurement in progress");

	return("");
};

void VecVPmndUbdkState::fillFeed(
			Feed& feed
		) {
	feed.clear();

	std::set<uint8_t> items = {NC,READY,ACTIVE};

	for (auto it = items.begin(); it != items.end(); it++) feed.appendIxSrefTitles(*it, getSref(*it), getTitle(*it));
};

/******************************************************************************
 namespace VecWPmndUbdkBuffer
 ******************************************************************************/

uint8_t VecWPmndUbdkBuffer::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "cmdrettohostif") return CMDRETTOHOSTIF;
	else if (s == "hostiftocmdinv") return HOSTIFTOCMDINV;

	return(0);
};

string VecWPmndUbdkBuffer::getSref(
			const uint8_t tix
		) {
	if (tix == CMDRETTOHOSTIF) return("cmdretToHostif");
	else if (tix == HOSTIFTOCMDINV) return("hostifToCmdinv");

	return("");
};

void VecWPmndUbdkBuffer::fillFeed(
			Feed& feed
		) {
	feed.clear();

	std::set<uint8_t> items = {CMDRETTOHOSTIF,HOSTIFTOCMDINV};

	for (auto it = items.begin(); it != items.end(); it++) feed.appendIxSrefTitles(*it, getSref(*it), getSref(*it));
};
