#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <ios>
#include <iostream>
using namespace std;

const int UPPER_BOUND = 100;

int generateRandomNumber() {
  srand((unsigned int)time(NULL));
  return rand() % UPPER_BOUND;
}

int main(int argc, char *argv[]) {
  bool playGame = true;
  int secretNumber = generateRandomNumber();
  int numberTries = ceil(log2(UPPER_BOUND));
  int tries = 0;
  int guess = 0;

  do {
    if (tries == numberTries) {
      cout << "Number of tries reached" << endl;
      break;
    }

    cout << "Insert number:" << endl;
    cin >> guess;
    tries += 1;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input, try again" << endl;
      continue;
    }

    if (guess == secretNumber) {
      cout << "You guessed correctly" << endl;
      playGame = false;
    } else {
      cout << "Incorrect guess, try again" << endl;
      continue;
    }

  } while (playGame);

  cout << "Secret number " << secretNumber << endl;

  return EXIT_SUCCESS;
}
