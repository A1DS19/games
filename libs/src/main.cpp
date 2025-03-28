#include "main.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

void randomNumbers(vector<int> &numbers) {
  srand(time(NULL));
  const int MAX_NUMBERS = 100;

  for (int i = 0; i < MAX_NUMBERS; i++) {
    numbers.push_back(rand() % MAX_NUMBERS);
  }
}

bool descCompare(int a, int b) {
  if (a > b) {
    return true;
  }

  return false;
}

int main() {
  // always pass string by ref to functions otherwise it will copy
  string value = "hello";
  string value2 = "world";
  const char *cValue = value.c_str(); // c string from string

  cout << value + " " + value2 << endl;
  cout << cValue << endl;

  vector<int> ints = {1, 2, 3, 4, 5};
  ints.push_back(10);
  for (int i = 0; i < ints.size(); i++) {
    cout << i;
  }
  cout << endl;
  ints.pop_back();

  vector<int> numbers;
  randomNumbers(numbers);

  sort(numbers.begin(), numbers.end(), descCompare);
  for (int i = 0; i < numbers.size(); i++) {
    cout << numbers[i] << "-";
  }
  cout << endl;

  return EXIT_SUCCESS;
}
