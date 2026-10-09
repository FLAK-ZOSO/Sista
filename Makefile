IMPLEMENTATIONS = include/sista/ansi.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp
OBJECTS = ansi.o border.o coordinates.o cursor.o field.o pawn.o

CXX ?= g++
AR ?= ar
RANLIB ?= ranlib
CXXSTD ?= -std=c++17
CXXFLAGS ?= -Wall -g
PICFLAGS ?= -fPIC

RAW_TAG := $(shell git describe --tags --abbrev=0 2>/dev/null)
TAG := $(patsubst v%,%,$(RAW_TAG))
HEADER_VERSION := $(shell sed -n 's/^\#define SISTA_VERSION "\([^"]*\)"/\1/p' include/sista/version.hpp)
FULL_VERSION ?= $(if $(strip $(TAG)),$(TAG),$(HEADER_VERSION))

MAJOR_VERSION := $(word 1,$(subst ., ,$(FULL_VERSION)))
MINOR_VERSION := $(word 2,$(subst ., ,$(FULL_VERSION)))
PATCH_AND_PR := $(word 3,$(subst ., ,$(FULL_VERSION)))

ifeq ($(strip $(PATCH_AND_PR)),)
$(error FULL_VERSION must contain at least MAJOR.MINOR.PATCH; got '$(FULL_VERSION)')
endif


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
ifneq ($(origin prefix),undefined)
    PREFIX := $(prefix)
endif
LIBDIR ?= $(PREFIX)/lib
ifneq ($(origin libdir),undefined)
    LIBDIR := $(libdir)
endif

# GNU installation directory and command conventions.  Keep the historical
# uppercase variables as compatibility aliases for packaging and existing users.
prefix ?= $(PREFIX)
exec_prefix ?= $(prefix)
libdir ?= $(LIBDIR)
includedir ?= $(prefix)/include
datarootdir ?= $(prefix)/share
docdir ?= $(datarootdir)/doc/sista
htmldir ?= $(docdir)/html
dvidir ?= $(docdir)/dvi
pdfdir ?= $(docdir)/pdf
psdir ?= $(docdir)/ps
infodir ?= $(datarootdir)/info
mandir ?= $(datarootdir)/man
man3dir ?= $(mandir)/man3
man7dir ?= $(mandir)/man7

INSTALL ?= install
INSTALL_DATA ?= $(INSTALL) -m 644
MKDIR_P ?= mkdir -p
STRIP ?= strip
CTAGS ?= ctags
DOXYGEN ?= doxygen

PACKAGE = sista
DIST_NAME = $(PACKAGE)-$(FULL_VERSION)
DIST_ARCHIVE = $(DIST_NAME).tar.gz
MAN3_PAGES = docs/man/sista-ansi.3 docs/man/sista-border.3 docs/man/sista-c-api.3 \
	docs/man/sista-coordinates.3 docs/man/sista-cursor.3 docs/man/sista-field.3 \
	docs/man/sista-pawn.3 docs/man/sista-version.3
