IMPLEMENTATIONS = ../include/sista/ansi.cpp ../include/sista/border.cpp ../include/sista/coordinates.cpp ../include/sista/cursor.cpp ../include/sista/field.cpp ../include/sista/pawn.cpp
OBJECTS = ansi.o border.o coordinates.o cursor.o field.o pawn.o
ifeq ($(OS),Windows_NT)
	PREFIX ?= C:\Program Files\Sista
	INCLUDE_PATH_DIRECTIVE = -I"$(PREFIX)\include"
	LD_LIBRARY_PATH_DIRECTIVE = -L"$(PREFIX)\lib"
else
	PREFIX ?= /usr/local
	INCLUDE_PATH_DIRECTIVE = -I$(PREFIX)/include
	LD_LIBRARY_PATH_DIRECTIVE = -L$(PREFIX)/lib
endif
ifeq "$(shell uname -s)" "Darwin"
	DYLD_LIBRARY_PATH_DIRECTIVE = -Wl,-rpath,$(PREFIX)/lib
endif

all: header-test colors24-bit colors256 conflictTest resetAttribute screen-mode swapTest verticalTest clean_objects

header-test.o:
	g++ -std=c++17 -Wall -Wno-narrowing -Wno-sign-compare -g -c header-test.cpp

header-test: header-test.o $(OBJECTS)
	g++ -std=c++17 -o header-test header-test.o $(OBJECTS)

shared-test.o:
	g++ -std=c++17 -Wall -Wno-narrowing -Wno-sign-compare -g $(INCLUDE_PATH_DIRECTIVE) -c shared-test.cpp

shared-test: shared-test.o
	g++ -std=c++17 -o shared-test shared-test.o $(LD_LIBRARY_PATH_DIRECTIVE) -lSista $(DYLD_LIBRARY_PATH_DIRECTIVE)

shared-test-static.o:
	g++ -std=c++17 -Wall -Wno-narrowing -Wno-sign-compare -g $(INCLUDE_PATH_DIRECTIVE) -c shared-test-static.cpp

shared-test-static: shared-test-static.o
	g++ -std=c++17 -static -o shared-test-static shared-test-static.o $(LD_LIBRARY_PATH_DIRECTIVE) -lSista

%.o: ../include/sista/%.cpp
	g++ -std=c++17 -Wall -g -c $< -o $@

colors24-bit: colors24-bit.cpp $(OBJECTS)
	g++ -std=c++17 -Wall -g -c colors24-bit.cpp
	g++ -std=c++17 -Wall -g -o colors24-bit colors24-bit.o $(OBJECTS)

colors256: colors256.cpp $(OBJECTS)
	g++ -std=c++17 -Wall -g -c colors256.cpp
	g++ -std=c++17 -Wall -g -o colors256 colors256.o $(OBJECTS)

conflictTest: conflictTest.cpp $(OBJECTS)
	g++ -std=c++17 -Wall -g -c conflictTest.cpp
	g++ -std=c++17 -Wall -g -o conflictTest conflictTest.o $(OBJECTS)

resetAttribute: resetAttribute.cpp $(OBJECTS)
	g++ -std=c++17 -Wall -g -c resetAttribute.cpp
	g++ -std=c++17 -Wall -g -o resetAttribute resetAttribute.o $(OBJECTS)

screen-mode: screen-mode.cpp $(OBJECTS)
	g++ -std=c++17 -Wall -g -c screen-mode.cpp
	g++ -std=c++17 -Wall -g -o screen-mode screen-mode.o $(OBJECTS)

swapTest: swapTest.cpp $(OBJECTS)
	g++ -std=c++17 -Wall -g -c swapTest.cpp
	g++ -std=c++17 -Wall -g -o swapTest swapTest.o $(OBJECTS)

verticalTest: verticalTest.cpp $(OBJECTS)
	g++ -std=c++17 -Wall -g -c verticalTest.cpp
	g++ -std=c++17 -Wall -g -o verticalTest verticalTest.o $(OBJECTS)

api-test.o: api-test.cpp
	g++ -std=c++17 -Wall -g -c api-test.cpp $(INCLUDE_PATH_DIRECTIVE)

api-test: api-test.o
	g++ -std=c++17 -Wall -g -o api-test api-test.o -lSista_api -lSista $(LD_LIBRARY_PATH_DIRECTIVE) $(DYLD_LIBRARY_PATH_DIRECTIVE)

api-test-border.o: api-test-border.cpp
	g++ -std=c++17 -Wall -g -c api-test-border.cpp $(INCLUDE_PATH_DIRECTIVE)

api-test-border: api-test-border.o
	g++ -std=c++17 -Wall -g -o api-test-border api-test-border.o -lSista_api -lSista $(LD_LIBRARY_PATH_DIRECTIVE) $(DYLD_LIBRARY_PATH_DIRECTIVE)

api-test-multiple-styles.o: api-test-multiple-styles.c
	gcc -std=c89 -Wall -g -c api-test-multiple-styles.c $(INCLUDE_PATH_DIRECTIVE)

api-test-multiple-styles: api-test-multiple-styles.o
	gcc -std=c89 -Wall -g -o api-test-multiple-styles api-test-multiple-styles.o -lSista_api $(LD_LIBRARY_PATH_DIRECTIVE) $(DYLD_LIBRARY_PATH_DIRECTIVE)

clean_objects:
	rm -f *.o

clean: clean_objects
	rm -f header-test shared-test shared-test-static colors24-bit colors256 conflictTest resetAttribute screen-mode swapTest verticalTest api-test

.PHONY: all clean_objects clean
