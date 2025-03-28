#include "main.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

void initializeShip(Ship &ship, int size, ShipType type,
                    ShipOrientation orientation) {
  ship.size = size;
  ship.type = type;
  ship.position.row = 0;
  ship.position.col = 0;
  ship.orientation = orientation;
}

void initializePlayer(Player *player, PlayerName name) {
  if (strlen(name) == 0) {
    cout << "player name is must be valid" << endl;
    return;
  }
  strcpy(player->name, name);
  initializeShip(player->ships[0], AIRCRAFT_CARRIER_SIZE, ST_AIRCRAFT_CARRIER);
  initializeShip(player->ships[1], BATTLESHIP_SIZE, ST_BATTLESHIP);
  initializeShip(player->ships[2], CRUISER_SIZE, ST_CRUISER);
  initializeShip(player->ships[3], DESTROYER_SIZE, ST_DESTROYER);
  initializeShip(player->ships[4], SUBMARINE_SIZE, ST_SUBMARINE);
}

void clearBoards(Player &player) {
  for (size_t r = 0; r < BOARD_SIZE; r++) {
    for (size_t c = 0; c < BOARD_SIZE; c++) {
      player.guessBoard[r][c] = GT_NONE;
      player.shipBoard[r][c].type = ST_NONE;
      player.shipBoard[r][c].isHit = false;
    }
  }
}

char getGuessRepresentation(const Player &player, int row, int col) {
  if (player.guessBoard[row][col] == GT_HIT) {
    return '*';
  }

  if (player.guessBoard[row][col] == GT_MISSED) {
    return 'o';
  }

  return ' ';
}

char getShipRepresentation(const Player &player, int row, int col) {
  if (player.shipBoard[row][col].isHit) {
    return '*';
  }

  switch (player.shipBoard[row][col].type) {
  case ST_AIRCRAFT_CARRIER:
    return 'A';
    break;
  case ST_DESTROYER:
    return 'D';
    break;
  case ST_CRUISER:
    return 'C';
    break;
  case ST_BATTLESHIP:
    return 'B';
    break;
  case ST_SUBMARINE:
    return 'S';
    break;
  default:
    return ' ';
  }
}

void drawColumnsRow() {
  cout << "  ";
  for (int i = 0; i < BOARD_SIZE; i++) {
    int columnName = i + 1;
    cout << " " << columnName << "  ";
  }
}

void drawShipBoardRow(const Player &player, int row) {
  char rowName = row + 'A';
  cout << rowName << "|";

  for (int c = 0; c < BOARD_SIZE; c++) {
    cout << " " << getShipRepresentation(player, row, c) << " |";
  }
}

void drawGuessBoardRow(const Player &player, int row) {
  char rowName = row + 'A';
  cout << rowName << '|';

  for (int c = 0; c < BOARD_SIZE; c++) {
    cout << " " << getGuessRepresentation(player, row, c) << " |";
  }
}

void drawSeparatorLine() {
  cout << " ";
  for (int i = 0; i < BOARD_SIZE; i++) {
    cout << "+---";
  }
  cout << "+";
}

void drawBoards(const Player &player) {
  drawColumnsRow();
  drawColumnsRow();

  cout << endl;

  for (int r = 0; r < BOARD_SIZE; r++) {
    drawSeparatorLine();
    cout << " ";
    drawSeparatorLine();
    cout << endl;
    drawShipBoardRow(player, r);
    cout << " ";
    drawGuessBoardRow(player, r);
    cout << endl;
  }

  drawSeparatorLine();
  cout << " ";
  drawSeparatorLine();
  cout << endl;
}

char *getShipNameForShipType(ShipType &type) {
  switch (type) {
  case ST_AIRCRAFT_CARRIER:
    return "Aircraft Carrier";
    break;
  case ST_DESTROYER:
    return "Destroyer";
    break;
  case ST_CRUISER:
    return "Cruiser";
    break;
  case ST_BATTLESHIP:
    return "Battleship";
    break;
  case ST_SUBMARINE:
    return "Submarine";
    break;
  default:
    return "None";
  }
}

