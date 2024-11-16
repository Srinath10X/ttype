CXX = g++
CXXFLAGS = -g -Wall -Werror

SRC_FILE = src/main.cpp
BIN_FILE_NAME = ttype
ARCH = $(shell uname -m)
BIN_NAME_WITH_ARCH = $(BIN_FILE_NAME)-$(ARCH)

INSTALL_DIR = $(HOME)/.local/bin/
BUILD_DIR = build/$(ARCH)

all: build

clean:
	rm -rf $(BUILD_DIR)

build: $(SRC_FILE)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILE) -o $(BUILD_DIR)/$(BIN_NAME_WITH_ARCH)

install: build
	mkdir -p $(INSTALL_DIR)
	mv -f $(BUILD_DIR)/$(BIN_NAME_WITH_ARCH) $(INSTALL_DIR)/$(BIN_FILE_NAME)

run: $(BUILD_DIR)/$(BIN_NAME_WITH_ARCH)
	./$(BUILD_DIR)/$(BIN_NAME_WITH_ARCH)

$(BUILD_DIR)/$(BIN_NAME_WITH_ARCH): $(SRC_FILE)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILE) -o $(BUILD_DIR)/$(BIN_NAME_WITH_ARCH)

.PHONY: all clean build install run check
