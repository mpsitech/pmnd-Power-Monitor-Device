/**
	* \file CtrPmndUduaChrono.h
	* chrono controller (declarations)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef CTRPMNDUDUACHRONO_H
#define CTRPMNDUDUACHRONO_H

#include "Pmnd.h"

#define CmdPmndUduaChronoGetHhst CtrPmndUduaChrono::CmdGetHhst

#define VecVPmndUduaChronoCommand CtrPmndUduaChrono::VecVCommand

/**
	* CtrPmndUduaChrono
	*/
class CtrPmndUduaChrono : public CtrPmnd {

public:
	/**
		* VecVCommand (full: VecVPmndUduaChronoCommand)
		*/
	class VecVCommand {

	public:
		static constexpr uint8_t GETHHST = 0x00;
		static constexpr uint8_t SETHHST = 0x01;

		static uint8_t getTix(const std::string& sref);
		static std::string getSref(const uint8_t tix);

		static void fillFeed(Sbecore::Feed& feed);
	};

public:
	CtrPmndUduaChrono(UntPmnd* unt);

public:
	static const uint8_t tixVController = 0x01;

public:
	static uint8_t getTixVCommandBySref(const std::string& sref);
	static std::string getSrefByTixVCommand(const uint8_t tixVCommand);
	static void fillFeedFCommand(Sbecore::Feed& feed);

	static Dbecore::Cmd* getNewCmd(const uint8_t tixVCommand);

	static Dbecore::Cmd* getNewCmdGetHhst();
	void getHhst(uint32_t& hhst);

	static Dbecore::Cmd* getNewCmdSetHhst();
	void setHhst(const uint32_t hhst);

};

#endif
