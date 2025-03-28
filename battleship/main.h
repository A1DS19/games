#ifndef MAIN_H 

#define MAIN_H

enum {
  AIRCRAFT_CARRIER_SIZE = 5,
  BATTLESHIP_SIZE = 4,
  DESTROYER_SIZE = 3,
  CRUISER_SIZE = 3,
  SUBMARINE_SIZE = 2,
  BOARD_SIZE = 10,
  NUM_SHIPS = 5,
  PLAYER_NAME_SIZE = 8,
  MAX_SHIP_SIZE = AIRCRAFT_CARRIER_SIZE
};

enum ShipType {
  ST_AIRCRAFT_CARRIER = 1,
  ST_BATTLESHIP = 2,
  ST_CRUISER = 3,
  ST_DESTROYER = 4,
  ST_SUBMARINE = 5,
  ST_NONE = 0
};

enum ShipOrientation {
  SO_VERTICAL,
  SO_HORIZONTAL = 0
};

struct ShipPosition {
  int row;
  int col;
};

struct Ship {
  ShipType type;
  int size;
  ShipOrientation orientation;
  ShipPosition position;
};

enum GuessType {
  GT_NONE = 0,
  GT_MISSED,
  GT_HIT
};

struct ShipPartType {
  ShipType type;
  bool isHit;
};

typedef char PlayerName[PLAYER_NAME_SIZE];
struct Player {
  PlayerName name;
  Ship ships[NUM_SHIPS];
  GuessType guessBoard[BOARD_SIZE][BOARD_SIZE];
  ShipPartType shipBoard[BOARD_SIZE][BOARD_SIZE];
};

void initializeShip(Ship &ship, int size, ShipType type,
                    ShipOrientation orientation = SO_HORIZONTAL);
void initializePlayer(Player *player, PlayerName name);
void playGame(Player &player1, Player &player2);
void clearBoards(Player &player);
void drawBoards(const Player &player);
void setupBoards(Player &player);
void drawColumnsRow();
void drawSeparatorLine();
void drawShipBoardRow(const Player &player, int row);
void drawGuessBoardRow(const Player &player, int row);
char getShipRepresentation(const Player &player, int row, int col);
char getGuessRepresentation(const Player &player, int row, int col);
char *getShipNameForShipType(ShipType &type);
ShipPosition getBoardPosition();
template <typename T>
void printArray(const T arr[], int size);
ShipPosition mapBoardPosition(char rowInput, int colInput);
ShipOrientation getShipOrientation();
bool isValidPlacement(const Player &player, const Ship &currentShip, const ShipPosition &shipPosition, const ShipOrientation &shipOrientation);
void placeShipOnBoard(Player &player, Ship &currentShip, const ShipPosition &shipPosition, const ShipOrientation &shipOrientation);
void clearScreen();

#endif
