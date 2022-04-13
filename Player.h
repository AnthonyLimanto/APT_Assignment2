#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

#include "LinkedList.h"
#include "Node.h"

class Player
{
public:
    Player(std::string name);
    ~Player();
    /* Helper Methods */
    void addPoints(int points);
    void drawTile(Tile *tile);
    void printHand();
    void endPenalty();

    /* Getters */
    LinkedList getPlayerHand();
    std::string getPlayerName();
    int getPlayerScore();

private:
    std::string name;
    int score;
    LinkedList *hand;
};

#endif