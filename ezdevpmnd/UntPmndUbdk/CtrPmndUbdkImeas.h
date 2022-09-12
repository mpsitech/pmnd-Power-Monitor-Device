/**
	* \file CtrPmndUbdkImeas.h
	* imeas controller (declarations)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef CTRPMNDUBDKIMEAS_H
#define CTRPMNDUBDKIMEAS_H

#include "Pmnd.h"

#define CmdPmndUbdkImeasGet CtrPmndUbdkImeas::CmdGet

#define VecVPmndUbdkImeasCommand CtrPmndUbdkImeas::VecVCommand

/**
	* CtrPmndUbdkImeas
	*/
class CtrPmndUbdkImeas : public CtrPmnd {

public:
	/**
		* VecVCommand (full: VecVPmndUbdkImeasCommand)
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
	CtrPmndUbdkImeas(UntPmnd* unt);

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
