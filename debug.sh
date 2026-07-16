#! /usr/bin/env bash

DEBUG=$1
SUITE=$2
TEST=$3

case $1 in
    "list")
        ./runner --gtest_list_tests
    ;;
    "fail")
        lldb ./runner -- \
             --gtest_filter=${SUITE}.${TEST} \
             --gtest_break_on_failure \
             --gtest_catch_exceptions=0
    ;;
   "start")
       lldb ./runner \
           -o "breakpoint set --name ${SUITE}_${TEST}_Test::TestBody" \
           -- \
           --gtest_filter="${SUITE}.${TEST}" \
           --gtest_break_on_failure \
           --gtest_catch_exceptions=0
   ;;
   *)
       echo >/dev/stderr "unknown command $1"
   ;;
esac
