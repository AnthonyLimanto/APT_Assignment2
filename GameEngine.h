
#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include <fstream>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Node.h"
#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
// #include "Menu.h"

#define BOARD_DIM_ROW 15
#define BOARD_DIM_COL 15
#define MAX_HAND_SIZE 7
#define TILE_BAG_SIZE 98

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void save_Game(std::string filename);
    void load_Game(std::string filename);

    void addPlayer(std::string name);
    void create_tile_bag();
    void draw_hands();

    /* Where the gameplay starts etc. */
    void Engine();

    void get_winner();
    void user_inputs();
    void print_board();
    void tilePlace(int row, int col, Tile *Tile);
    Player *current_player;

private:
    int num_players;
    bool exit;

    LinkedList *tile_bag;
    std::vector<Player *> players;
    std::vector<std::vector<Tile *>> board{BOARD_DIM_ROW, std::vector<Tile *>(BOARD_DIM_COL, nullptr)};
};

#endif // ASSIGN2_GAMEENGINE_H
