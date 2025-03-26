#!/bin/bash

# Check if a directory name is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <directory-name>"
  exit 1
fi

# Create the directory structure
mkdir -p "$1"/bin

# Navigate into the directory
cd "$1"

# Create Makefile
cat > Makefile << EOF
all:
\tg++ main.cpp -o ./bin/main
EOF

cat > .gitignore << EOF
/*/bin/*
EOF

# Create main.cpp
cat > main.cpp << EOF
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  cout << "hello world" << endl;
  return EXIT_SUCCESS;
}
EOF

echo "Project '$1' created successfully."

