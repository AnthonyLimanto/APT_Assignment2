#include <string>
#include <iostream>

#include "LinkedList.h"
#include "Player.h"
#include "Node.h"

Player::Player(std::string name)
{
    hand = new LinkedList();
    this->name = name;
    this->score = 0;
}
Player::Player(Player &other)
{
    hand = new LinkedList(other.getPlayerHand());
    this->name = other.getPlayerName();
    this->score = other.getPlayerScore();
}
Player::~Player()
{
    delete hand;
}

void Player::addPoints(int points)
{
    this->score += points;
}

/* Add a tile to the hand */
void Player::drawTile(Tile *tile)
{
    hand->addBack(tile);
}

/* Prints the players hand.
 * Place holder method names for now.
 */
void Player::printHand()
{
    std::cout << "Your hand is " << std::endl;
    for (int i = 0; i < hand->size(); i++)
    {
        std::cout << hand->get(i)->getLetter() << "-" << hand->get(i)->getNum() << ", ";
    }
    std::cout << std::endl;
}

LinkedList Player::getPlayerHand()
{
    return *hand;
}

std::string Player::getPlayerName()
{
    return name;
}

int Player::getPlayerScore()
{
    return score;
}

/* Method to apply end penalty if the player has cards left in thier hand.
 * Place holder method names for now.
 */
void Player::endPenalty()
{
    if (hand->size() > 0)
    {
        for (int i = 0; i < hand->size(); i++)
        {
            score -= hand->get(i)->getNum();
        }
    }
}
