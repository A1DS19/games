#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <directory-name>"
  exit 1
fi

mkdir -p "$1/bin"
cd "$1"

# Ensure TAB character is preserved in Makefile
cat > Makefile <<- 'EOF'
all:
	g++ main.cpp -o ./bin/main
EOF

cat > main.cpp << 'EOF'
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  cout << "hello world" << endl;
  return EXIT_SUCCESS;
}
EOF

echo "Project '$1' created successfully."
