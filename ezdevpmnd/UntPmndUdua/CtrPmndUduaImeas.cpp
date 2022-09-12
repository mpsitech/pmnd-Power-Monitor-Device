/**
	* \file CtrPmndUduaImeas.cpp
	* imeas controller (implementation)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "CtrPmndUduaImeas.h"

using namespace std;
using namespace Sbecore;
using namespace Xmlio;
using namespace Dbecore;

/******************************************************************************
 class CtrPmndUduaImeas::VecVCommand
 ******************************************************************************/

uint8_t CtrPmndUduaImeas::VecVCommand::getTix(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "set") return SET;
	else if (s == "get") return GET;

	return(0);
};

string CtrPmndUduaImeas::VecVCommand::getSref(
			const uint8_t tix
		) {
	if (tix == SET) return("set");
	else if (tix == GET) return("get");

	return("");
};

void CtrPmndUduaImeas::VecVCommand::fillFeed(
			Feed& feed
		) {
	feed.clear();

	std::set<uint8_t> items = {SET,GET};

	for (auto it = items.begin(); it != items.end(); it++) feed.appendIxSrefTitles(*it, getSref(*it), getSref(*it));
};

/******************************************************************************
 class CtrPmndUduaImeas
 ******************************************************************************/

CtrPmndUduaImeas::CtrPmndUduaImeas(
			UntPmnd* unt
		) : CtrPmnd(unt) {
};

uint8_t CtrPmndUduaImeas::getTixVCommandBySref(
			const string& sref
		) {
	return VecVCommand::getTix(sref);
};

string CtrPmndUduaImeas::getSrefByTixVCommand(
			const uint8_t tixVCommand
		) {
	return VecVCommand::getSref(tixVCommand);
};

void CtrPmndUduaImeas::fillFeedFCommand(
			Feed& feed
		) {
	VecVCommand::fillFeed(feed);
};

Cmd* CtrPmndUduaImeas::getNewCmd(
			const uint8_t tixVCommand
		) {
	Cmd* cmd = NULL;

	if (tixVCommand == VecVCommand::SET) cmd = getNewCmdSet();
	else if (tixVCommand == VecVCommand::GET) cmd = getNewCmdGet();

	return cmd;
};

Cmd* CtrPmndUduaImeas::getNewCmdSet() {
	Cmd* cmd = new Cmd(0x03, VecVCommand::SET, Cmd::VecVRettype::VOID);

	cmd->addParInv("fir", Par::VecVType::UINT8);

	return cmd;
};

void CtrPmndUduaImeas::set(
			const uint8_t fir
		) {
	Cmd* cmd = getNewCmdSet();

	cmd->parsInv["fir"].setUint8(fir);

	if (unt->runCmd(cmd)) {
	} else {
		delete cmd;
		throw DbeException("error running set");
	};

	delete cmd;
};

Cmd* CtrPmndUduaImeas::getNewCmdGet() {
	Cmd* cmd = new Cmd(0x03, VecVCommand::GET, Cmd::VecVRettype::STATSNG);

	cmd->addParRet("Vs", Par::VecVType::UINT16);

	return cmd;
};

void CtrPmndUduaImeas::get(
			uint16_t& Vs
		) {
	Cmd* cmd = getNewCmdGet();

	if (unt->runCmd(cmd)) {
		Vs = cmd->parsRet["Vs"].getUint16();
	} else {
		delete cmd;
		throw DbeException("error running get");
	};

	delete cmd;
};
