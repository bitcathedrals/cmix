
#
# common
#

MAX_ERRORS = 6
MAX_BACKTRACE=4

DIAGNOSTICS = -Wall -Wextra -Werror -fcolor-diagnostics -ferror-limit=$(MAX_ERRORS) -ftemplate-backtrace-limit=$(MAX_BACKTRACE)

CXX ?= clang++
CXXFLAGS = -std=c++20 $(DIAGNOSTICS) -I$(SRC_DIR) -pthread
LDFLAGS = -ledit -lncurses

AR = ar
ARFLAGS = rcs

MAIN_AR = core.a

#
# production
# 

SRC_DIR = src
OBJ_DIR = .build/prod

SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

PROD = cmix

OPT_FLAGS ?= -O3 -flto

# Compile .cpp -> obj/.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OPT_FLAGS) -c $< -o $@

# cmix.o main() conflicts with entry points like googletest
WITHOUT_CMIX_MAIN=$(filter-out $(OBJ_DIR)/cmix.o, $(OBJS))

# build static lib
$(OBJ_DIR)/$(MAIN_AR): $(WITHOUT_CMIX_MAIN)
	$(AR) $(ARFLAGS) $(OBJ_DIR)/$(MAIN_AR) $(WITHOUT_CMIX_MAIN)

# Link step
$(TARGET): $(OBJ_DIR)/$(MAIN_AR) $(OBJ_DIR)/cmix.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -flto $(LDFLAGS)

#
# debug - same build technique as production but with debugging
#

DBG_OBJ_DIR = .build/dbg

DEBUG_FLAGS = -g -O0 -fsanitize=address

DBG_SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
DBG_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(DBG_OBJ_DIR)/%.o,$(SRCS))

DEBUG = dbg

# Compile .cpp -> obj/.o
$(DBG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# cmix.o main() conflicts with entry points like googletest
DBG_WITHOUT_CMIX_MAIN=$(filter-out $(DBG_OBJ_DIR)/cmix.o, $(DBG_OBJS))

# build static lib
$(DBG_OBJ_DIR)/$(MAIN_AR): $(DBG_WITHOUT_CMIX_MAIN)
	$(AR) $(ARFLAGS) $(DBG_OBJ_DIR)/$(MAIN_AR) $(DBG_WITHOUT_CMIX_MAIN)

# Link step
$(DEBUG): $(DBG_OBJ_DIR)/$(MAIN_AR) $(DBG_OBJ_DIR)/cmix.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(DEBUG_FLAGS) $(LDFLAGS)

#
# testing
#

GOOGLE_TEST=vendor/googletest

TEST_FLAGS = -I$(GOOGLE_TEST)/googletest/include -I$(TEST_DIR) $(CXXFLAGS)
TEST_LDFLAGS = -L$(GOOGLE_TEST)/lib -lgtest -lgtest_main

TEST_TARGET = run-tests

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
	$(CXX) $(TEST_FLAGS) -o $@ $^ $(TEST_LDFLAGS) -ledit

# project scope

tests: $(TEST_TARGET)

debug: $(DEBUG)

default: $(PROD)

clean:
	rm -rf .build $(TARGET) $(DEBUG_TARGET) $(TEST_TARGET)

.PHONY: clean
