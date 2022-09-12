/**
	* \file CtrPmndUbdkState.cpp
	* state controller (implementation)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "CtrPmndUbdkState.h"

using namespace std;
using namespace Sbecore;
using namespace Xmlio;
using namespace Dbecore;

/******************************************************************************
 class CtrPmndUbdkState::VecVCommand
 ******************************************************************************/

uint8_t CtrPmndUbdkState::VecVCommand::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "get") return GET;

	return(0);
};

string CtrPmndUbdkState::VecVCommand::getSref(
			const uint8_t tix
		) {
	if (tix == GET) return("get");

	return("");
};

void CtrPmndUbdkState::VecVCommand::fillFeed(
			Feed& feed
		) {
	feed.clear();

	std::set<uint8_t> items = {GET};

	for (auto it = items.begin(); it != items.end(); it++) feed.appendIxSrefTitles(*it, getSref(*it), getSref(*it));
};

/******************************************************************************
 class CtrPmndUbdkState
 ******************************************************************************/

CtrPmndUbdkState::CtrPmndUbdkState(
			UntPmnd* unt
		) : CtrPmnd(unt) {
};

uint8_t CtrPmndUbdkState::getTixVCommandBySref(
			const string& sref
		) {
	return VecVCommand::getTix(sref);
};

string CtrPmndUbdkState::getSrefByTixVCommand(
			const uint8_t tixVCommand
		) {
	return VecVCommand::getSref(tixVCommand);
};

void CtrPmndUbdkState::fillFeedFCommand(
			Feed& feed
		) {
	VecVCommand::fillFeed(feed);
};

Cmd* CtrPmndUbdkState::getNewCmd(
			const uint8_t tixVCommand
		) {
	Cmd* cmd = NULL;

	if (tixVCommand == VecVCommand::GET) cmd = getNewCmdGet();

	return cmd;
};

Cmd* CtrPmndUbdkState::getNewCmdGet() {
	Cmd* cmd = new Cmd(0x04, VecVCommand::GET, Cmd::VecVRettype::STATSNG);

	cmd->addParRet("tixVUbdkState", Par::VecVType::TIX, VecVPmndUbdkState::getTix, VecVPmndUbdkState::getSref, VecVPmndUbdkState::fillFeed);

	return cmd;
};

void CtrPmndUbdkState::get(
			uint8_t& tixVUbdkState
		) {
	Cmd* cmd = getNewCmdGet();

	if (unt->runCmd(cmd)) {
		tixVUbdkState = cmd->parsRet["tixVUbdkState"].getTix();
	} else {
		delete cmd;
		throw DbeException("error running get");
	};

	delete cmd;
};
