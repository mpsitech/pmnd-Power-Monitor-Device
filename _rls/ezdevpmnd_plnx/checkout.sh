# file checkout.sh
# checkout script for Pmnd device access library sources, release ezdevpmnd_plnx (ubuntu cross-compilation)
# copyright: (C) 2017-2020 MPSI Technologies GmbH
# author: Alexander Wirthmueller (auto-generation)
# date created: 28 May 2022
# IP header --- ABOVE

if [ -z ${WHIZROOT+x} ]; then
	echo "WHIZROOT is not defined. It looks as if you didn't run a Whiznium initialization script beforehand."
	exit 1
fi

export set BUILDROOT=${SYSROOT}${WHIZSDKROOT}/build

mkdir $BUILDROOT/ezdevpmnd

cp makeall.sh $BUILDROOT/ezdevpmnd/

cp Makefile $BUILDROOT/ezdevpmnd/

cp ../../ezdevpmnd/*.h $BUILDROOT/ezdevpmnd/
cp ../../ezdevpmnd/*.cpp $BUILDROOT/ezdevpmnd/

cp ../../ezdevpmnd/UntPmndUbdk/*.h $BUILDROOT/ezdevpmnd/
cp ../../ezdevpmnd/UntPmndUbdk/*.cpp $BUILDROOT/ezdevpmnd/

cp ../../ezdevpmnd/UntPmndUdua/*.h $BUILDROOT/ezdevpmnd/
cp ../../ezdevpmnd/UntPmndUdua/*.cpp $BUILDROOT/ezdevpmnd/
