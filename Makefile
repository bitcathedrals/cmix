OS := $(shell uname -s)

#
# common
#

PROD_GOAL = prod
TEST_GOAL = test
DEBUG_GOAL = debug
PERF_GOAL = benchmark

MAX_ERRORS=3
MAX_BACKTRACE=4

CORE_DIAGNOSTICS = -Wall -Wextra -Werror -ftemplate-backtrace-limit=$(MAX_BACKTRACE)

ifeq ($(CXX), g++)
DIAGNOSTICS = $(CORE_DIAGNOSTICS) -fdiagnostics-color=never -fmax-errors=$(MAX_ERRORS)
else
DIAGNOSTICS = $(CORE_DIAGNOSTICS) -ferror-limit=$(MAX_ERRORS) 
endif

CXX ?= clang++
CXXFLAGS = -g -std=c++20 $(DIAGNOSTICS) -I$(SRC_DIR) -pthread -MMD
LDFLAGS = -ledit -lncurses

#
# Production
#

SRC_DIR = src
OBJ_DIR = .build/prod

SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

ifneq ($(findstring $(PROD_GOAL), $(MAKECMDGOALS)),)
  DFILES = $(wildcard $(OBJ_DIR)/*.d $(OBJ_DIR)/*/*.d $(OBJ_DIR)/*/*/*.d)

  ifneq ($(DFILES),)
    include $(DFILES)
  endif
endif

PROD_TARGET = cmix

OPT_FLAGS ?= -O3 -flto -ffunction-sections -fdata-sections

ifeq ($(CXX),g++) 
OPT_FLAGS=$(OPT_FLAGS) -Wl,--gc-sections
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OPT_FLAGS) -c $< -o $@

$(PROD_TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(OPT_FLAGS) $(LDFLAGS)

#
# test
#

GOOGLE_TEST = vendor/googletest

TEST_DIR = tests/

ifeq ($(OS),OpenBSD) 
TEST_RUNTIME = 
TEST_COVERAGE_FLAGS = 
else ifeq ($(OS), Linux)
TEST_COVERAGE_FLAGS = -O0 -g --coverage
else
TEST_COVERAGE_FLAGS = -O0 -g -fcoverage-mapping -fprofile-instr-generate
TEST_RUNTIME = -fsanitize=address
endif

TEST_FLAGS = -I$(GOOGLE_TEST)/googletest/include $(TEST_RUNTIME) $(TEST_COVERAGE_FLAGS)
TEST_LDFLAGS = $(TEST_RUNTIME) -L$(GOOGLE_TEST)/lib $(TEST_COVERAGE_FLAGS) -lgtest -lgtest_main

TEST_TARGET = runner

TEST_DIR = tests/
TEST_OBJ = .build/test

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp $(TEST_DIR)/*/*.cpp $(TEST_DIR)/*/*/*.cpp)

TEST_CORE_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(TEST_OBJ)/%.o,$(SRCS))
TEST_SUITE_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(TEST_OBJ)/%.o,$(TEST_SRCS))

TEST_WITHOUT_MAIN=$(filter-out $(TEST_OBJ)/cmix.o , $(TEST_CORE_OBJS))

ifneq ($(findstring $(TEST_GOAL), $(MAKECMDGOALS)),)
  TEST_DFILES = $(wildcard $(TEST_OBJ)/*.d $(TEST_OBJ)/*/*.d $(TEST_OBJ)/*/*/*.d)
  ifneq ($(TEST_DFILES),)
    include $(TEST_DFILES)
  endif
endif

$(TEST_OBJ)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -c $< -o $@

$(TEST_OBJ)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -c $< -o $@

$(TEST_TARGET):  $(TEST_SUITE_OBJS) $(TEST_WITHOUT_MAIN)
	$(CXX) -o $@ $^ $(TEST_LDFLAGS) -ledit

ifeq ($(OS),Darwin) 
XCRUN = xcrun
else
XCRUN = 
endif

run:
	find $(TEST_OBJ) -name '*.gcda' -print | xargs rm
	./runner

coverage:
	$(XCRUN) llvm-profdata merge -sparse *.profraw -o final.profdata
	$(XCRUN) llvm-cov show -ignore-filename-regex "vendor/*" -instr-profile=final.profdata ./runner >coverage.txt

#
# perf
# 

PERF_DIR = perf/
PERF_OBJ = .build/perf

ifeq ($(DO_PROFILE), 1)
PERF_PROFILE_FLAGS = -fprofile-instr-generate
endif

ifeq ($(DO_OPTMIZE), 1)
PERF_PROFILE_FLAGS = -fprofile-generate
endif

PERF_FLAGS = -O2 -fno-omit-frame-pointer $(PERF_PROFILE_FLAGS)

PERF_SRCS = $(wildcard $(PERF_DIR)/*.cpp $(PERF_DIR)/*/*.cpp $(PERF_DIR)/*/*/*.cpp)

PERF_CORE_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(PERF_OBJ)/%.o,$(SRCS))
PERF_BENCH_OBJS = $(patsubst $(PERF_DIR)/%.cpp,$(PERF_OBJ)/%.o,$(PERF_SRCS))

PERF_OBJS = $(PERF_CORE_OBJS) $(PERF_BENCH_OBJS)

ifneq ($(findstring $(PERF_GOAL), $(MAKECMDGOALS)),)
	PERF_DFILES = $(wildcard $(PERF_OBJ)/*.d $(PERF_OBJ)/*/*.d $(PERF_OBJ)/*/*/*.d)

  ifneq ($(PERF_DFILES),)
    include $(PERF_DFILES)
  endif
endif

PERF_TARGET = bench

PERF_WITHOUT_MAIN=$(filter-out $(PERF_OBJ)/cmix.o , $(PERF_OBJS))

$(PERF_OBJ)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(PERF_FLAGS) -c $< -o $@

$(PERF_OBJ)/%.o: $(PERF_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(PERF_FLAGS) -c $< -o $@

$(PERF_TARGET): $(PERF_WITHOUT_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(PERF_FLAGS) $(LDFLAGS)

#
# project scope
#

kloc:
	wc -l `find src tests perf debug -type f -print`

prod: $(PROD_TARGET)

test: $(TEST_TARGET)

benchmark: $(PERF_TARGET)

default: prod

prod-clean:
	-rm -rf $(OBJ_DIR)
	-rm -f $(PROD_TARGET)

test-clean:
	-rm -f $(TEST_TARGET)
	-rm -rf $(TEST_OBJ)
	-rm -f *.profraw
	-rm -f *.profdata

benchmark-clean:
	-rm -rf $(PERF_OBJ)
	-rm -f $(PERF_TARGET)

clean: prod-clean test-clean perf-clean

.PHONY: prod-clean test-clean perf-clean default

# $(info TEST_OBJS is $(TEST_OBJS))
