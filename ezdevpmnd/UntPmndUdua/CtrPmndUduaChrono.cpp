/**
	* \file CtrPmndUduaChrono.cpp
	* chrono controller (implementation)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "CtrPmndUduaChrono.h"

using namespace std;
using namespace Sbecore;
using namespace Xmlio;
using namespace Dbecore;

/******************************************************************************
 class CtrPmndUduaChrono::VecVCommand
 ******************************************************************************/

uint8_t CtrPmndUduaChrono::VecVCommand::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "gethhst") return GETHHST;
	else if (s == "sethhst") return SETHHST;

	return(0);
};

string CtrPmndUduaChrono::VecVCommand::getSref(
			const uint8_t tix
		) {
	if (tix == GETHHST) return("getHhst");
	else if (tix == SETHHST) return("setHhst");

	return("");
};

void CtrPmndUduaChrono::VecVCommand::fillFeed(
			Feed& feed
		) {
	feed.clear();

	std::set<uint8_t> items = {GETHHST,SETHHST};

	for (auto it = items.begin(); it != items.end(); it++) feed.appendIxSrefTitles(*it, getSref(*it), getSref(*it));
};

/******************************************************************************
 class CtrPmndUduaChrono
 ******************************************************************************/

CtrPmndUduaChrono::CtrPmndUduaChrono(
			UntPmnd* unt
		) : CtrPmnd(unt) {
};

uint8_t CtrPmndUduaChrono::getTixVCommandBySref(
			const string& sref
		) {
	return VecVCommand::getTix(sref);
};

string CtrPmndUduaChrono::getSrefByTixVCommand(
			const uint8_t tixVCommand
		) {
	return VecVCommand::getSref(tixVCommand);
};

void CtrPmndUduaChrono::fillFeedFCommand(
			Feed& feed
		) {
	VecVCommand::fillFeed(feed);
};

Cmd* CtrPmndUduaChrono::getNewCmd(
			const uint8_t tixVCommand
		) {
	Cmd* cmd = NULL;

	if (tixVCommand == VecVCommand::GETHHST) cmd = getNewCmdGetHhst();
	else if (tixVCommand == VecVCommand::SETHHST) cmd = getNewCmdSetHhst();

	return cmd;
};

Cmd* CtrPmndUduaChrono::getNewCmdGetHhst() {
	Cmd* cmd = new Cmd(0x01, VecVCommand::GETHHST, Cmd::VecVRettype::STATSNG);

	cmd->addParRet("hhst", Par::VecVType::UINT32);

	return cmd;
};

void CtrPmndUduaChrono::getHhst(
			uint32_t& hhst
		) {
	Cmd* cmd = getNewCmdGetHhst();

	if (unt->runCmd(cmd)) {
		hhst = cmd->parsRet["hhst"].getUint32();
	} else {
		delete cmd;
		throw DbeException("error running getHhst");
	};

	delete cmd;
};

Cmd* CtrPmndUduaChrono::getNewCmdSetHhst() {
	Cmd* cmd = new Cmd(0x01, VecVCommand::SETHHST, Cmd::VecVRettype::VOID);

	cmd->addParInv("hhst", Par::VecVType::UINT32);

	return cmd;
};

void CtrPmndUduaChrono::setHhst(
			const uint32_t hhst
		) {
	Cmd* cmd = getNewCmdSetHhst();

	cmd->parsInv["hhst"].setUint32(hhst);

	if (unt->runCmd(cmd)) {
	} else {
		delete cmd;
		throw DbeException("error running setHhst");
	};

	delete cmd;
};
