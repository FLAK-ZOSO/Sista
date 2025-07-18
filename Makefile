# Makefile for sista.cpp
IMPLEMENTATIONS = include/sista/ANSI-Settings.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp
OBJECTS = ANSI-Settings.o border.o coordinates.o cursor.o field.o pawn.o

all: objects file clean

objects:
	g++ -std=c++17 -Wall -g -c $(IMPLEMENTATIONS)

objects_dynamic:
	g++ -std=c++17 -Wall -g -fPIC -c $(IMPLEMENTATIONS)

file: objects
	g++ -std=c++17 -Wall -g -c sista.cpp
	g++ -std=c++17 -Wall -g -o sista sista.o $(OBJECTS)

dynamic_lib_file: libSista.so objects_dynamic
	g++ -std=c++17 -Wall -g -fPIC -c sista.cpp
	g++ -std=c++17 -Iinclude -L. -o sista sista.cpp -lSista

static_lib_file: static objects
	g++ -std=c++17 -Iinclude -o sista sista.cpp -lSista

libSista.so: $(OBJECTS)
	g++ -std=c++17 -Wall -fPIC -shared -o libSista.so $(OBJECTS)

%.o: include/sista/%.cpp
	g++ -std=c++17 -Wall -g -fPIC -c $< -o $@

clean:
	rm -f *.o libSista.so libSista.a

static: libSista.a

libSista.a: $(OBJECTS)
	ar rcs libSista.a $(OBJECTS)

PREFIX ?= /usr

install: libSista.so libSista.a
	install -d $(PREFIX)/lib64
	install -m 755 libSista.so $(PREFIX)/lib64/
	install -m 644 libSista.a $(PREFIX)/lib64/
	install -d $(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(PREFIX)/include/sista/
	ldconfig

.PHONY: install static