IMPLEMENTATIONS = include/sista/ansi.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp
OBJECTS = ansi.o border.o coordinates.o cursor.o field.o pawn.o

RAW_TAG := $(shell git describe --tags --abbrev=0 2>/dev/null)
TAG := $(subst v,,$(RAW_TAG))
FULL_VERSION ?= $(TAG)
FULL_VERSION ?= 3.0.0-beta.42 # Fallback version if no tag is found

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

# Set default PREFIX and variables based on OS
ifeq ($(OS),Windows_NT)
    PREFIX ?= C:\Program Files\Sista
    LIB_EXT=.a
    SHARED_EXT=.dll
else ifeq "$(shell uname -s)" "Darwin"
    PREFIX ?= /usr/local
    LIB_EXT=.a
    SHARED_EXT=.dylib
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

build: libSista.so libSista_api.so libSista.a libSista_api.a

objects:
	g++ -std=c++17 -Wall -c $(IMPLEMENTATIONS)

objects_dynamic:
	g++ -std=c++17 -Wall -fPIC -c $(IMPLEMENTATIONS)

# Compiles all the library files into object files, then links them to the executable
sista: objects
	g++ -std=c++17 -Wall -c sista.cpp
	g++ $(STATIC_FLAG) -Wall -o sista sista.o $(OBJECTS)

# Compiles sista.cpp and links it against the local dynamic library libSista.so
sista_against_dynamic_lib_local: libSista.so objects_dynamic
	g++ -std=c++17 -Wall -fPIC -c sista.cpp
	g++ -o sista sista.o libSista.so

ifneq "$(shell uname -s)" "Darwin"
# Compiles sista.cpp and links it against the local static library libSista.a
sista_against_static_lib_local: libSista.a objects
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -static -o sista sista.o libSista.a
endif

# Compiles sista.cpp and links it against the system dynamic library libSista.so
sista_against_dynamic_lib_shared:
	g++ -std=c++17 -Wall -fPIC -c sista.cpp
	g++ -o sista sista.o -lSista

ifneq "$(shell uname -s)" "Darwin"
# Compiles sista.cpp and links it against the system static library libSista.a
sista_against_static_lib_shared:
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -static -o sista sista.o -lSista
endif

%.o: include/sista/%.cpp
	g++ -std=c++17 -Wall -fPIC -c $< -o $@

api.o: include/sista/api.h include/sista/api.cpp
	g++ -std=c++17 -Wall -fPIC -Iinclude -c include/sista/api.cpp -o api.o -lSista

libSista.so: $(OBJECTS)
	g++ -std=c++17 -Wall -fPIC -shared -o libSista.so.$(FULL_VERSION) $(OBJECTS) -Wl,-soname,libSista.so.$(MAJOR_VERSION)

libSista_api.so: api.o
	g++ -Wall -fPIC -shared -o libSista_api.so.$(FULL_VERSION) api.o libSista.so.$(FULL_VERSION) -lstdc++ -Wl,-soname,libSista_api.so.$(MAJOR_VERSION)

ifeq "$(shell uname -s)" "Darwin"
libSista.dylib: $(OBJECTS)
	g++ -Wall -dynamiclib -o libSista.dylib.$(FULL_VERSION) $(OBJECTS) \
	-Wl,-install_name,@rpath/libSista.dylib,-current_version,$(MAJOR_VERSION),-compatibility_version,$(MAJOR_VERSION),-rpath,$(PREFIX)/lib

libSista_api.dylib: api.o
	g++ -Wall -dynamiclib -o libSista_api.dylib.$(FULL_VERSION) api.o libSista.dylib.$(FULL_VERSION) \
	-Wl,-install_name,@rpath/libSista_api.dylib,-current_version,$(MAJOR_VERSION),-compatibility_version,$(MAJOR_VERSION),-rpath,$(PREFIX)/lib
endif

ifeq ($(OS),Windows_NT) # Assumes usage of MinGW on Windows
libSista.dll: $(OBJECTS)
	g++ -std=c++17 -Wall -shared -o libSista.dll $(OBJECTS) -Wl,--out-implib,libSista.lib

libSista_api.dll: api.o
	g++ -Wall -shared -o libSista_api.dll api.o libSista.dll -Wl,--out-implib,libSista_api.lib
endif

libSista.a: $(OBJECTS)
	ar rcs libSista.a $(OBJECTS)
	ranlib libSista.a

