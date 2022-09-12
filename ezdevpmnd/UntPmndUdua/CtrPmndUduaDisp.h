/**
	* \file CtrPmndUduaDisp.h
	* disp controller (declarations)
	* \copyright (C) 2016-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#ifndef CTRPMNDUDUADISP_H
#define CTRPMNDUDUADISP_H

#include "Pmnd.h"

#define VecVPmndUduaDispCommand CtrPmndUduaDisp::VecVCommand

/**
	* CtrPmndUduaDisp
	*/
class CtrPmndUduaDisp : public CtrPmnd {

public:
	/**
		* VecVCommand (full: VecVPmndUduaDispCommand)
		*/
	class VecVCommand {

	public:

		static uint8_t getTix(const std::string& sref);
		static std::string getSref(const uint8_t tix);

		static void fillFeed(Sbecore::Feed& feed);
	};

public:
	CtrPmndUduaDisp(UntPmnd* unt);

public:
	static const uint8_t tixVController = 0x02;

public:
	static uint8_t getTixVCommandBySref(const std::string& sref);
	static std::string getSrefByTixVCommand(const uint8_t tixVCommand);
	static void fillFeedFCommand(Sbecore::Feed& feed);

	static Dbecore::Cmd* getNewCmd(const uint8_t tixVCommand);

};

#endif
