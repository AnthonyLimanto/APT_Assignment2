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
    this->pass_count = 0;
}
Player::Player(Player &other)
{
    hand = new LinkedList(*other.hand);
    this->name = other.name;
    this->score = other.score;
    this->pass_count = other.score;
}
Player::~Player()
{
    delete hand;
}

void Player::add_points(int points)
{
    this->score += points;
}

void Player::add_pass()
{
    this->pass_count += 1;
}

void Player::reset_passes()
{
    this->pass_count = 0;
}

/* Add a tile to the hand */
void Player::draw_tile(Tile *tile)
{
    hand->add_front(tile);
}

/* Prints the players hand.
 * Place holder method names for now.
 */
void Player::print_hand()
{

    std::cout << "Your hand is " << std::endl;
    if (hand->getSize() > 0)
    {
        for (int i = 0; i < hand->getSize(); i++)
        {
            std::cout << hand->get_tile_at_index(i)->getLetter() << "-" << hand->get_tile_at_index(i)->getValue() << ", ";
        }
    }
    std::cout << std::endl;
}

LinkedList *Player::get_player_hand()
{
    return hand;
}

std::string Player::get_player_name()
{
    return name;
}

int Player::get_player_passes()
{
    return pass_count;
}

int Player::get_player_score()
{
    return score;
}