MAN7_PAGES = docs/man/sista.7
MAN_ALIAS_SPECS = ANSISettings=sista-ansi.3 RGBColor=sista-ansi.3 \
	Border=sista-border.3 Coordinates=sista-coordinates.3 Cursor=sista-cursor.3 \
	Field=sista-field.3 Path=sista-field.3 SwappableField=sista-field.3 \
	Pawn=sista-pawn.3 getVersion=sista-version.3 \
	sista_createField=sista-c-api.3 sista_printField=sista-c-api.3 \
	sista_destroyField=sista-c-api.3 sista_createSwappableField=sista-c-api.3 \
	sista_printSwappableField=sista-c-api.3 sista_destroySwappableField=sista-c-api.3 \
	sista_resetAnsi=sista-c-api.3 sista_setForegroundColor=sista-c-api.3 \
	sista_setBackgroundColor=sista-c-api.3 sista_setAttribute=sista-c-api.3 \
	sista_resetAttribute=sista-c-api.3 sista_setForegroundColorRGB=sista-c-api.3 \
	sista_setBackgroundColorRGB=sista-c-api.3 sista_createANSISettings=sista-c-api.3 \
	sista_createANSISettingsRGB=sista-c-api.3 sista_applyANSISettings=sista-c-api.3 \
	sista_destroyANSISettings=sista-c-api.3 sista_createBorder=sista-c-api.3 \
	sista_destroyBorder=sista-c-api.3 sista_printFieldWithBorder=sista-c-api.3 \
	sista_printSwappableFieldWithBorder=sista-c-api.3 \
	sista_createPawnInSwappableField=sista-c-api.3 sista_createPawnInField=sista-c-api.3 \
	sista_getLastErrorCode=sista-c-api.3 sista_getLastErrorMessage=sista-c-api.3 \
	sista_movePawn=sista-c-api.3 sista_addPawnToSwap=sista-c-api.3 \
	sista_applySwaps=sista-c-api.3 sista_clearScreen=sista-c-api.3 \
	sista_createCursor=sista-c-api.3 sista_moveCursor=sista-c-api.3 \
	sista_cursorGoTo=sista-c-api.3 sista_cursorGoToCoordinates=sista-c-api.3 \
	sista_destroyCursor=sista-c-api.3 sista_getVersion=sista-c-api.3 \
	sista_getVersionMajor=sista-c-api.3 sista_getVersionMinor=sista-c-api.3 \
	sista_getVersionPatch=sista-c-api.3

# Use cmd.exe for recipes on Windows
ifeq ($(OS),Windows_NT)
	SHELL := cmd.exe
endif

all: build

build: $(SHARED_TARGETS) libSista.a libSista_api.a

check: build
	$(MAKE) -C demo pawnsCountTest
ifeq ($(OS),Windows_NT)
	demo\pawnsCountTest.exe
else
	./demo/pawnsCountTest
endif

test: check

info dvi pdf ps:
	@echo 'Sista does not provide documentation in the $@ format.'

man: $(MAN3_PAGES) $(MAN7_PAGES)

check-man: man
	python3 scripts/check_man_pages.py

html: docs/html/index.html

