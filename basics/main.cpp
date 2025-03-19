#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  int a = 0, b = 0, c = 0;
  string hello = "hello world";
  bool true_false = true;

  cout << hello << endl;

  cout << "add number:\n" << endl;
  cin >> a >> b >> c;

  cout << a << b << c << endl;

  if ((a > b) && (a > c)) {
    cout << "a is great if" << endl;
  }

  switch (a) {
  case 100:
    cout << "a is:" << a << endl;
    break;
  case 200:
    cout << "a is:" << a << endl;
  case 300: {
    string message = "a is:";
    cout << message << a << endl;
  } break;
  default:
    break;
  }

  string message = a > b ? "a is great tern" : "b is great tern";
  cout << message << endl;

  return EXIT_SUCCESS;
}
