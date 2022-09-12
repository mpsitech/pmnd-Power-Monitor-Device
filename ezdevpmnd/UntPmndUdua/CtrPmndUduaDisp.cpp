/**
	* \file CtrPmndUduaDisp.cpp
	* disp controller (implementation)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "CtrPmndUduaDisp.h"

using namespace std;
using namespace Sbecore;
using namespace Xmlio;
using namespace Dbecore;

/******************************************************************************
 class CtrPmndUduaDisp::VecVCommand
 ******************************************************************************/

uint8_t CtrPmndUduaDisp::VecVCommand::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	return(0);
};

string CtrPmndUduaDisp::VecVCommand::getSref(
			const uint8_t tix
		) {

	return("");
};

void CtrPmndUduaDisp::VecVCommand::fillFeed(
			Feed& feed
		) {
	feed.clear();
};

/******************************************************************************
 class CtrPmndUduaDisp
 ******************************************************************************/

CtrPmndUduaDisp::CtrPmndUduaDisp(
			UntPmnd* unt
		) : CtrPmnd(unt) {
};

uint8_t CtrPmndUduaDisp::getTixVCommandBySref(
			const string& sref
		) {
	return VecVCommand::getTix(sref);
};

string CtrPmndUduaDisp::getSrefByTixVCommand(
			const uint8_t tixVCommand
		) {
	return VecVCommand::getSref(tixVCommand);
};

void CtrPmndUduaDisp::fillFeedFCommand(
			Feed& feed
		) {
	VecVCommand::fillFeed(feed);
};

Cmd* CtrPmndUduaDisp::getNewCmd(
			const uint8_t tixVCommand
		) {
	Cmd* cmd = NULL;

	return cmd;
};
