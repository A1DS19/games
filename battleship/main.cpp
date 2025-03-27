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

void setupBoards(Player &player) {
  clearBoards(player);
  drawBoards(player);
}

void playGame(Player &player1, Player &player2) {
  setupBoards(player1);
  setupBoards(player2);
}

int main(int argc, char *argv[]) {
  Player player1;
  Player player2;

  playGame(player1, player2);

  return EXIT_SUCCESS;
}
