#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct Book {
  char *name;
} Book;

void printBook(const Book &book) { cout << book.name << endl; }

int main(int argc, char *argv[]) {
  Book book;
  book.name = "qwe";
  printBook(book);

  Book *book2 = new Book;
  book2->name = "ewq";
  printBook(*book2);

  delete book2;
  return EXIT_SUCCESS;
}
