IMPLEMENTATIONS = ../include/sista/ANSI-Settings.cpp ../include/sista/border.cpp ../include/sista/coordinates.cpp ../include/sista/cursor.cpp ../include/sista/field.cpp ../include/sista/pawn.cpp

all:
	g++ -std=c++17 -Wall -g -c $(IMPLEMENTATIONS)
	g++ -std=c++17 -Wall -g -c header-test.cpp
	g++ -std=c++17 -Wall -g -o header-test header-test.o ANSI-Settings.o border.o coordinates.o cursor.o pawn.o field.o
	rm -f *.o

shared-test.o:
	g++ -std=c++17 -Wall -Wno-narrowing -Wno-sign-compare -g -c shared-test.cpp

shared-test: shared-test.o
	g++ -std=c++17 -o shared-test shared-test.o -lSista

clean:
	rm -f *.o header-test shared-test

.PHONY: all clean
