CXX := C:/mingw32/bin/g++.exe

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/crypto.exe

CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2 -D_WIN32_WINNT=0x0A00
INCLUDES := -Iinclude
LDLIBS := -lws2_32

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(TARGET)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDLIBS)

run: $(TARGET)
	$(TARGET)

clean:
	if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"

rebuild: clean all

.PHONY: all run clean rebuild