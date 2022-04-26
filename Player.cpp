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
    hand = new LinkedList(*other.hand);
    this->name = other.name;
    this->score = other.score;
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
    hand->add_front(tile);
}

/* Prints the players hand.
 * Place holder method names for now.
 */
void Player::printHand()
{
    std::cout << "Your hand is " << std::endl;
    for (int i = 0; i < hand->getSize(); i++)
    {
        std::cout << hand->get_tile_at_index(i)->getLetter() << "-" << hand->get_tile_at_index(i)->getValue() << ", ";
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
    if (hand->getSize() > 0)
    {
        for (int i = 0; i < hand->getSize(); i++)
        {
            score -= hand->get_tile_at_index(i)->getValue();
        }
    }
}
