IMPLEMENTATIONS = include/sista/ansi.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp
OBJECTS = ansi.o border.o coordinates.o cursor.o field.o pawn.o

RAW_TAG := $(shell git describe --tags --abbrev=0 2>/dev/null)
TAG := $(subst v,,$(RAW_TAG))
FULL_VERSION ?= $(TAG)
FULL_VERSION ?= 3.0.0-beta.42 # Fallback version if no tag is found

MAJOR_VERSION := $(word 1,$(subst ., ,$(FULL_VERSION)))
MINOR_VERSION := $(word 2,$(subst ., ,$(FULL_VERSION)))
PATCH_AND_PR := $(word 3,$(subst ., ,$(FULL_VERSION)))


# Set default PREFIX and variables based on OS
ifeq ($(OS),Windows_NT)
    PREFIX ?= C:\Program Files\Sista
    LIB_EXT=.a
    SHARED_EXT=.dll
    SHARED_TARGETS=libSista.dll libSista_api.dll
else ifeq "$(shell uname -s)" "Darwin"
    PREFIX ?= /usr/local
    LIB_EXT=.a
    SHARED_EXT=.dylib
    SHARED_TARGETS=libSista.dylib libSista_api.dylib
else
    PREFIX ?= /usr/local
    LIB_EXT=.a
    SHARED_EXT=.so
    SHARED_TARGETS=libSista.so libSista_api.so
endif

# May be overridden by distribution packaging (for example, /usr/lib64 on
# 64-bit RPM systems). Keep the conventional /lib subdirectory by default.
LIBDIR ?= $(PREFIX)/lib

# Use cmd.exe for recipes on Windows
ifeq ($(OS),Windows_NT)
	SHELL := cmd.exe
endif

all: build

build: $(SHARED_TARGETS) libSista.a libSista_api.a

objects objects_dynamic: $(OBJECTS)

# Compiles all the library files into object files, then links them to the executable
sista: $(OBJECTS)
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -Wall -o sista sista.o $(OBJECTS)

# Compiles sista.cpp and links it against the local dynamic library libSista.so
sista_against_dynamic_lib_local: libSista$(SHARED_EXT)
	g++ -std=c++17 -Wall -fPIC -c sista.cpp
	g++ -o sista sista.o ./libSista$(SHARED_EXT)

# Links Sista statically while retaining dynamic system dependencies
sista_against_static_lib_local: libSista.a
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -o sista sista.o libSista.a

# Compiles sista.cpp and links it against the system dynamic library libSista.so
sista_against_dynamic_lib_shared:
	g++ -std=c++17 -Wall -fPIC -c sista.cpp
	g++ -o sista sista.o -lSista

# Links the installed Sista archive while retaining dynamic system dependencies
sista_against_static_lib_shared:
	g++ -std=c++17 -Wall -c sista.cpp
	g++ -o sista sista.o "$(LIBDIR)/libSista.a"

%.o: include/sista/%.cpp
	g++ -std=c++17 -Wall -fPIC -c $< -o $@

api.o: include/sista/api.h include/sista/api.cpp
	g++ -std=c++17 -Wall -fPIC -Iinclude -c include/sista/api.cpp -o api.o

libSista.so: libSista.so.$(FULL_VERSION)
	ln -sf libSista.so.$(FULL_VERSION) libSista.so.$(MAJOR_VERSION)
	ln -sf libSista.so.$(MAJOR_VERSION) libSista.so

libSista.so.$(FULL_VERSION): $(OBJECTS)
	g++ -std=c++17 -Wall -fPIC -shared -o libSista.so.$(FULL_VERSION) $(OBJECTS) -Wl,-soname,libSista.so.$(MAJOR_VERSION)

libSista_api.so: libSista_api.so.$(FULL_VERSION)
	ln -sf libSista_api.so.$(FULL_VERSION) libSista_api.so.$(MAJOR_VERSION)
	ln -sf libSista_api.so.$(MAJOR_VERSION) libSista_api.so

libSista_api.so.$(FULL_VERSION): api.o libSista.so
	g++ -Wall -fPIC -shared -o libSista_api.so.$(FULL_VERSION) api.o libSista.so.$(FULL_VERSION) -lstdc++ -Wl,-soname,libSista_api.so.$(MAJOR_VERSION)

ifeq "$(shell uname -s)" "Darwin"
libSista.dylib: libSista.dylib.$(FULL_VERSION)
	ln -sf libSista.dylib.$(FULL_VERSION) libSista.dylib.$(MAJOR_VERSION)
	ln -sf libSista.dylib.$(MAJOR_VERSION) libSista.dylib

libSista.dylib.$(FULL_VERSION): $(OBJECTS)
	g++ -Wall -dynamiclib -o libSista.dylib.$(FULL_VERSION) $(OBJECTS) \
	-Wl,-install_name,@rpath/libSista.dylib,-current_version,$(MAJOR_VERSION),-compatibility_version,$(MAJOR_VERSION),-rpath,$(PREFIX)/lib

libSista_api.dylib: libSista_api.dylib.$(FULL_VERSION)
	ln -sf libSista_api.dylib.$(FULL_VERSION) libSista_api.dylib.$(MAJOR_VERSION)
	ln -sf libSista_api.dylib.$(MAJOR_VERSION) libSista_api.dylib

