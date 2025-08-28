IMPLEMENTATIONS = include/sista/ansi.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp
OBJECTS = ansi.o border.o coordinates.o cursor.o field.o pawn.o

RAW_TAG := $(shell git describe --tags --abbrev=0 2>/dev/null)
TAG := $(subst v,,$(RAW_TAG))
FULL_VERSION ?= $(TAG)
FULL_VERSION ?= 3.0.0-alpha.42 # Fallback version if no tag is found

MAJOR_VERSION := $(word 1,$(subst ., ,$(FULL_VERSION)))
MINOR_VERSION := $(word 2,$(subst ., ,$(FULL_VERSION)))
PATCH_AND_PR := $(word 3,$(subst ., ,$(FULL_VERSION)))


# For the Makefile CI workflow, macos-latest cannot use the `-static` flag
ifeq "$(shell uname -s)" "Darwin"
	STATIC_FLAG=
	LIB_EXT=.a
	SHARED_EXT=.dylib
else
	STATIC_FLAG=-static
endif

# Set default PREFIX for Windows and Unix
ifeq ($(OS),Windows_NT)
    PREFIX ?= C:\Program Files\Sista
    LIB_EXT=.a
    SHARED_EXT=.dll
else ifneq "$(shell uname -s)" "Darwin"
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

api.o: include/sista-api/api.h include/sista-api/api.cpp
	g++ -std=c++17 -Wall -fPIC -Iinclude -Iinclude/sista-api -c include/sista-api/api.cpp -o api.o

libSista.so: $(OBJECTS)
	g++ -std=c++17 -Wall -fPIC -shared -o libSista.so.$(FULL_VERSION) $(OBJECTS) -Wl,-soname,libSista.so.$(MAJOR_VERSION)

libSista_api.so: api.o
	g++ -std=c++17 -Wall -fPIC -shared -o libSista_api.so.$(FULL_VERSION) api.o libSista.so.$(FULL_VERSION) -Wl,-soname,libSista_api.so.$(MAJOR_VERSION)

ifeq "$(shell uname -s)" "Darwin"
libSista.dylib: $(OBJECTS)
	g++ -std=c++17 -Wall -dynamiclib -o libSista.dylib.$(FULL_VERSION) $(OBJECTS) -Wl,-install_name,@rpath/libSista.dylib,-current_version,$(MAJOR_VERSION),-compatibility_version,$(MAJOR_VERSION)

libSista_api.dylib: api.o
	g++ -std=c++17 -Wall -dynamiclib -o libSista_api.dylib.$(FULL_VERSION) api.o libSista.so.$(FULL_VERSION) -Wl,-install_name,@rpath/libSista_api.dylib,-current_version,$(MAJOR_VERSION),-compatibility_version,$(MAJOR_VERSION)
endif

ifeq ($(OS),Windows_NT) # Assumes usage of MinGW on Windows
libSista.dll: $(OBJECTS)
	g++ -std=c++17 -Wall -shared -o libSista.dll $(OBJECTS) -Wl,--out-implib,libSista.lib

libSista_api.dll: api.o
	g++ -std=c++17 -Wall -shared -o libSista_api.dll api.o libSista.so.$(FULL_VERSION) -Wl,--out-implib,libSista_api.lib
endif

libSista.a: $(OBJECTS)
	ar rcs libSista.a $(OBJECTS)

libSista_api.a: api.o
	ar rcs libSista_api.a api.o

clean:
	rm -f *.o sista libSista.so* libSista.a libSista.dylib* libSista.dll libSista.lib api.o libSista_api.so* libSista_api.a libSista_api.dylib* libSista_api.dll libSista_api.lib

ifeq ($(OS),Windows_NT)
install: libSista.dll libSista.a libSista_api.dll libSista_api.a
	@echo "Installing Sista version $(FULL_VERSION) to $(PREFIX)..."
	@if not exist "$(PREFIX)" mkdir "$(PREFIX)"
	@if not exist "$(PREFIX)\lib" mkdir "$(PREFIX)\lib"
	@if not exist "$(PREFIX)\include\sista" mkdir "$(PREFIX)\include\sista"
	copy libSista.dll "$(PREFIX)\lib\"
	copy libSista.lib "$(PREFIX)\lib\"
	copy libSista.a "$(PREFIX)\lib\"
	copy libSista_api.dll "$(PREFIX)\lib\"
	copy libSista_api.lib "$(PREFIX)\lib\"
	copy libSista_api.a "$(PREFIX)\lib\"
	copy include\sista\*.hpp "$(PREFIX)\include\sista\"
	copy include\sista-api\*.h "$(PREFIX)\include\sista\"
	@echo "Library and headers installed to $(PREFIX)."
	@echo "Remember to add $(PREFIX)\lib to your compiler's library search path and $(PREFIX)\include\sista to your include path."

