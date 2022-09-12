/**
	* \file UntPmndUbdk.cpp
	* SiLabs EFM8UB10 Development Kit unit (implementation)
	* \copyright (C) 2017-2020 MPSI Technologies GmbH
	* \author Alexander Wirthmueller (auto-generation)
	* \date created: 28 May 2022
	*/
// IP header --- ABOVE

#include "UntPmndUbdk.h"

using namespace std;
using namespace Sbecore;
using namespace Xmlio;
using namespace Dbecore;

UntPmndUbdk::UntPmndUbdk() : UntPmnd() {
	// IP constructor --- IBEGIN
	bpsRx = 0;
	bpsTx = 0;

	fd = 0;
	// IP constructor --- IEND
};

UntPmndUbdk::~UntPmndUbdk() {
	if (initdone) term();
};

// IP init.hdr --- RBEGIN
void UntPmndUbdk::init(
			const string& _path
			, const unsigned int _bpsRx
			, const unsigned int _bpsTx
		) {
// IP init.hdr --- REND
	chrono = new CtrPmndUbdkChrono(this);
	disp = new CtrPmndUbdkDisp(this);
	imeas = new CtrPmndUbdkImeas(this);
	state = new CtrPmndUbdkState(this);

	// IP init.cust --- IBEGIN
	path = _path;
	bpsRx = _bpsRx;
	bpsTx = _bpsTx;

	NRetry = 3;
	timeoutRx = 25000; // in us; used in rx read() regardless of device configuration
	timeoutRxWord = (10 * 1000000) / bpsRx; // 10 bits per word

	const size_t sizeRxbuf = 1024;
	rxbuf = new unsigned char[sizeRxbuf];

	const size_t sizeTxbuf = 1024;
	txbuf = new unsigned char[sizeTxbuf];

#ifdef __linux__
	// open character device
	fd = open(path.c_str(), O_RDWR | O_NOCTTY);
	if (fd == -1) {
		fd = 0;
		throw DbeException("error opening device " + path + "");
	};

	speed_t speed;

	termios term;
	serial_struct ss;

	memset(&term, 0, sizeof(term));
	if (tcgetattr(fd, &term) != 0) throw DbeException("error getting terminal attributes");

	// 8N1, no flow control, read blocking with 100ms timeout
	cfmakeraw(&term);

	switch (bpsRx) { // ignore bpsTx
		case 300: speed = B300; break;
		case 600: speed = B600; break;
		case 1200: speed = B1200; break;
		case 2400: speed = B2400; break;
		case 4800: speed = B4800; break;
		case 9600: speed = B9600; break;
		case 19200: speed = B19200; break;
		case 57600: speed = B57600; break;
		case 115200: speed = B115200; break;
		default: speed = B38400; // used in FTDI driver for higher baud rates
	};

	cfsetispeed(&term, speed);
	cfsetospeed(&term, speed);

	term.c_iflag = 0;
	term.c_oflag = 0;

	term.c_cflag &= ~(CRTSCTS | CSIZE | CSTOPB);
	term.c_cflag |= (CLOCAL | CREAD | CS8);

	//term.c_lflag = 0;

	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 1;

	tcflush(fd, TCIOFLUSH);
	if (tcsetattr(fd, TCSANOW, &term) != 0) throw DbeException("error setting terminal attributes");

	if (speed == B38400) {
		if (ioctl(fd, TIOCGSERIAL, &ss) == -1) throw DbeException("error getting serial struct");

		//cout << "ss.baud_base=" << ss.baud_base << endl; // should be 60'000'000

		ss.flags &= ~ASYNC_SPD_MASK;
		ss.flags |= ASYNC_SPD_CUST;

		int div = ss.baud_base / bpsRx; // down to 12 or up to 5MHz works
		ss.custom_divisor = div; // set to 10Mbps or 1MByte/s ; for 640*480*14/8=537.6kByte/s FLIR => more than 1 image per second

		if (ioctl(fd, TIOCSSERIAL, &ss) == -1) throw DbeException("error setting serial struct");
	};
#endif
	// IP init.cust --- IEND

	initdone = true;
};

