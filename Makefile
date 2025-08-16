# Makefile for sista.cpp
IMPLEMENTATIONS = include/sista/ANSI-Settings.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp
OBJECTS = ANSI-Settings.o border.o coordinates.o cursor.o field.o pawn.o

# For the Makefile CI workflow, macos-latest cannot use the `-static` flag
ifeq "$(shell uname -s)" "Darwin"
	STATIC_FLAG=
else
	STATIC_FLAG=-static
endif

all: sista

objects:
	g++ -std=c++17 -Wall -c $(IMPLEMENTATIONS)

objects_dynamic:
	g++ -std=c++17 -Wall -fPIC -c $(IMPLEMENTATIONS)

# Compiles all the library files into object files, then links them to the executable
sista: objects
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -std=c++17 $(STATIC_FLAG) -Wall -o sista sista.o $(OBJECTS)

# Compiles sista.cpp and links it against the local dynamic library libSista.so
sista_against_dynamic_lib_local: libSista.so objects_dynamic
	g++ -std=c++17 -Wall -fPIC -c sista.cpp
	g++ -std=c++17 -o sista sista.o libSista.so

# Compiles sista.cpp and links it against the local static library libSista.a
sista_against_static_lib_local: libSista.a objects
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -std=c++17 -static -o sista sista.o libSista.a

# Compiles sista.cpp and links it against the system dynamic library libSista.so
sista_against_dynamic_lib_shared: install
	g++ -std=c++17 -Wall -fPIC -c sista.cpp
	g++ -std=c++17 -o sista sista.o -lSista

# Compiles sista.cpp and links it against the system static library libSista.a
sista_against_static_lib_shared: install
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -std=c++17 -static -o sista sista.o -lSista

%.o: include/sista/%.cpp
	g++ -std=c++17 -Wall -fPIC -c $< -o $@

libSista.so: $(OBJECTS)
	g++ -std=c++17 -Wall -fPIC -shared -o libSista.so $(OBJECTS)

libSista.a: $(OBJECTS)
	ar rcs libSista.a $(OBJECTS)

clean:
	rm -f *.o libSista.so libSista.a

PREFIX ?= /usr/local

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

.PHONY: all objects objects_dynamic clean install uninstall sista_against_dynamic_lib_local sista_against_static_lib_local sista_against_dynamic_lib_shared sista_against_static_lib_shared
