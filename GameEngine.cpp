
#include "GameEngine.h"

GameEngine::GameEngine()
{
    numPlayers = 0;
}
GameEngine::~GameEngine()
{
    for (unsigned int i = 0; i < players.size(); i++)
    {
        delete players[i];
    }
}
