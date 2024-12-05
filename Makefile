# Makefile for sista.cpp
IMPLEMENTATIONS = include/sista/ANSI-Settings.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp

all: objects file clean

objects:
	g++ -std=c++17 -Wall -g -c $(IMPLEMENTATIONS)

file: objects
	g++ -std=c++17 -Wall -g -c sista.cpp
	g++ -std=c++17 -Wall -g -o sista sista.o ANSI-Settings.o border.o coordinates.o cursor.o pawn.o field.o

clean:
	rm -f *.o