libSista_api.a: api.o
	ar rcs libSista_api.a api.o
	ranlib libSista_api.a

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
	copy include\sista\*.h "$(PREFIX)\include\sista\"
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
	install -m 644 libSista.dylib.$(FULL_VERSION) $(PREFIX)/lib/
	install -m 644 libSista_api.dylib.$(FULL_VERSION) $(PREFIX)/lib/
	ln -sf libSista.dylib.$(FULL_VERSION) $(PREFIX)/lib/libSista.dylib.$(MAJOR_VERSION)
	ln -sf libSista.dylib.$(MAJOR_VERSION) $(PREFIX)/lib/libSista.dylib
	ln -sf libSista_api.dylib.$(FULL_VERSION) $(PREFIX)/lib/libSista_api.dylib.$(MAJOR_VERSION)
	ln -sf libSista_api.dylib.$(MAJOR_VERSION) $(PREFIX)/lib/libSista_api.dylib
	install -m 644 libSista.a $(PREFIX)/lib/
	install -m 644 libSista_api.a $(PREFIX)/lib/
	install -d $(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(PREFIX)/include/sista/
	install -m 644 include/sista/*.h $(PREFIX)/include/sista/

uninstall:
	rm -f $(PREFIX)/lib/libSista.dylib
	rm -f $(PREFIX)/lib/libSista.dylib.*
	rm -f $(PREFIX)/lib/libSista_api.dylib
	rm -f $(PREFIX)/lib/libSista_api.dylib.*
	rm -f $(PREFIX)/lib/libSista.a
	rm -f $(PREFIX)/lib/libSista_api.a
	rm -rf $(PREFIX)/include/sista
else
install: libSista.so libSista.a libSista_api.so libSista_api.a
	@echo "Staged install to '$(DESTDIR)$(PREFIX)' (use DESTDIR for packaging)"
	install -d $(DESTDIR)$(PREFIX)/lib
	install -m 644 libSista.so.$(FULL_VERSION) $(DESTDIR)$(PREFIX)/lib/
	install -m 644 libSista_api.so.$(FULL_VERSION) $(DESTDIR)$(PREFIX)/lib/
	ln -sf libSista_api.so.$(FULL_VERSION) $(DESTDIR)$(PREFIX)/lib/libSista_api.so.$(MAJOR_VERSION)
	ln -sf libSista_api.so.$(MAJOR_VERSION) $(DESTDIR)$(PREFIX)/lib/libSista_api.so
	ln -sf libSista.so.$(FULL_VERSION) $(DESTDIR)$(PREFIX)/lib/libSista.so.$(MAJOR_VERSION)
	ln -sf libSista.so.$(MAJOR_VERSION) $(DESTDIR)$(PREFIX)/lib/libSista.so
	install -m 644 libSista.a $(DESTDIR)$(PREFIX)/lib/
	install -m 644 libSista_api.a $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(DESTDIR)$(PREFIX)/include/sista/ || true
	install -m 644 include/sista/*.h $(DESTDIR)$(PREFIX)/include/sista/ || true
	# write ld.so config into the package tree (do not modify the real system)
	install -d $(DESTDIR)/etc/ld.so.conf.d
	printf '%s\n' '$(PREFIX)/lib' > $(DESTDIR)/etc/ld.so.conf.d/sista.conf
	# only update the real system if DESTDIR is empty (interactive install)
	if [ -z "$(DESTDIR)" ]; then \
	  if command -v sudo >/dev/null 2>&1; then \
	    echo "$(PREFIX)/lib" | sudo tee /etc/ld.so.conf.d/sista.conf; \
	    sudo ldconfig || true; \
	  else \
	    echo "$(PREFIX)/lib" | tee /etc/ld.so.conf.d/sista.conf; \
	    ldconfig || true; \
	  fi \
	fi

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/libSista.so
	rm -f $(DESTDIR)$(PREFIX)/lib/libSista.so.*
	rm -f $(DESTDIR)$(PREFIX)/lib/libSista_api.so
	rm -f $(DESTDIR)$(PREFIX)/lib/libSista_api.so.*
	rm -f $(DESTDIR)$(PREFIX)/lib/libSista.a
	rm -f $(DESTDIR)$(PREFIX)/lib/libSista_api.a
	rm -rf $(DESTDIR)$(PREFIX)/include/sista
	rm -f $(DESTDIR)/etc/ld.so.conf.d/sista.conf
	if [ -z "$(DESTDIR)" ]; then \
	  if command -v sudo >/dev/null 2>&1; then \
	    sudo ldconfig || true; \
	  else \
	    ldconfig || true; \
	  fi \
	fi
endif

.PHONY: all objects objects_dynamic clean install uninstall sista_against_dynamic_lib_local sista_against_static_lib_local sista_against_dynamic_lib_shared sista_against_static_lib_shared
