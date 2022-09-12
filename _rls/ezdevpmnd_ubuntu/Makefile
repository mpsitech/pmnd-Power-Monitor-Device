# file Makefile
# make file for Pmnd device access library, release ezdevpmnd_ubuntu
# copyright: (C) 2016-2020 MPSI Technologies GmbH
# author: Alexander Wirthmueller (auto-generation)
# date created: 28 May 2022
# IP header --- ABOVE

BUILDROOT = ${WHIZSDKROOT}/build
LIBROOT = ${WHIZSDKROOT}/lib

CPP = g++
CPPFLAGS = -std=c++11 -g -Wall -Os -pthread

STATLIB = ar
STATLIBFLAGS = rcs

INCPATH = -I$(BUILDROOT)
INCPATH += -I${WHIZSDKROOT}/build -I/usr/include/jsoncpp -I/usr/include/libxml2

PCHS = DevPmnd.h.gch

OBJS = Pmnd.o
OBJS +=
OBJS += UntPmndUbdk.o UntPmndUbdk_vecs.o CtrPmndUbdkChrono.o CtrPmndUbdkDisp.o CtrPmndUbdkImeas.o CtrPmndUbdkState.o
OBJS += UntPmndUdua.o UntPmndUdua_vecs.o CtrPmndUduaChrono.o CtrPmndUduaDisp.o CtrPmndUduaImeas.o CtrPmndUduaState.o

LIB = libezdevpmnd

.SUFFIXES: .h .h.gch .cpp

.h.h.gch :
	$(CPP) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

.cpp.o:
	$(CPP) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

all:	$(LIB)

$(LIB):	$(PCHS) $(OBJS)
	$(STATLIB) $(STATLIBFLAGS) $(LIB).a $(OBJS)
	rm -f *.o

install:
	mv $(LIB).a $(LIBROOT)/

clean: 
	rm -f *.gch
	rm -f *.o