void UntPmndUbdk::term() {
	// IP term.cust --- IBEGIN
#ifdef __linux__
	if (fd) {
		close(fd);
		fd = 0;
	};
#endif
	// IP term.cust --- IEND

	delete chrono;
	delete disp;
	delete imeas;
	delete state;

	initdone = false;
};

bool UntPmndUbdk::rx(
			unsigned char* buf
			, const size_t reqlen
		) {
	bool retval = (reqlen == 0);

	// requirement: receive data from device observing history / rxtxdump settings

	// IP rx --- IBEGIN
#ifdef __linux__
	if (reqlen != 0) {
		fd_set fds;

		timeval timeout, timeout_save;

		int s;

		size_t nleft;
		int n;

		int en;

		string msg;

		FD_ZERO(&fds);
		FD_SET(fd, &fds);

		timeout_save.tv_sec = (timeoutRx + timeoutRxWord * reqlen) / 1000000;
		timeout_save.tv_usec = (timeoutRx + timeoutRxWord * reqlen) % 1000000; // timeout includes the transfer itself!

		if (rxtxdump) {
			if (!histNotDump) cout << "rx ";
			else appendToHist("rx ");
		};

		nleft = reqlen;
		en = 0;

		while (nleft > 0) {
			timeout = timeout_save;
			s = select(fd+1, &fds, NULL, NULL, &timeout);

			if (s > 0) {
				n = read(fd, &(buf[reqlen-nleft]), nleft);
				if (n >= 0) nleft -= n;
				else {
					en = errno;
					break;
				};

			} else if (s == 0) {
				en = ETIMEDOUT;
				break;

			} else {
				en = errno;
			};
		};

		retval = (nleft == 0);

		if (rxtxdump) {
			if (nleft == 0) msg = "0x" + Dbe::bufToHex(buf, reqlen, true);
			else msg = string(strerror(en));
			
			if (!histNotDump) cout << msg << endl;
			else appendToLastInHist(msg);
		};
	};
#endif
	// IP rx --- IEND

	return retval;
};

bool UntPmndUbdk::tx(
			unsigned char* buf
			, const size_t reqlen
		) {
	bool retval = (reqlen == 0);

	// requirement: transmit data to device observing history / rxtxdump settings

	// IP tx --- IBEGIN
	timespec deltat;

#ifdef __linux__
	if (reqlen != 0) {
		size_t nleft;
		int n;

		string msg;

		if (rxtxdump) {
			if (!histNotDump) cout << "tx ";
			else appendToHist("tx ");
		};

		nleft = reqlen;
		n = 0;

		while (nleft > 0) {
			n = write(fd, &(buf[reqlen-nleft]), nleft);

			if (n >= 0) nleft -= n;
			else break;
		};

		retval = (nleft == 0);

		if (nleft == 0) {
			// write() is non-blocking but on hw level ongoing at this stage; make sure subsequent rx() doesn't time out
			deltat.tv_sec = 0;
			deltat.tv_nsec = ((long) 1000000000) * 10 * reqlen / bpsTx;

			nanosleep(&deltat, NULL);
		};

		if (rxtxdump) {
			if (nleft == 0) msg = "0x" + Dbe::bufToHex(buf, reqlen, true);
			else msg = string(strerror(n));

			if (!histNotDump) cout << msg << endl;
			else appendToLastInHist(msg);
		};
	};
#endif
	// IP tx --- IEND

	return retval;
};

void UntPmndUbdk::flush() {
	tcflush(fd, TCIOFLUSH); // IP flush --- ILINE
};

uint8_t UntPmndUbdk::getTixVControllerBySref(
			const string& sref
		) {
	return VecVPmndUbdkController::getTix(sref);
};

string UntPmndUbdk::getSrefByTixVController(
			const uint8_t tixVController
		) {
	return VecVPmndUbdkController::getSref(tixVController);
};

