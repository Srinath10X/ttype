CXX = g++
CXXFLAGS = -g -Wall -Werror

LIBS = -lncurses
SRC_FILE = src/main.cpp
BIN_FILE_NAME = ttype 

all: main

main: $(SRC_FILE)
	$(CXX) $(CXXFLAGS) $(SRC_FILE) $(LIBS) -o $(BIN_FILE_NAME)

install: 
	mkdir -p $(HOME)/.local/bin/
	mv $(BIN_FILE_NAME) $(HOME)/.local/bin/

build: $(SRC_FILE)
	$(CXX) $(CXXFLAGS) $(SRC_FILE) -o $(BIN_FILE_NAME)
	mkdir -p $(HOME)/.local/bin/
	mv $(BIN_FILE_NAME) $(HOME)/.local/bin/

clean:
	rm -f $(BIN_FILE_NAME)
