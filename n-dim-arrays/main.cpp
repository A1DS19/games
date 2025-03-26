#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int arr[2][2] = {{1, 2}, {1, 2}};

  for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
    for (size_t j = 0; j < sizeof(arr) / sizeof(arr[0]); j++) {
      cout << arr[i][j] << endl;
    }
  }

  return EXIT_SUCCESS;
}
