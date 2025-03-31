#include "main.hpp"

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  const char *msg = "Hello, ncurses! Press any key to exit.";
  mvprintw(rows / 2, (cols - strlen(msg)) / 2, "%s", msg);

  refresh();

  int ch = getch(); // wait for a keypress

  // Optional: Print what was pressed (debug)
  mvprintw(rows - 2, 0, "You pressed: %d. Exiting...", ch);
  refresh();
  getch(); // wait again so you can see the message

  endwin();
  return EXIT_SUCCESS;
}
