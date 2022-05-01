
#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include <fstream>
#include <random>
#include <iostream>
#include <string>
#include <vector>

#include "Node.h"
#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
// #include "Menu.h"

#define BOARD_DIM_ROW 15
#define BOARD_DIM_COL 15
#define MAX_HAND_SIZE 7
#define TILEBAG_SIZE 98

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void saveGame(std::string filename);
    void loadGame(std::string filename);

    void addPlayer(std::string name);
    void createTileBag();
    void drawTile();

    /* Where the gameplay starts etc. */
    void Engine();

    void getWinner();
    void userInputs(std::string input);
    void printBoard();

private:
    int numPlayers;
    Player *currentPlayer;
    LinkedList *tilebag;
    std::vector<Player *> players;
    std::vector<std::vector<Tile *>> board{BOARD_DIM_ROW, std::vector<Tile *>(BOARD_DIM_COL, nullptr)};
};

#endif // ASSIGN2_GAMEENGINE_H
