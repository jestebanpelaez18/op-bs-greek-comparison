CXX      := g++
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -Wpedantic
INCLUDES := -Iincludes

SRC_DIR  := srcs
BIN_DIR  := bin

MAIN_SRC := $(SRC_DIR)/main.cpp
TEST_SRC := $(SRC_DIR)/tests.cpp

MAIN_BIN := $(BIN_DIR)/main
TEST_BIN := $(BIN_DIR)/tests


.PHONY: all main tests run clean fclean re

all: main

main: $(MAIN_BIN)

tests: $(TEST_BIN)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(MAIN_BIN): $(MAIN_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

ifneq ($(wildcard $(TEST_SRC)),)
$(TEST_BIN): $(TEST_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@
endif

run: main
	./$(MAIN_BIN)

clean:
	@echo "Cleaning binaries..."
	rm -f $(MAIN_BIN) $(TEST_BIN)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all


