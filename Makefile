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

dynamic_lib_file: libSista.so objects_dynamic
	g++ -std=c++17 -Wall -g -fPIC -c sista.cpp
	g++ -std=c++17 -o sista sista.o -lSista

static_lib_file: static objects
	g++ -std=c++17 -o sista sista.cpp -lSista

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
	install -d $(PREFIX)/lib
	install -m 755 libSista.so $(PREFIX)/lib/
	install -m 644 libSista.a $(PREFIX)/lib/
	install -d $(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(PREFIX)/include/sista/
	echo "$(PREFIX)/lib" | sudo tee /etc/ld.so.conf.d/sista.conf
	ldconfig

uninstall:
	rm -f $(PREFIX)/lib/libSista.so
	rm -f $(PREFIX)/lib/libSista.a
	rm -rf $(PREFIX)/include/sista
	rm -f /etc/ld.so.conf.d/sista.conf
	ldconfig

.PHONY: all objects objects_dynamic file dynamic_lib_file static_lib_file clean static install uninstall