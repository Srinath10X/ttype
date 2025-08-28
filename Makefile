CXX = g++
CXXFLAGS = -g -Wall -Werror -I include

SRC_FILES = src/main.cpp \
						src/handlers/terminal_handler.cpp \
						src/handlers/ui_handler.cpp \
						src/modules/timer.cpp \
						src/modules/text_generator.cpp

BIN_FILE_NAME = ttype
ARCH = $(shell uname -m)
BIN_NAME_WITH_ARCH = $(BIN_FILE_NAME)-$(ARCH)

BUILD_DIR = build
INSTALL_DIR = /usr/bin

all: build

clean:
	rm -rf $(BUILD_DIR)

build: $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(BIN_NAME_WITH_ARCH)

install: build
	mkdir -p $(INSTALL_DIR)
	mv -f $(BUILD_DIR)/$(BIN_NAME_WITH_ARCH) $(INSTALL_DIR)/$(BIN_FILE_NAME)

run: $(BUILD_DIR)/$(BIN_NAME_WITH_ARCH)
	./$(BUILD_DIR)/$(BIN_NAME_WITH_ARCH)

$(BUILD_DIR)/$(BIN_NAME_WITH_ARCH): $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(BIN_NAME_WITH_ARCH)

.PHONY: all clean build install run
