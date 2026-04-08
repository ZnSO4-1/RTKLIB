# makefile for rtklib unit test
CXX ?= g++

CC := $(CXX)
SRC    = ../../src
#CXXFLAGS = -Wall -O3 -std=c++11 -pedantic -I$(SRC) -DENAGLO
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic -I$(SRC) -DTRACE -DENAGLO -DENAQZS
LDLIBS = -lm -llapack -lblas

BIN    = t_matrix t_time t_coord t_rinex t_lambda t_atmos t_misc t_preceph t_gloeph \
t_geoid t_ppp t_ionex t_stec t_tle

all        : $(BIN)
t_matrix   : t_matrix.o rtkcmn.o preceph.o
t_time     : t_time.o rtkcmn.o preceph.o
t_coord    : t_coord.o rtkcmn.o geoid.o preceph.o
t_rinex    : t_rinex.o rtkcmn.o rinex.o preceph.o
t_lambda   : t_lambda.o rtkcmn.o lambda.o preceph.o
t_atmos    : t_atmos.o rtkcmn.o preceph.o
t_misc     : t_misc.o rtkcmn.o preceph.o
t_preceph  : t_preceph.o rtkcmn.o preceph.o rinex.o ephemeris.o sbas.o qzslex.o
t_gloeph   : t_gloeph.o rtkcmn.o rinex.o ephemeris.o sbas.o preceph.o qzslex.o
t_geoid    : t_geoid.o rtkcmn.o preceph.o geoid.o
t_ppp      : t_ppp.o rtkcmn.o ephemeris.o preceph.o sbas.o ionex.o pntpos.o ppp.o ppp_ar.o
t_ppp      : stec.o lambda.o qzslex.o
t_ionex    : t_ionex.o rtkcmn.o preceph.o ionex.o
t_stec     : t_stec.o rtkcmn.o preceph.o stec.o
t_tle      : t_tle.o rtkcmn.o rinex.o ephemeris.o sbas.o preceph.o tle.o qzslex.o

rtkcmn.o   : $(SRC)/rtklib.h $(SRC)/rtkcmn.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtkcmn.cpp
rinex.o    : $(SRC)/rtklib.h $(SRC)/rinex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rinex.cpp
rtkpos.o   : $(SRC)/rtklib.h $(SRC)/rtkpos.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtkpos.cpp
lambda.o   : $(SRC)/rtklib.h $(SRC)/lambda.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/lambda.cpp
geoid.o    : $(SRC)/rtklib.h $(SRC)/geoid.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/geoid.cpp
ephemeris.o: $(SRC)/rtklib.h $(SRC)/ephemeris.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ephemeris.cpp
sbas.o     : $(SRC)/rtklib.h $(SRC)/sbas.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/sbas.cpp
preceph.o  : $(SRC)/rtklib.h $(SRC)/preceph.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/preceph.cpp
ppp.o      : $(SRC)/rtklib.h $(SRC)/ppp.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ppp.cpp
ppp_ar.o   : $(SRC)/rtklib.h $(SRC)/ppp_ar.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ppp_ar.cpp
pntpos.o   : $(SRC)/rtklib.h $(SRC)/pntpos.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/pntpos.cpp
ionex.o    : $(SRC)/rtklib.h $(SRC)/ionex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ionex.cpp
stec.o     : $(SRC)/rtklib.h $(SRC)/stec.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/stec.cpp
tle.o      : $(SRC)/rtklib.h $(SRC)/tle.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/tle.cpp
qzslex.o   : $(SRC)/rtklib.h $(SRC)/qzslex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/qzslex.cpp

utest : utest1 utest2 utest3 utest4 utest5 utest6 utest7 utest8
utest : utest9 utest10 utest11 utest12 utest14

utest1 :
	./t_matrix  > utest1.out
utest2 :
	./t_time    > utest2.out
utest3 :
	./t_coord   > utest3.out
utest4 :
	./t_rinex   > utest4.out
utest5 :
	./t_lambda  > utest5.out
utest6 :
	./t_atmos   > utest6.out
utest7 :
	./t_misc    > utest7.out
utest8 :
	./t_preceph > utest8.out
utest9 :
	./t_gloeph  > utest9.out
utest10 :
#	./t_geoid   > utest10.out
utest11 :
	./t_ppp     > utest11.out
utest12 :
	./t_ionex   > utest12.out
utest13 :
	./t_stec    > utest13.out
utest14 :
	./t_tle     > utest14.out

clean :
	rm -f *.o *.out *.exe $(BIN) *.stackdump gmon.out
