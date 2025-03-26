#include "main.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
using namespace std;

const char *secret_phrase = "apple";

void draw(const int currentGuess) {
  cout << INITIAL_HANGMAN << endl;
  switch (currentGuess) {
  case 1:
    cout << LOSS1_HANGMAN << endl;
    break;
  case 2:
    cout << LOSS2_HANGMAN << endl;
    break;
  case 3:
    cout << LOSS3_HANGMAN << endl;
    break;
  case 4:
    cout << LOSS4_HANGMAN << endl;
    break;
  case 5:
    cout << LOSS5_HANGMAN << endl;
    break;
  case 6:
    cout << LOSS6_HANGMAN << endl;
    break;
  }
}

bool validateInput(const char guess) {
  for (size_t i = 0; i < strlen(secret_phrase); i++) {
    if (secret_phrase[i] == guess) {
      return true;
      break;
    }
  }

  return false;
}

int main(int argc, char *argv[]) {
  bool playAgain = true;
  char guess;
  int badCurrentGuess = 0;
  int goodCurrentGuess = 0;

  do {
    draw(badCurrentGuess);

    if (badCurrentGuess == MAX_GUESS_AMOUNT) {
      cout << "You lost, please try again" << endl;
      break;
    } else if (goodCurrentGuess == MAX_GUESS_AMOUNT) {
      cout << "You win!" << endl;
    }

    cout << "Enter character:" << endl;
    cin >> guess;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Input failed, try again" << endl;
      continue;
    }

    if (validateInput(guess)) {
      cout << "Guess is correct" << endl;
      goodCurrentGuess += 1;
    } else {
      cout << "Guess is incorrect" << endl;
      badCurrentGuess += 1;
    }

  } while (playAgain);

  return EXIT_SUCCESS;
}