uninstall:
	del "$(PREFIX)\lib\libSista.dll"
	del "$(PREFIX)\lib\libSista.lib"
	del "$(PREFIX)\lib\libSista.a"
	del "$(PREFIX)\lib\libSista_api.dll"
	del "$(PREFIX)\lib\libSista_api.lib"
	@if exist "$(PREFIX)\include\sista" rmdir /S /Q "$(PREFIX)\include\sista"
else ifeq "$(shell uname -s)" "Darwin"
install: libSista.dylib libSista.a libSista_api.dylib libSista_api.a
	@echo "Installing Sista version $(FULL_VERSION) to $(PREFIX)..."
	install -d $(PREFIX)/lib
	install -m 755 libSista.dylib.$(FULL_VERSION) $(PREFIX)/lib/
	install -m 755 libSista_api.dylib.$(FULL_VERSION) $(PREFIX)/lib/
	ln -sf libSista.dylib.$(FULL_VERSION) $(PREFIX)/lib/libSista.dylib.$(MAJOR_VERSION)
	ln -sf libSista.dylib.$(MAJOR_VERSION) $(PREFIX)/lib/libSista.dylib
	ln -sf libSista_api.dylib.$(FULL_VERSION) $(PREFIX)/lib/libSista_api.dylib.$(MAJOR_VERSION)
	ln -sf libSista_api.dylib.$(MAJOR_VERSION) $(PREFIX)/lib/libSista_api.dylib
	install -m 644 libSista.a $(PREFIX)/lib/
	install -m 644 libSista_api.a $(PREFIX)/lib/
	install -d $(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(PREFIX)/include/sista/
	install -m 644 include/sista-api/*.h $(PREFIX)/include/sista/

uninstall:
	rm -f $(PREFIX)/lib/libSista.dylib
	rm -f $(PREFIX)/lib/libSista.dylib.$(MAJOR_VERSION)
	rm -f $(PREFIX)/lib/libSista.dylib.$(FULL_VERSION)
	rm -f $(PREFIX)/lib/libSista_api.dylib
	rm -f $(PREFIX)/lib/libSista_api.dylib.$(MAJOR_VERSION)
	rm -f $(PREFIX)/lib/libSista_api.dylib.$(FULL_VERSION)
	rm -f $(PREFIX)/lib/libSista.a
	rm -f $(PREFIX)/lib/libSista_api.a
	rm -rf $(PREFIX)/include/sista
else
install: libSista.so libSista.a libSista_api.so libSista_api.a
	@echo "Installing Sista version $(FULL_VERSION) to $(PREFIX)..."
	install -d $(PREFIX)/lib
	install -m 755 libSista.so.$(FULL_VERSION) $(PREFIX)/lib/
	install -m 755 libSista_api.so.$(FULL_VERSION) $(PREFIX)/lib/
	ln -sf libSista_api.so.$(FULL_VERSION) $(PREFIX)/lib/libSista_api.so.$(MAJOR_VERSION)
	ln -sf libSista_api.so.$(MAJOR_VERSION) $(PREFIX)/lib/libSista_api.so
	ln -sf libSista.so.$(FULL_VERSION) $(PREFIX)/lib/libSista.so.$(MAJOR_VERSION)
	ln -sf libSista.so.$(MAJOR_VERSION) $(PREFIX)/lib/libSista.so
	install -m 644 libSista.a $(PREFIX)/lib/
	install -m 644 libSista_api.a $(PREFIX)/lib/
	install -d $(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(PREFIX)/include/sista/
	install -m 644 include/sista-api/*.h $(PREFIX)/include/sista/
	echo "$(PREFIX)/lib" | sudo tee /etc/ld.so.conf.d/sista.conf
	ldconfig

uninstall:
	rm -f $(PREFIX)/lib/libSista.so
	rm -f $(PREFIX)/lib/libSista.so.$(MAJOR_VERSION)
	rm -f $(PREFIX)/lib/libSista.so.$(FULL_VERSION)
	rm -f $(PREFIX)/lib/libSista_api.so
	rm -f $(PREFIX)/lib/libSista_api.so.$(MAJOR_VERSION)
	rm -f $(PREFIX)/lib/libSista_api.so.$(FULL_VERSION)
	rm -f $(PREFIX)/lib/libSista.a
	rm -f $(PREFIX)/lib/libSista_api.a
	rm -rf $(PREFIX)/include/sista
	rm -f /etc/ld.so.conf.d/sista.conf
	ldconfig
endif

.PHONY: all objects objects_dynamic clean install uninstall sista_against_dynamic_lib_local sista_against_static_lib_local sista_against_dynamic_lib_shared sista_against_static_lib_shared
