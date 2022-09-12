/**
	* \file CtrPmndUbdkDisp.cpp
	* disp controller (implementation)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "CtrPmndUbdkDisp.h"

using namespace std;
using namespace Sbecore;
using namespace Xmlio;
using namespace Dbecore;

/******************************************************************************
 class CtrPmndUbdkDisp::VecVCommand
 ******************************************************************************/

uint8_t CtrPmndUbdkDisp::VecVCommand::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	return(0);
};

string CtrPmndUbdkDisp::VecVCommand::getSref(
			const uint8_t tix
		) {

	return("");
};

void CtrPmndUbdkDisp::VecVCommand::fillFeed(
			Feed& feed
		) {
	feed.clear();
};

/******************************************************************************
 class CtrPmndUbdkDisp
 ******************************************************************************/

CtrPmndUbdkDisp::CtrPmndUbdkDisp(
			UntPmnd* unt
		) : CtrPmnd(unt) {
};

uint8_t CtrPmndUbdkDisp::getTixVCommandBySref(
			const string& sref
		) {
	return VecVCommand::getTix(sref);
};

string CtrPmndUbdkDisp::getSrefByTixVCommand(
			const uint8_t tixVCommand
		) {
	return VecVCommand::getSref(tixVCommand);
};

void CtrPmndUbdkDisp::fillFeedFCommand(
			Feed& feed
		) {
	VecVCommand::fillFeed(feed);
};

Cmd* CtrPmndUbdkDisp::getNewCmd(
			const uint8_t tixVCommand
		) {
	Cmd* cmd = NULL;

	return cmd;
};
