/**
	* \file CtrPmndUduaState.h
	* state controller (declarations)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef CTRPMNDUDUASTATE_H
#define CTRPMNDUDUASTATE_H

#include "Pmnd.h"

#include "UntPmndUdua_vecs.h"

#define CmdPmndUduaStateGet CtrPmndUduaState::CmdGet

#define VecVPmndUduaStateCommand CtrPmndUduaState::VecVCommand

/**
	* CtrPmndUduaState
	*/
class CtrPmndUduaState : public CtrPmnd {

public:
	/**
		* VecVCommand (full: VecVPmndUduaStateCommand)
		*/
	class VecVCommand {

	public:
		static constexpr uint8_t GET = 0x00;

		static uint8_t getTix(const std::string& sref);
		static std::string getSref(const uint8_t tix);

		static void fillFeed(Sbecore::Feed& feed);
	};

public:
	CtrPmndUduaState(UntPmnd* unt);

public:
	static const uint8_t tixVController = 0x04;

public:
	static uint8_t getTixVCommandBySref(const std::string& sref);
	static std::string getSrefByTixVCommand(const uint8_t tixVCommand);
	static void fillFeedFCommand(Sbecore::Feed& feed);

	static Dbecore::Cmd* getNewCmd(const uint8_t tixVCommand);

	static Dbecore::Cmd* getNewCmdGet();
	void get(uint8_t& tixVUduaState);

};

#endif
