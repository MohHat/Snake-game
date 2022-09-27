CXX?=g++

HEADERS=include/
LIB=lib/
LIB_HEADERS=lib/include/

SRC= $(wildcard src/*.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))

TARGET=build/game

CFLAGS_LINUX= -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
CFLAGS_WINDOWS = # TODO

linux: setup build-linux

build-linux: $(OBJ)
	${CXX} ${CFLAGS_LINUX} $^ -I${HEADERS} -I${LIB_HEADERS} -o ${TARGET} 

run: build-linux
	./${TARGET}

# Build object files
$(OBJ): $(SRC)
	$(CXX) $(CFLAGS-base) -c -o $@ $*.cpp

setup:
	mkdir -p build/

clean:
	rm -rf build/
	rm -rf src/*.o

.PHONY: clean
