CXX = g++
CXXFLAGS = -g -Wall -Werror

SRC_FILE = src/main.cpp
BIN_FILE_NAME = ttype
INSTALL_DIR = $(HOME)/.local/bin/

all: build

build: $(SRC_FILE)
	$(CXX) $(CXXFLAGS) $(SRC_FILE) -o $(BIN_FILE_NAME)

install: build
	mkdir -p $(INSTALL_DIR)
	mv -f $(BIN_FILE_NAME) $(INSTALL_DIR)

check: build
	./$(BIN_FILE_NAME) || echo "Check failed!"

clean:
	rm -f $(BIN_FILE_NAME)
