#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <directory-name>"
  exit 1
fi

# Create necessary directories: bin, build, include, lib, scripts, and src
mkdir -p "$1"/{bin,build,include,scripts,src}
cd "$1"

# Create .gitignore file
cat > .gitignore << 'EOF'
# Ignore build artifacts
/build/
/bin/
/lib/

# Ignore generated files
compile_commands.json
.clang_complete

# Ignore editor files
*.swp
*~

# OS-specific files
.DS_Store
.cache/
EOF

# Create CMakeLists.txt
cat > CMakeLists.txt << 'EOF'
# Enable export of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name dynamically based on the folder name
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Compiler flags (e.g., debug information)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Source files (all .cpp files in the src directory)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add executable
add_executable(main ${SOURCES})

# Set the output directory for the executable
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Custom target to generate .clang_complete (optional)
add_custom_target(
  generate_clang_complete
  COMMAND python ${CMAKE_SOURCE_DIR}/scripts/cc_args.py ${CMAKE_BINARY_DIR}/compile_commands.json > ${CMAKE_SOURCE_DIR}/.clang_complete
  DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)
EOF

# Create a sample header file in include directory: main.hpp
cat > include/main.hpp << 'EOF'
#pragma once

#include <iostream>
#include <cstdlib>  

void hello();
EOF

# Create a sample source file in src directory: main.cpp
cat > src/main.cpp << 'EOF'
#include "main.hpp"

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    hello();
    return EXIT_SUCCESS;
}
EOF

# Create a minimal placeholder Python script in scripts directory: cc_args.py
cat > scripts/cc_args.py << 'EOF'
#!/usr/bin/env python
import sys

if len(sys.argv) < 2:
    sys.exit("Usage: cc_args.py <compile_commands.json>")

# This is a simple placeholder that prints the contents of compile_commands.json.
with open(sys.argv[1], 'r') as f:
    print(f.read())
EOF

# Make the Python script executable
chmod +x scripts/cc_args.py

echo "Project '$1' created successfully."
