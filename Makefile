#
# compiler
# 

CXX ?= clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src  -pthread
LDFLAGS = -ledit -lncurses

AR = ar
ARFLAGS = rcs

MAIN_AR = core.ar

#
# source
#

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = cmix

# Compile .cpp -> obj/.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# build static lib
$(MAIN_AR): $(OBJS)
	$(AR) $(ARFLAGS) $(OBJ_DIR)/$(MAIN_AR) $(OBJS)

# Link step
$(TARGET): $(OBJ_DIR)/$(MAIN_AR) cmix.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

#
# testing
#

GOOGLE_TEST=../googletest

TEST_FLAGS := $(CXXFLAGS) -I$(GOOGLE_TEST)/googletest/include
TEST_LDFLAGS := $(LDFLAGS)

TEST_RUNNER = $(GOOGLE_TEST)/lib/libgtest_main.a

TEST_TARGET = test_runner

TESTS_SRC_DIR = test/src

TEST_SRCS = $(wildcard $(TESTS_SRC_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTS_SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TESTS_SRCS))

#
# compile tests
#

$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CXX) $(TEST_FLAGS) -c $< -o $@

#
# compile test runner
# 

$(TEST_TARGET): $(TEST_OBJS) $(OBJS) $(TEST_RUNNER)
	$(CXX) $(TEST_FLAGS) -o $@ $^ $(TEST_LDFLAGS)

tests: $(TEST_TARGET)

all: $(TARGET) $(TEST_TARGET)

clean:
	rm -f $(OBJ_DIR)/* $(TARGET) $(TEST_TARGET)

.PHONY: clean
