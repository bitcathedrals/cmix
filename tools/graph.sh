#! /usr/bin/env bash

tools/graph $1 | dot -Tpng -o graph.png
