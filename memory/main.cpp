#include <cstdlib>
#include <iostream>
using namespace std;

void pass_by_value(int r) { cout << "val " << r << endl; }
void pass_by_ref(int &r) { cout << "val " << r << endl; }
void pass_by_ptr(int *r) {
  if (r == nullptr) {
    cout << "nullptr" << endl;
    return;
  }

  cout << "val " << *r << endl;
}
void swap(int &a, int &b) {
  int buffer = a;
  a = b;
  b = buffer;
}

int main(int argc, char *argv[]) {
  // reference | address of, use &
  int a = 10;
  cout << "ref " << &a << endl;

  // pointers | C style pointers
  int *pa = &a;
  cout << "pa value " << pa << endl;
  cout << "deref pa value " << *pa << endl;

  // reference variables
  int &ra = a;
  cout << "ra value " << ra << endl;

  // constans pointers
  // 1. Pointer to constant integer (value immutable):
  const int *b = nullptr; // or int const *a;
  // 2. Constant pointer to integer (pointer immutable):
  int *const c = nullptr;
  // 3. Constant pointer to constant integer (both immutable):
  const int *const d = nullptr;

  int e = 10;
  pass_by_value(e);
  pass_by_ref(e);
  pass_by_ptr(&e);
  pass_by_ptr(nullptr);

  int sa = 1;
  int sb = 2;
  swap(sa, sb);
  cout << "sa " << sa << endl;
  cout << "sb " << sb << endl;

  return EXIT_SUCCESS;
}
