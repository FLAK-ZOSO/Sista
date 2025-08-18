# Makefile for sista.cpp
IMPLEMENTATIONS = include/sista/ANSI-Settings.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp
OBJECTS = ANSI-Settings.o border.o coordinates.o cursor.o field.o pawn.o

# For the Makefile CI workflow, macos-latest cannot use the `-static` flag
ifeq "$(shell uname -s)" "Darwin"
	STATIC_FLAG=
else
	STATIC_FLAG=-static
endif

# Set default PREFIX for Windows and Unix
ifeq ($(OS),Windows_NT)
    PREFIX ?= C:\Program Files\Sista
    LIB_EXT=.a
    SHARED_EXT=.dll
else
    PREFIX ?= /usr/local
    LIB_EXT=.a
    SHARED_EXT=.so
endif

# Use cmd.exe for recipes on Windows
ifeq ($(OS),Windows_NT)
	SHELL := cmd.exe
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

ifneq "$(shell uname -s)" "Darwin"
# Compiles sista.cpp and links it against the local static library libSista.a
sista_against_static_lib_local: libSista.a objects
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -std=c++17 -static -o sista sista.o libSista.a
endif

# Compiles sista.cpp and links it against the system dynamic library libSista.so
sista_against_dynamic_lib_shared:
	g++ -std=c++17 -Wall -fPIC -c sista.cpp
	g++ -std=c++17 -o sista sista.o -lSista

ifneq "$(shell uname -s)" "Darwin"
# Compiles sista.cpp and links it against the system static library libSista.a
sista_against_static_lib_shared:
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -std=c++17 -static -o sista sista.o -lSista
endif

%.o: include/sista/%.cpp
	g++ -std=c++17 -Wall -fPIC -c $< -o $@

libSista.so: $(OBJECTS)
	g++ -std=c++17 -Wall -fPIC -shared -o libSista.so $(OBJECTS)

ifeq ($(OS),Windows_NT) # Assumes usage of MinGW on Windows
libSista.dll: $(OBJECTS)
	g++ -std=c++17 -Wall -shared -o libSista.dll $(OBJECTS) -Wl,--out-implib,libSista.lib

libSista.a: $(OBJECTS)
	ar rcs libSista.a $(OBJECTS)
endif

libSista.a: $(OBJECTS)
	ar rcs libSista.a $(OBJECTS)

clean:
	rm -f *.o libSista.so libSista.a

ifeq ($(OS),Windows_NT)
install: libSista.dll libSista.a
	@if not exist "$(PREFIX)" mkdir "$(PREFIX)"
	@if not exist "$(PREFIX)\lib" mkdir "$(PREFIX)\lib"
	@if not exist "$(PREFIX)\include\sista" mkdir "$(PREFIX)\include\sista"
	copy libSista.dll "$(PREFIX)\lib\"
	copy libSista.lib "$(PREFIX)\lib\"
	copy libSista.a "$(PREFIX)\lib\"
	copy include\sista\*.hpp "$(PREFIX)\include\sista\"
	@echo "Library and headers installed to $(PREFIX)."
	@echo "Remember to add $(PREFIX)\lib to your compiler's library search path and $(PREFIX)\include\sista to your include path."

uninstall:
	del "$(PREFIX)\lib\libSista.dll"
	del "$(PREFIX)\lib\libSista.lib"
	del "$(PREFIX)\lib\libSista.a"
	@if exist "$(PREFIX)\include\sista" rmdir /S /Q "$(PREFIX)\include\sista"
else ifeq "$(shell uname -s)" "Darwin"
install: libSista.so libSista.a
	install -d $(PREFIX)/lib
	install -m 755 libSista.so $(PREFIX)/lib/
	install -m 644 libSista.a $(PREFIX)/lib/
	install -d $(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(PREFIX)/include/sista/

uninstall:
	rm -f $(PREFIX)/lib/libSista.so
	rm -f $(PREFIX)/lib/libSista.a
	rm -rf $(PREFIX)/include/sista
else
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
endif

.PHONY: all objects objects_dynamic clean install uninstall sista_against_dynamic_lib_local sista_against_static_lib_local sista_against_dynamic_lib_shared sista_against_static_lib_shared
