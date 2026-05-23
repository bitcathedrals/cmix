OS := $(shell uname -s)

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

# commonly used for most builds

SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

#
# production
# 

OBJ_DIR = .build/prod

PROD_TARGET = cmix

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
$(PROD_TARGET): $(OBJ_DIR)/$(MAIN_AR) $(OBJ_DIR)/cmix.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -flto $(LDFLAGS)

#
# test
#

GOOGLE_TEST = vendor/googletest

TEST_DIR = tests/


ifeq ($(OS),OpenBSD) 
TEST_RUNTIME = 
TEST_COVERAGE_FLAGS = 
else
TEST_RUNTIME = -fsanitize=address
TEST_COVERAGE_FLAGS = -g -fcoverage-mapping -fprofile-instr-generate
endif

TEST_FLAGS = -I$(GOOGLE_TEST)/googletest/include -I$(TEST_DIR) $(CXXFLAGS) $(TEST_RUNTIME) $(TEST_COVERAGE_FLAGS)
TEST_LDFLAGS = $(TEST_RUNTIME) -L$(GOOGLE_TEST)/lib $(TEST_COVERAGE_FLAGS) -lgtest -lgtest_main

TEST_TARGET = runner

TEST_DIR = tests/
TEST_OBJ = .build/test

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp $(TEST_DIR)/*/*.cpp $(TEST_DIR)/*/*/*.cpp)

TEST_CORE_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(TEST_OBJ)/%.o,$(SRCS))
TEST_SUITE_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(TEST_OBJ)/%.o,$(TEST_SRCS))

WITHOUT_MAIN=$(filter-out $(TEST_OBJ)/cmix.o , $(TEST_CORE_OBJS))

TEST_SUITE_AR = $(TEST_OBJ)/test-suite.a
TEST_CORE_AR = $(TEST_OBJ)/test-core.a

# test suite .a

$(TEST_OBJ)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -c $< -o $@

$(TEST_SUITE_AR): $(TEST_SUITE_OBJS)
	$(AR) $(ARFLAGS) $(TEST_SUITE_AR) $(TEST_SUITE_OBJS)

# app core .a

$(TEST_OBJ)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -c $< -o $@

$(TEST_CORE_AR): $(WITHOUT_MAIN)
	$(AR) $(ARFLAGS) $(TEST_CORE_AR) $(WITHOUT_MAIN)

# using the .a files is broken for now.
#  $(TEST_TARGET): $(TEST_SUITE_AR) $(TEST_CORE_AR)

$(TEST_TARGET):  $(TEST_SUITE_OBJS) $(WITHOUT_MAIN)
	$(CXX) -o $@ $^ $(TEST_LDFLAGS) -ledit

ifeq ($(OS),Darwin) 
XCRUN = xcrun
else
XCRUN = 
endif

coverage:
	$(XCRUN) llvm-profdata merge -sparse *.profraw -o final.profdata
	$(XCRUN) llvm-cov show -instr-profile=final.profdata ./runner >coverage.txt

#
# debug - same build technique as production but with debugging
#

DBG_OBJ_DIR = .build/dbg

DEBUG_FLAGS = -g -O0

DBG_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(DBG_OBJ_DIR)/%.o,$(SRCS))

DEBUG_TARGET = dbg

$(DBG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# build

$(DEBUG_TARGET): $(DBG_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(DEBUG_FLAGS) $(LDFLAGS)

#
# perf
# 

PERF_OBJ = .build/perf

#ifdef DO_PROFILE
PERF_PROFILE_FLAGS = -fprofile-instr-generate
#endif

#ifdef DO_OPTMIZE
PERF_PROFILE_FLAGS = -fprofile-generate
#endif

PERF_FLAGS = -Isrc -g -O2 -fno-omit-frame-pointer $(PERF_PROFILE_FLAGS)

PERF_BUILD = $(patsubst $(SRC_DIR)/%.cpp,$(PERF_OBJ)/%.o,$(SRCS))

PERF_TARGET = perf

# Compile .cpp -> obj/.o
$(PERF_OBJ)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(PERF_FLAGS) -c $< -o $@

# Link step
$(PERF_TARGET): $(PERF_BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(PERF_FLAGS) $(LDFLAGS)

#
# project scope
#

prod: $(PROD_TARGET)

test: $(TEST_TARGET)

debug: $(DEBUG_TARGET)

profile: $(PERF_TARGET)

default: prod

prod-clean:
	-rm -rf $(OBJ_DIR)
	-rm -f $(PROD_TARGET)

test-clean:
	-rm -f $(TEST_TARGET)
	-rm -rf $(TEST_OBJ)
	-rm -f *.profraw
	-rm -f *.profdata

debug-clean:
	-rm -f $(DEBUG_TARGET)
	-rm -rf $(DBG_OBJ_DIR)

perf-clean:
	-rm -rf $(PERF_OBJ)
	-rm -f $(PERF_TARGET)

clean: prod-clean test-clean debug-clean perf-clean

.PHONY: prod-clean test-clean debug-clean perf-clean default

# $(info TEST_SRCS is $(TEST_SRCS))
# $(info TEST_OBJS is $(TEST_OBJS))
