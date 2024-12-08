#!/bin/bash

# Get the project name from CMakeLists.txt
project_name=$(grep "project(" CMakeLists.txt | sed 's/project(\([^ ]*\).*/\1/')

# Ensure we're in the build directory
if [[ $(basename "$PWD") != "build" ]]; then
    if [[ -d "build" ]]; then
        cd build
    else
        echo "Error: No build directory found"
        exit 1
    fi
fi

# Run cmake
echo "Running CMake..."
cmake ..

# Run make
echo "Building project..."
make

# Check if make was successful
if [ $? -eq 0 ]; then
    echo "Build successful! Running program..."
    ./"$project_name"
else
    echo "Build failed!"
    exit 1
fi
