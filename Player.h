#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

#include "LinkedList.h"
#include "Node.h"

class Player
{
public:
    Player(std::string name);
    Player(Player &other);
    ~Player();
    /* Helper Methods */
    void add_points(int points);
    void add_pass();
    void draw_tile(Tile *tile);
    void print_hand();
    void reset_passes();

    /* Getters */
    LinkedList *get_player_hand();
    std::string get_player_name();
    int get_player_score();
    int get_player_passes();

private:
    std::string name;
    int score;
    int pass_count;
    LinkedList *hand;
};

#endif