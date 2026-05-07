#
# compiler
# 

SRC_DIR = src
OBJ_DIR = obj

CXX ?= clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(SRC_DIR)  -pthread
LDFLAGS = -ledit -lncurses

AR = ar
ARFLAGS = rcs

MAIN_AR = core.a

#
# source
#

SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = cmix

# Compile .cpp -> obj/.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# build static lib
$(OBJ_DIR)/$(MAIN_AR): $(OBJS)
	$(AR) $(ARFLAGS) $(OBJ_DIR)/$(MAIN_AR) $(OBJS)

# Link step
$(TARGET): $(OBJ_DIR)/$(MAIN_AR) cmix.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

#
# testing
#

GOOGLE_TEST=vendor/googletest

TEST_FLAGS = -I$(GOOGLE_TEST)/googletest/include -I$(TEST_DIR) $(CXXFLAGS)
TEST_LDFLAGS = -L$(GOOGLE_TEST)/lib -lgtest -lgtest_main

TEST_TARGET = test_runner

TEST_DIR = tests/

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp $(TEST_DIR)/*/*.cpp $(TEST_DIR)/*/*/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

#
# compile tests
#

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -c $< -o $@

#
# compile test runner
# 

# $(info TEST_SRCS is $(TEST_SRCS))
# $(info TEST_OBJS is $(TEST_OBJS))

$(TEST_TARGET): $(TEST_OBJS) $(OBJ_DIR)/$(MAIN_AR)
	$(CXX) $(TEST_FLAGS) -o $@ $^ $(TEST_LDFLAGS)

# project scope

tests: $(TEST_TARGET)

app: $(TARGET)

clean:
	rm -rf $(OBJ_DIR)/* $(TARGET) $(TEST_TARGET)

.PHONY: clean
