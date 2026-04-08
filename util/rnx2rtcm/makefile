# makefile for rnx2rtcm
CXX ?= g++

CC := $(CXX)
BINDIR = /usr/local/bin
SRC    = ../../src
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic -I$(SRC) -DTRACE -DENAGLO -DENAGAL -DENAQZS -DNFREQ=3 -DNEXOBS=3
LDLIBS  = -lm

rnx2rtcm   : rnx2rtcm.o rtkcmn.o rinex.o rtcm.o rtcm2.o rtcm3.o rtcm3e.o

rnx2rtcm.o : rnx2rtcm.cpp
	$(CXX) -c $(CXXFLAGS) rnx2rtcm.cpp
rtkcmn.o   : $(SRC)/rtkcmn.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtkcmn.cpp
rinex.o    : $(SRC)/rinex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rinex.cpp
rtcm.o     : $(SRC)/rtcm.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm.cpp
rtcm2.o    : $(SRC)/rtcm2.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm2.cpp
rtcm3.o    : $(SRC)/rtcm3.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm3.cpp
rtcm3e.o   : $(SRC)/rtcm3e.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm3e.cpp

install:
	cp rnx2rtcm $(BINDIR)

clean:
	rm -f rnx2rtcm rnx2rtcm.exe *.o

OPT1=inp/GMSD7_201210140.* -x 2
OPT2=inp/javad1_201103010000.* -x 2
OPT3=inp/brdc0600.11* inp/gras0600.11o -x 2

test: test1 test2 test3 test4 test5 test6 test7

test1:
	./rnx2rtcm $(OPT1) -typ 1002,1019,1033 -sta 111 -out out/rtcm_1002.rtcm3
test2:
	./rnx2rtcm $(OPT1) -typ 1004,1019,1033 -sta 222 -out out/rtcm_1004.rtcm3
test3:
	./rnx2rtcm $(OPT1) -typ 1010,1020,1033 -sta 333 -out out/rtcm_1010.rtcm3
test4:
	./rnx2rtcm $(OPT1) -typ 1012,1020,1033 -sta 444 -out out/rtcm_1012.rtcm3
test5:
	./rnx2rtcm $(OPT1) -typ 1044 -sta 555 -out out/rtcm_1044.rtcm3
test6:
	./rnx2rtcm $(OPT1) -typ 1074 -sta 666 -out out/rtcm_1074.rtcm3
test7:
	./rnx2rtcm $(OPT2) -typ 1074,1084,1094,1104,1114,1019,1020,1044,1045,1046 -sta 444 -out out/rtcm_1074_jav.rtcm3
test8:
	./rnx2rtcm $(OPT2) -typ 1075,1085,1095,1105,1115,1019,1020,1044,1045,1046 -sta 555 -out out/rtcm_1075_jav.rtcm3
test9:
	./rnx2rtcm $(OPT2) -typ 1076,1086,1096,1106,1116,1019,1020,1044,1045,1046 -sta 666 -out out/rtcm_1076_jav.rtcm3
test10:
	./rnx2rtcm $(OPT2) -typ 1077,1087,1097,1107,1117,1019,1020,1044,1045,1046 -sta 777 -out out/rtcm_1077_jav.rtcm3
test11:
	./rnx2rtcm $(OPT3) -typ 1077,1087,1019,1020 -sta 888 -out out/rtcm_1077_gras.rtcm3
