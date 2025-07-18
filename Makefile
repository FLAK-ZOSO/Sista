# Makefile for sista.cpp
IMPLEMENTATIONS = include/sista/ANSI-Settings.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp
OBJECTS = ANSI-Settings.o border.o coordinates.o cursor.o field.o pawn.o

all: objects file

objects:
	g++ -std=c++17 -Wall -g -c $(IMPLEMENTATIONS)

objects_dynamic:
	g++ -std=c++17 -Wall -g -fPIC -c $(IMPLEMENTATIONS)

file: objects
	g++ -std=c++17 -Wall -g -c sista.cpp
	g++ -std=c++17 -Wall -g -o sista sista.o $(OBJECTS)

dynamic_lib_file: library objects_dynamic
	g++ -std=c++17 -Wall -g -fPIC -c sista.cpp
	g++ -std=c++17 -Iinclude -L. -o sista sista.cpp -lSista

library: $(OBJECTS)
	g++ -std=c++17 -Wall -fPIC -shared -o libSista.so $(OBJECTS)

%.o: include/sista/%.cpp
	g++ -std=c++17 -Wall -g -fPIC -c $< -o $@

clean:
	rm -f *.o sista libSista.so

PREFIX ?= /usr/local

install: libSista.so
	install -d $(PREFIX)/lib
	install -m 755 libSista.so $(PREFIX)/lib/
	install -d $(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(PREFIX)/include/sista/

.PHONY: install