docs/html/index.html: Doxyfile $(IMPLEMENTATIONS) $(wildcard include/sista/*.hpp) $(wildcard include/sista/*.h)
	$(DOXYGEN) Doxyfile

TAGS: $(IMPLEMENTATIONS) $(wildcard include/sista/*.hpp) $(wildcard include/sista/*.h) sista.cpp
	$(CTAGS) -e -o $@ $(IMPLEMENTATIONS) $(wildcard include/sista/*.hpp) $(wildcard include/sista/*.h) sista.cpp

dist:
	git archive --format=tar.gz --prefix=$(DIST_NAME)/ -o $(DIST_ARCHIVE) HEAD

objects objects_dynamic: $(OBJECTS)

# Compiles all the library files into object files, then links them to the executable
sista: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXSTD) $(CXXFLAGS) -c sista.cpp
	$(CXX) $(LDFLAGS) -o sista sista.o $(OBJECTS)

# Compiles sista.cpp and links it against the local dynamic library libSista.so
sista_against_dynamic_lib_local: libSista$(SHARED_EXT)
	$(CXX) $(CPPFLAGS) $(CXXSTD) $(CXXFLAGS) $(PICFLAGS) -c sista.cpp
	$(CXX) $(LDFLAGS) -o sista sista.o ./libSista$(SHARED_EXT)

# Links Sista statically while retaining dynamic system dependencies
sista_against_static_lib_local: libSista.a
	$(CXX) $(CPPFLAGS) $(CXXSTD) $(CXXFLAGS) -c sista.cpp
	$(CXX) $(LDFLAGS) -o sista sista.o libSista.a

# Compiles sista.cpp and links it against the system dynamic library libSista.so
sista_against_dynamic_lib_shared:
	$(CXX) $(CPPFLAGS) $(CXXSTD) $(CXXFLAGS) $(PICFLAGS) -c sista.cpp
	$(CXX) $(LDFLAGS) -o sista sista.o -lSista

# Links the installed Sista archive while retaining dynamic system dependencies
sista_against_static_lib_shared:
	$(CXX) $(CPPFLAGS) $(CXXSTD) $(CXXFLAGS) -c sista.cpp
	$(CXX) $(LDFLAGS) -o sista sista.o "$(LIBDIR)/libSista.a"

%.o: include/sista/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXSTD) $(CXXFLAGS) $(PICFLAGS) -c $< -o $@

api.o: include/sista/api.h include/sista/api.cpp
	$(CXX) $(CPPFLAGS) $(CXXSTD) $(CXXFLAGS) $(PICFLAGS) -Iinclude -c include/sista/api.cpp -o api.o

libSista.so: libSista.so.$(FULL_VERSION)
	ln -sf libSista.so.$(FULL_VERSION) libSista.so.$(MAJOR_VERSION)
	ln -sf libSista.so.$(MAJOR_VERSION) libSista.so

libSista.so.$(FULL_VERSION): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(PICFLAGS) -shared -o libSista.so.$(FULL_VERSION) $(OBJECTS) -Wl,-soname,libSista.so.$(MAJOR_VERSION)

libSista_api.so: libSista_api.so.$(FULL_VERSION)
	ln -sf libSista_api.so.$(FULL_VERSION) libSista_api.so.$(MAJOR_VERSION)
	ln -sf libSista_api.so.$(MAJOR_VERSION) libSista_api.so

libSista_api.so.$(FULL_VERSION): api.o libSista.so
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(PICFLAGS) -shared -o libSista_api.so.$(FULL_VERSION) api.o libSista.so.$(FULL_VERSION) -lstdc++ -Wl,-soname,libSista_api.so.$(MAJOR_VERSION)

ifeq "$(shell uname -s)" "Darwin"
libSista.dylib: libSista.dylib.$(FULL_VERSION)
	ln -sf libSista.dylib.$(FULL_VERSION) libSista.dylib.$(MAJOR_VERSION)
	ln -sf libSista.dylib.$(MAJOR_VERSION) libSista.dylib

libSista.dylib.$(FULL_VERSION): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -dynamiclib -o libSista.dylib.$(FULL_VERSION) $(OBJECTS) \
	-Wl,-install_name,@rpath/libSista.dylib,-current_version,$(MAJOR_VERSION),-compatibility_version,$(MAJOR_VERSION),-rpath,$(PREFIX)/lib

libSista_api.dylib: libSista_api.dylib.$(FULL_VERSION)
	ln -sf libSista_api.dylib.$(FULL_VERSION) libSista_api.dylib.$(MAJOR_VERSION)
	ln -sf libSista_api.dylib.$(MAJOR_VERSION) libSista_api.dylib

libSista_api.dylib.$(FULL_VERSION): api.o libSista.dylib
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -dynamiclib -o libSista_api.dylib.$(FULL_VERSION) api.o libSista.dylib.$(FULL_VERSION) \
	-Wl,-install_name,@rpath/libSista_api.dylib,-current_version,$(MAJOR_VERSION),-compatibility_version,$(MAJOR_VERSION),-rpath,$(PREFIX)/lib
endif

ifeq ($(OS),Windows_NT) # Assumes usage of MinGW on Windows
libSista.dll: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared -o libSista.dll $(OBJECTS) -Wl,--out-implib,libSista.lib

libSista_api.dll: api.o libSista.dll
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared -o libSista_api.dll api.o libSista.dll -Wl,--out-implib,libSista_api.lib
endif

libSista.a: $(OBJECTS)
	$(AR) rcs libSista.a $(OBJECTS)
	$(RANLIB) libSista.a

libSista_api.a: api.o
	$(AR) rcs libSista_api.a api.o
	$(RANLIB) libSista_api.a

ifeq ($(OS),Windows_NT)
mostlyclean:
	-del /F /Q *.o 2>NUL

clean: mostlyclean
	-del /F /Q sista sista.exe libSista.a libSista.dll libSista.lib libSista_api.a libSista_api.dll libSista_api.lib 2>NUL

distclean: clean
	@if exist docs\html rmdir /S /Q docs\html
	@if exist docs\latex rmdir /S /Q docs\latex

maintainer-clean:
	@echo This command is intended for maintainers to use; it
	@echo deletes files that may need special tools to rebuild.
	$(MAKE) distclean
	-del /F /Q TAGS $(DIST_ARCHIVE) 2>NUL
else
mostlyclean:
	rm -f *.o

clean: mostlyclean
	rm -f sista libSista.so* libSista.a libSista.dylib* libSista.dll libSista.lib libSista_api.so* libSista_api.a libSista_api.dylib* libSista_api.dll libSista_api.lib

distclean: clean
	rm -rf docs/html docs/latex

maintainer-clean:
	@echo 'This command is intended for maintainers to use; it'
	@echo 'deletes files that may need special tools to rebuild.'
	$(MAKE) distclean
	rm -f TAGS $(DIST_ARCHIVE)
endif

ifeq ($(OS),Windows_NT)
install: libSista.dll libSista.a libSista_api.dll libSista_api.a install-man
	@echo "Installing Sista version $(FULL_VERSION) to $(PREFIX)..."
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
	del "$(PREFIX)\lib\libSista_api.dll"
	del "$(PREFIX)\lib\libSista_api.lib"
	del "$(PREFIX)\lib\libSista_api.a"
	@if exist "$(PREFIX)\include\sista" rmdir /S /Q "$(PREFIX)\include\sista"
	@if exist "$(docdir)" rmdir /S /Q "$(docdir)"
	@if exist "$(man3dir)\sista*.3" del /F /Q "$(man3dir)\sista*.3"
	@if exist "$(man3dir)\ANSISettings.3" del /F /Q "$(man3dir)\ANSISettings.3" "$(man3dir)\RGBColor.3" "$(man3dir)\Border.3" "$(man3dir)\Coordinates.3" "$(man3dir)\Cursor.3" "$(man3dir)\Field.3" "$(man3dir)\Path.3" "$(man3dir)\SwappableField.3" "$(man3dir)\Pawn.3" "$(man3dir)\getVersion.3"
	@if exist "$(man7dir)\sista.7" del /F /Q "$(man7dir)\sista.7"
	REM remove MSVC-friendly names as well
	del "$(PREFIX)\lib\Sista.lib" || @rem
	del "$(PREFIX)\lib\Sista_api.lib" || @rem
else ifeq "$(shell uname -s)" "Darwin"
install: libSista.dylib libSista.a libSista_api.dylib libSista_api.a install-man
	@echo "Installing Sista version $(FULL_VERSION) to $(PREFIX)..."
	$(INSTALL_DATA) libSista.dylib.$(FULL_VERSION) $(DESTDIR)$(libdir)/
	$(INSTALL_DATA) libSista_api.dylib.$(FULL_VERSION) $(DESTDIR)$(libdir)/
	ln -sf libSista.dylib.$(FULL_VERSION) $(DESTDIR)$(libdir)/libSista.dylib.$(MAJOR_VERSION)
	ln -sf libSista.dylib.$(MAJOR_VERSION) $(DESTDIR)$(libdir)/libSista.dylib
	ln -sf libSista_api.dylib.$(FULL_VERSION) $(DESTDIR)$(libdir)/libSista_api.dylib.$(MAJOR_VERSION)
	ln -sf libSista_api.dylib.$(MAJOR_VERSION) $(DESTDIR)$(libdir)/libSista_api.dylib
	$(INSTALL_DATA) libSista.a $(DESTDIR)$(libdir)/
	$(INSTALL_DATA) libSista_api.a $(DESTDIR)$(libdir)/
	$(INSTALL_DATA) include/sista/*.hpp $(DESTDIR)$(includedir)/sista/
	$(INSTALL_DATA) include/sista/*.h $(DESTDIR)$(includedir)/sista/

uninstall:
	rm -f $(DESTDIR)$(libdir)/libSista.dylib
	rm -f $(DESTDIR)$(libdir)/libSista.dylib.*
	rm -f $(DESTDIR)$(libdir)/libSista_api.dylib
	rm -f $(DESTDIR)$(libdir)/libSista_api.dylib.*
	rm -f $(DESTDIR)$(libdir)/libSista.a
	rm -f $(DESTDIR)$(libdir)/libSista_api.a
	rm -rf $(DESTDIR)$(includedir)/sista $(DESTDIR)$(docdir)
	rm -f $(DESTDIR)$(man3dir)/sista*.3 $(DESTDIR)$(man7dir)/sista.7
	@for spec in $(MAN_ALIAS_SPECS); do alias=$${spec%%=*}; rm -f "$(DESTDIR)$(man3dir)/$$alias.3"; done
else
install: libSista.so libSista.a libSista_api.so libSista_api.a install-man
	@echo "Staged install to '$(DESTDIR)$(PREFIX)' (use DESTDIR for packaging)"
	$(INSTALL_DATA) libSista.so.$(FULL_VERSION) $(DESTDIR)$(libdir)/
	$(INSTALL_DATA) libSista_api.so.$(FULL_VERSION) $(DESTDIR)$(libdir)/
	ln -sf libSista_api.so.$(FULL_VERSION) $(DESTDIR)$(libdir)/libSista_api.so.$(MAJOR_VERSION)
	ln -sf libSista_api.so.$(MAJOR_VERSION) $(DESTDIR)$(libdir)/libSista_api.so
	ln -sf libSista.so.$(FULL_VERSION) $(DESTDIR)$(libdir)/libSista.so.$(MAJOR_VERSION)
	ln -sf libSista.so.$(MAJOR_VERSION) $(DESTDIR)$(libdir)/libSista.so
	$(INSTALL_DATA) libSista.a $(DESTDIR)$(libdir)/
	$(INSTALL_DATA) libSista_api.a $(DESTDIR)$(libdir)/
	$(INSTALL_DATA) include/sista/*.hpp $(DESTDIR)$(includedir)/sista/ || true
	$(INSTALL_DATA) include/sista/*.h $(DESTDIR)$(includedir)/sista/ || true
	# write ld.so config into the package tree (do not modify the real system)
	install -d $(DESTDIR)/etc/ld.so.conf.d
	printf '%s\n' '$(libdir)' > $(DESTDIR)/etc/ld.so.conf.d/sista.conf
	# only update the real system if DESTDIR is empty (interactive install)
	if [ -z "$(DESTDIR)" ]; then \
	  if command -v sudo >/dev/null 2>&1; then \
	    echo "$(libdir)" | sudo tee /etc/ld.so.conf.d/sista.conf; \
	    sudo ldconfig || true; \
	  else \
	    echo "$(libdir)" | tee /etc/ld.so.conf.d/sista.conf; \
	    ldconfig || true; \
	  fi \
	fi

uninstall:
	rm -f $(DESTDIR)$(libdir)/libSista.so
	rm -f $(DESTDIR)$(libdir)/libSista.so.*
	rm -f $(DESTDIR)$(libdir)/libSista_api.so
	rm -f $(DESTDIR)$(libdir)/libSista_api.so.*
	rm -f $(DESTDIR)$(libdir)/libSista.a
	rm -f $(DESTDIR)$(libdir)/libSista_api.a
	rm -rf $(DESTDIR)$(includedir)/sista $(DESTDIR)$(docdir)
	rm -f $(DESTDIR)$(man3dir)/sista*.3 $(DESTDIR)$(man7dir)/sista.7
	@for spec in $(MAN_ALIAS_SPECS); do alias=$${spec%%=*}; rm -f "$(DESTDIR)$(man3dir)/$$alias.3"; done
	rm -f $(DESTDIR)/etc/ld.so.conf.d/sista.conf
	if [ -z "$(DESTDIR)" ]; then \
	  if command -v sudo >/dev/null 2>&1; then \
	    sudo ldconfig || true; \
	  else \
	    ldconfig || true; \
	  fi \
	fi
endif

ifeq ($(OS),Windows_NT)
installdirs:
	@if not exist "$(PREFIX)" mkdir "$(PREFIX)"
	@if not exist "$(PREFIX)\lib" mkdir "$(PREFIX)\lib"
	@if not exist "$(PREFIX)\include\sista" mkdir "$(PREFIX)\include\sista"
	@if not exist "$(htmldir)" mkdir "$(htmldir)"
	@if not exist "$(dvidir)" mkdir "$(dvidir)"
	@if not exist "$(pdfdir)" mkdir "$(pdfdir)"
	@if not exist "$(psdir)" mkdir "$(psdir)"
	@if not exist "$(infodir)" mkdir "$(infodir)"
	@if not exist "$(man3dir)" mkdir "$(man3dir)"
	@if not exist "$(man7dir)" mkdir "$(man7dir)"

install-man: man installdirs
	copy docs\man\*.3 "$(man3dir)\"
	copy docs\man\*.7 "$(man7dir)\"
	@for %S in ($(MAN_ALIAS_SPECS)) do @for /F "tokens=1,2 delims==" %A in ("%S") do @copy /Y "$(man3dir)\%B" "$(man3dir)\%A.3" >NUL

install-html: html installdirs
	xcopy /E /I /Y docs\html "$(htmldir)"

install-strip: install
	$(STRIP) "$(PREFIX)\lib\libSista.dll" "$(PREFIX)\lib\libSista_api.dll"

installcheck:
	$(MAKE) -B -C demo api-test-errors PREFIX="$(DESTDIR)$(PREFIX)" LIBDIR="$(DESTDIR)$(PREFIX)\lib"
	set "PATH=$(DESTDIR)$(PREFIX)\lib;%PATH%" && demo\api-test-errors.exe
else
installdirs:
	$(MKDIR_P) $(DESTDIR)$(libdir) $(DESTDIR)$(includedir)/sista
	$(MKDIR_P) $(DESTDIR)$(htmldir) $(DESTDIR)$(dvidir) $(DESTDIR)$(pdfdir) $(DESTDIR)$(psdir) $(DESTDIR)$(infodir)
	$(MKDIR_P) $(DESTDIR)$(man3dir)
	$(MKDIR_P) $(DESTDIR)$(man7dir)

install-man: man installdirs
	$(INSTALL_DATA) $(MAN3_PAGES) $(DESTDIR)$(man3dir)/
	$(INSTALL_DATA) $(MAN7_PAGES) $(DESTDIR)$(man7dir)/
	@for spec in $(MAN_ALIAS_SPECS); do \
		alias=$${spec%%=*}; target=$${spec#*=}; \
		ln -sf "$$target" "$(DESTDIR)$(man3dir)/$$alias.3"; \
	done

install-html: html installdirs
	cp -R docs/html/. $(DESTDIR)$(htmldir)/

ifeq "$(shell uname -s)" "Darwin"
install-strip: install
	$(STRIP) -x $(DESTDIR)$(libdir)/libSista.dylib.$(FULL_VERSION) $(DESTDIR)$(libdir)/libSista_api.dylib.$(FULL_VERSION)

installcheck:
	$(MAKE) -B -C demo api-test-errors PREFIX="$(DESTDIR)$(prefix)" LIBDIR="$(DESTDIR)$(libdir)"
	DYLD_LIBRARY_PATH="$(DESTDIR)$(libdir)" ./demo/api-test-errors
else
install-strip: install
	$(STRIP) --strip-unneeded $(DESTDIR)$(libdir)/libSista.so.$(FULL_VERSION) $(DESTDIR)$(libdir)/libSista_api.so.$(FULL_VERSION)

installcheck:
	$(MAKE) -B -C demo api-test-errors PREFIX="$(DESTDIR)$(prefix)" LIBDIR="$(DESTDIR)$(libdir)"
	LD_LIBRARY_PATH="$(DESTDIR)$(libdir)" ./demo/api-test-errors
endif
endif

install-info: info installdirs
	@echo 'Sista has no Info manual to install.'

install-dvi: dvi installdirs
	@echo 'Sista has no DVI manual to install.'

install-pdf: pdf installdirs
	@echo 'Sista has no PDF manual to install.'

install-ps: ps installdirs
	@echo 'Sista has no PostScript manual to install.'

.PHONY: all build check test check-man info dvi html man pdf ps dist objects objects_dynamic mostlyclean clean distclean maintainer-clean install install-html install-man install-dvi install-pdf install-ps install-info install-strip uninstall installcheck installdirs sista_against_dynamic_lib_local sista_against_static_lib_local sista_against_dynamic_lib_shared sista_against_static_lib_shared
