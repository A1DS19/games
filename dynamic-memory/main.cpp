#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int *a = new int(10);
  cout << a << endl;

  int *b = a;
  cout << b << endl;

  delete a;
  a = nullptr;

  return EXIT_SUCCESS;
}