void UntPmndUbdk::fillFeedFController(
			Feed& feed
		) {
	VecVPmndUbdkController::fillFeed(feed);
};

uint8_t UntPmndUbdk::getTixWBufferBySref(
			const string& sref
		) {
	return VecWPmndUbdkBuffer::getTix(sref);
};

string UntPmndUbdk::getSrefByTixWBuffer(
			const uint8_t tixWBuffer
		) {
	return VecWPmndUbdkBuffer::getSref(tixWBuffer);
};

void UntPmndUbdk::fillFeedFBuffer(
			Feed& feed
		) {
	VecWPmndUbdkBuffer::fillFeed(feed);
};

uint8_t UntPmndUbdk::getTixVCommandBySref(
			const uint8_t tixVController
			, const string& sref
		) {
	uint8_t tixVCommand = 0;

	if (tixVController == VecVPmndUbdkController::CHRONO) tixVCommand = VecVPmndUbdkChronoCommand::getTix(sref);
	else if (tixVController == VecVPmndUbdkController::DISP) tixVCommand = VecVPmndUbdkDispCommand::getTix(sref);
	else if (tixVController == VecVPmndUbdkController::IMEAS) tixVCommand = VecVPmndUbdkImeasCommand::getTix(sref);
	else if (tixVController == VecVPmndUbdkController::STATE) tixVCommand = VecVPmndUbdkStateCommand::getTix(sref);

	return tixVCommand;
};

string UntPmndUbdk::getSrefByTixVCommand(
			const uint8_t tixVController
			, const uint8_t tixVCommand
		) {
	string sref;

	if (tixVController == VecVPmndUbdkController::CHRONO) sref = VecVPmndUbdkChronoCommand::getSref(tixVCommand);
	else if (tixVController == VecVPmndUbdkController::DISP) sref = VecVPmndUbdkDispCommand::getSref(tixVCommand);
	else if (tixVController == VecVPmndUbdkController::IMEAS) sref = VecVPmndUbdkImeasCommand::getSref(tixVCommand);
	else if (tixVController == VecVPmndUbdkController::STATE) sref = VecVPmndUbdkStateCommand::getSref(tixVCommand);

	return sref;
};

void UntPmndUbdk::fillFeedFCommand(
			const uint8_t tixVController
			, Feed& feed
		) {
	feed.clear();

	if (tixVController == VecVPmndUbdkController::CHRONO) VecVPmndUbdkChronoCommand::fillFeed(feed);
	else if (tixVController == VecVPmndUbdkController::DISP) VecVPmndUbdkDispCommand::fillFeed(feed);
	else if (tixVController == VecVPmndUbdkController::IMEAS) VecVPmndUbdkImeasCommand::fillFeed(feed);
	else if (tixVController == VecVPmndUbdkController::STATE) VecVPmndUbdkStateCommand::fillFeed(feed);
};

Bufxf* UntPmndUbdk::getNewBufxf(
			const uint8_t tixWBuffer
			, const size_t reqlen
			, unsigned char* buf
		) {
	Bufxf* bufxf = NULL;

	return bufxf;
};

Cmd* UntPmndUbdk::getNewCmd(
			const uint8_t tixVController
			, const uint8_t tixVCommand
		) {
	Cmd* cmd = NULL;

	if (tixVController == VecVPmndUbdkController::CHRONO) cmd = CtrPmndUbdkChrono::getNewCmd(tixVCommand);
	else if (tixVController == VecVPmndUbdkController::DISP) cmd = CtrPmndUbdkDisp::getNewCmd(tixVCommand);
	else if (tixVController == VecVPmndUbdkController::IMEAS) cmd = CtrPmndUbdkImeas::getNewCmd(tixVCommand);
	else if (tixVController == VecVPmndUbdkController::STATE) cmd = CtrPmndUbdkState::getNewCmd(tixVCommand);

	return cmd;
};