libSista_api.dylib.$(FULL_VERSION): api.o libSista.dylib
	g++ -Wall -dynamiclib -o libSista_api.dylib.$(FULL_VERSION) api.o libSista.dylib.$(FULL_VERSION) \
	-Wl,-install_name,@rpath/libSista_api.dylib,-current_version,$(MAJOR_VERSION),-compatibility_version,$(MAJOR_VERSION),-rpath,$(PREFIX)/lib
endif

ifeq ($(OS),Windows_NT) # Assumes usage of MinGW on Windows
libSista.dll: $(OBJECTS)
	g++ -std=c++17 -Wall -shared -o libSista.dll $(OBJECTS) -Wl,--out-implib,libSista.lib

libSista_api.dll: api.o libSista.dll
	g++ -Wall -shared -o libSista_api.dll api.o libSista.dll -Wl,--out-implib,libSista_api.lib
endif

libSista.a: $(OBJECTS)
	ar rcs libSista.a $(OBJECTS)
	ranlib libSista.a

libSista_api.a: api.o
	ar rcs libSista_api.a api.o
	ranlib libSista_api.a

mostlyclean:
	rm -f *.o

clean: mostlyclean
	rm -f sista libSista.so* libSista.a libSista.dylib* libSista.dll libSista.lib libSista_api.so* libSista_api.a libSista_api.dylib* libSista_api.dll libSista_api.lib

distclean: clean

maintainer-clean:
	@echo 'This command is intended for maintainers to use; it'
	@echo 'deletes files that may need special tools to rebuild.'
	$(MAKE) distclean

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
	REM Provide MSVC-friendly import library names (without "lib" prefix)
	copy libSista.lib "$(PREFIX)\lib\Sista.lib"
	copy libSista_api.lib "$(PREFIX)\lib\Sista_api.lib"
	copy include\sista\*.hpp "$(PREFIX)\include\sista\"
	copy include\sista\*.h "$(PREFIX)\include\sista\"
	@echo "Library and headers installed to $(PREFIX)."
	@echo "Remember to add $(PREFIX)\lib to your compiler's library search path and $(PREFIX)\include\sista to your include path."

uninstall:
	del "$(PREFIX)\lib\libSista.dll"
	del "$(PREFIX)\lib\libSista.lib"
	del "$(PREFIX)\lib\libSista.a"
	@if exist "$(PREFIX)\include\sista" rmdir /S /Q "$(PREFIX)\include\sista"
	REM remove MSVC-friendly names as well
	del "$(PREFIX)\lib\Sista.lib" || @rem
	del "$(PREFIX)\lib\Sista_api.lib" || @rem
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
	install -d $(DESTDIR)$(LIBDIR)
	install -m 644 libSista.so.$(FULL_VERSION) $(DESTDIR)$(LIBDIR)/
	install -m 644 libSista_api.so.$(FULL_VERSION) $(DESTDIR)$(LIBDIR)/
	ln -sf libSista_api.so.$(FULL_VERSION) $(DESTDIR)$(LIBDIR)/libSista_api.so.$(MAJOR_VERSION)
	ln -sf libSista_api.so.$(MAJOR_VERSION) $(DESTDIR)$(LIBDIR)/libSista_api.so
	ln -sf libSista.so.$(FULL_VERSION) $(DESTDIR)$(LIBDIR)/libSista.so.$(MAJOR_VERSION)
	ln -sf libSista.so.$(MAJOR_VERSION) $(DESTDIR)$(LIBDIR)/libSista.so
	install -m 644 libSista.a $(DESTDIR)$(LIBDIR)/
	install -m 644 libSista_api.a $(DESTDIR)$(LIBDIR)/
	install -d $(DESTDIR)$(PREFIX)/include/sista
	install -m 644 include/sista/*.hpp $(DESTDIR)$(PREFIX)/include/sista/ || true
	install -m 644 include/sista/*.h $(DESTDIR)$(PREFIX)/include/sista/ || true
	# write ld.so config into the package tree (do not modify the real system)
	install -d $(DESTDIR)/etc/ld.so.conf.d
	printf '%s\n' '$(LIBDIR)' > $(DESTDIR)/etc/ld.so.conf.d/sista.conf
	# only update the real system if DESTDIR is empty (interactive install)
	if [ -z "$(DESTDIR)" ]; then \
	  if command -v sudo >/dev/null 2>&1; then \
	    echo "$(LIBDIR)" | sudo tee /etc/ld.so.conf.d/sista.conf; \
	    sudo ldconfig || true; \
	  else \
	    echo "$(LIBDIR)" | tee /etc/ld.so.conf.d/sista.conf; \
	    ldconfig || true; \
	  fi \
	fi

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/libSista.so
	rm -f $(DESTDIR)$(LIBDIR)/libSista.so.*
	rm -f $(DESTDIR)$(LIBDIR)/libSista_api.so
	rm -f $(DESTDIR)$(LIBDIR)/libSista_api.so.*
	rm -f $(DESTDIR)$(LIBDIR)/libSista.a
	rm -f $(DESTDIR)$(LIBDIR)/libSista_api.a
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

.PHONY: all build objects objects_dynamic mostlyclean clean distclean maintainer-clean install uninstall sista_against_dynamic_lib_local sista_against_static_lib_local sista_against_dynamic_lib_shared sista_against_static_lib_shared
