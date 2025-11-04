CXX := g++
CXXFLAGS := -std=c++20 -O3 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS := 

SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build

DEMO := $(BIN_DIR)/demo
TESTS := $(BIN_DIR)/tests
BENCH := $(BIN_DIR)/bench

DEMO_SRCS := $(SRC_DIR)/main.cpp
TESTS_SRCS := $(SRC_DIR)/tests.cpp
BENCH_SRCS := $(SRC_DIR)/bench.cpp

DEMO_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(DEMO_SRCS))
TESTS_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TESTS_SRCS))
BENCH_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(BENCH_SRCS))

.PHONY: all clean demo tests bench

all: demo tests bench

demo: $(DEMO)

tests: $(TESTS)

bench: $(BENCH)

$(DEMO): $(DEMO_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TESTS): $(TESTS_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BENCH): $(BENCH_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
