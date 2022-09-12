/**
	* \file CtrPmndUduaImeas.h
	* imeas controller (declarations)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef CTRPMNDUDUAIMEAS_H
#define CTRPMNDUDUAIMEAS_H

#include "Pmnd.h"

#define CmdPmndUduaImeasGet CtrPmndUduaImeas::CmdGet

#define VecVPmndUduaImeasCommand CtrPmndUduaImeas::VecVCommand

/**
	* CtrPmndUduaImeas
	*/
class CtrPmndUduaImeas : public CtrPmnd {

public:
	/**
		* VecVCommand (full: VecVPmndUduaImeasCommand)
		*/
	class VecVCommand {

	public:
		static constexpr uint8_t SET = 0x00;
		static constexpr uint8_t GET = 0x01;

		static uint8_t getTix(const std::string& sref);
		static std::string getSref(const uint8_t tix);

		static void fillFeed(Sbecore::Feed& feed);
	};

public:
	CtrPmndUduaImeas(UntPmnd* unt);

public:
	static const uint8_t tixVController = 0x03;

public:
	static uint8_t getTixVCommandBySref(const std::string& sref);
	static std::string getSrefByTixVCommand(const uint8_t tixVCommand);
	static void fillFeedFCommand(Sbecore::Feed& feed);

	static Dbecore::Cmd* getNewCmd(const uint8_t tixVCommand);

	static Dbecore::Cmd* getNewCmdSet();
	void set(const uint8_t fir);

	static Dbecore::Cmd* getNewCmdGet();
	void get(uint16_t& Vs);

};

#endif
