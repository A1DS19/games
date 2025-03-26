#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <directory-name>"
  exit 1
fi

mkdir -p "$1/bin"
cd "$1"

cat > Makefile <<EOF
all:
$(echo -e "\tmkdir -p ./bin")
$(echo -e "\tg++ main.cpp -o ./bin/main")
EOF

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
