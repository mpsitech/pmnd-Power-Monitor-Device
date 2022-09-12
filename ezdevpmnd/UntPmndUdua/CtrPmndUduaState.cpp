/**
	* \file CtrPmndUduaState.cpp
	* state controller (implementation)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "CtrPmndUduaState.h"

using namespace std;
using namespace Sbecore;
using namespace Xmlio;
using namespace Dbecore;

/******************************************************************************
 class CtrPmndUduaState::VecVCommand
 ******************************************************************************/

uint8_t CtrPmndUduaState::VecVCommand::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "get") return GET;

	return(0);
};

string CtrPmndUduaState::VecVCommand::getSref(
			const uint8_t tix
		) {
	if (tix == GET) return("get");

	return("");
};

void CtrPmndUduaState::VecVCommand::fillFeed(
			Feed& feed
		) {
	feed.clear();

	std::set<uint8_t> items = {GET};

	for (auto it = items.begin(); it != items.end(); it++) feed.appendIxSrefTitles(*it, getSref(*it), getSref(*it));
};

/******************************************************************************
 class CtrPmndUduaState
 ******************************************************************************/

CtrPmndUduaState::CtrPmndUduaState(
			UntPmnd* unt
		) : CtrPmnd(unt) {
};

uint8_t CtrPmndUduaState::getTixVCommandBySref(
			const string& sref
		) {
	return VecVCommand::getTix(sref);
};

string CtrPmndUduaState::getSrefByTixVCommand(
			const uint8_t tixVCommand
		) {
	return VecVCommand::getSref(tixVCommand);
};

void CtrPmndUduaState::fillFeedFCommand(
			Feed& feed
		) {
	VecVCommand::fillFeed(feed);
};

Cmd* CtrPmndUduaState::getNewCmd(
			const uint8_t tixVCommand
		) {
	Cmd* cmd = NULL;

	if (tixVCommand == VecVCommand::GET) cmd = getNewCmdGet();

	return cmd;
};

Cmd* CtrPmndUduaState::getNewCmdGet() {
	Cmd* cmd = new Cmd(0x04, VecVCommand::GET, Cmd::VecVRettype::STATSNG);

	cmd->addParRet("tixVUduaState", Par::VecVType::TIX, VecVPmndUduaState::getTix, VecVPmndUduaState::getSref, VecVPmndUduaState::fillFeed);

	return cmd;
};

void CtrPmndUduaState::get(
			uint8_t& tixVUduaState
		) {
	Cmd* cmd = getNewCmdGet();

	if (unt->runCmd(cmd)) {
		tixVUduaState = cmd->parsRet["tixVUduaState"].getTix();
	} else {
		delete cmd;
		throw DbeException("error running get");
	};

	delete cmd;
};
