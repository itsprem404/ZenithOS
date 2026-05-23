CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = zenithos

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking executable..."
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build complete! Run: ./$(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Clean complete!"

rebuild: clean all

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

.PHONY: all run clean rebuild debug