template <typename T> void printArray(const T arr[], int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << (i == size - 1 ? "" : "-");
  }
  cout << endl;
}

ShipPosition mapBoardPosition(char rowInput, int colInput) {
  char realRow = rowInput - 'A';
  int realCol = colInput - 1;

  ShipPosition boardPosition;

  boardPosition.col = realCol;
  boardPosition.row = realRow;

  return boardPosition;
}

ShipPosition getBoardPosition() {
  char rowInput;
  int colInput;

  const char validRowInputs[10] = {'A', 'B', 'C', 'D', 'E',
                                   'F', 'G', 'H', 'I', 'J'};
  const int validColInputs[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  cout << "Enter valid row" << endl;
  printArray<char>(validRowInputs, 10);
  cin >> rowInput;

  cout << "Enter valid col" << endl;
  printArray<int>(validColInputs, 10);
  cin >> colInput;

  return mapBoardPosition(rowInput, colInput);
}

ShipOrientation getShipOrientation() {
  ShipOrientation shipOrientation;
  const char validInput[2] = {'H', 'V'};
  printArray(validInput, 2);
  char input;
  cin >> input;

  if (input == 'H') {
    shipOrientation = SO_HORIZONTAL;
  }

  if (input == 'V') {
    shipOrientation = SO_VERTICAL;
  }

  return shipOrientation;
}

bool isValidPlacement(const Player &player, const Ship &currentShip,
                      const ShipPosition &shipPosition,
                      const ShipOrientation &shipOrientation) {
  if (shipOrientation == SO_HORIZONTAL) {
    for (int c = 0; c < (shipPosition.col + currentShip.size); c++) {
      if (player.shipBoard[shipPosition.row][c].type != ST_NONE ||
          c >= BOARD_SIZE) {
        return false;
      }
    }
  } else {
    for (int r = shipPosition.row; r < (shipPosition.row + currentShip.size);
         r++) {
      if (player.shipBoard[r][shipPosition.col].type != ST_NONE ||
          r >= BOARD_SIZE) {
        return false;
      }
    }
  }

  return true;
}

void placeShipOnBoard(Player &player, Ship &currentShip,
                      const ShipPosition &shipPosition,
                      const ShipOrientation &shipOrientation) {
  currentShip.position = shipPosition;
  currentShip.orientation = shipOrientation;

  if (shipOrientation == SO_HORIZONTAL) {
    for (size_t c = shipPosition.col; c < (shipPosition.col + currentShip.size);
         c++) {
      player.shipBoard[shipPosition.row][c].type = currentShip.type;
      player.shipBoard[shipPosition.row][c].isHit = false;
    }
  } else {
    for (size_t r = shipPosition.row; r < (shipPosition.row + currentShip.size);
         r++) {
      player.shipBoard[r][shipPosition.col].type = currentShip.type;
      player.shipBoard[r][shipPosition.col].isHit = false;
    }
  }
}

void setupBoards(Player &player) {
  clearBoards(player);
  for (int i = 0; i < NUM_SHIPS; i++) {
    drawBoards(player);
    Ship &currentShip = player.ships[i];
    ShipPosition shipPosition;
    ShipOrientation shipOrientation;
    bool validPlacement = false;

    do {
      cout << player.name
           << " please set the position and orientation for your "
           << getShipNameForShipType(currentShip.type) << endl;
      shipPosition = getBoardPosition();
      shipOrientation = getShipOrientation();
      validPlacement =
          isValidPlacement(player, currentShip, shipPosition, shipOrientation);
      if (!validPlacement) {
        cout << "invalid placement" << endl;
      }

    } while (!validPlacement);
    placeShipOnBoard(player, currentShip, shipPosition, shipOrientation);
  }
  drawBoards(player);
}

void playGame(Player &player1, Player &player2) {
  setupBoards(player1);
  setupBoards(player2);
}

int main(int argc, char *argv[]) {
  Player player1;
  Player player2;

  initializePlayer(&player1, "jose");
  initializePlayer(&player2, "padilla");

  playGame(player1, player2);

  return EXIT_SUCCESS;
}
