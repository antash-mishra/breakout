#!/bin/bash

echo "Building Project"
cmake --build build

echo "Running Executable"
cd build && ./breakout
