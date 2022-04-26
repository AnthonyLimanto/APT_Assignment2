
#include "GameEngine.h"

GameEngine::GameEngine()
{
    tilebag = new LinkedList();
    numPlayers = 0;
}
GameEngine::~GameEngine()
{
    delete tilebag;
    for (unsigned int i = 0; i < players.size(); i++)
    {
        delete players[i];
    }
}

void GameEngine::addPlayer(std::string name)
{
    players.push_back(new Player(name));
    numPlayers++;
}

void GameEngine::createTileBag()
{
    std::ifstream file("ScrabbleTiles.txt");
    int numRead = 0;
    int value = 0;
    char letter;
    while (!file.eof() && numRead < TILEBAG_SIZE)
    {
        if (file.good())
        {
            file >> letter;
            file >> value;
            Tile *tile = new Tile(letter, value);
            tilebag->add_front(tile);
        }
    }
    /* TODO: Add random order to tilebag */
}

void GameEngine::getWinner()
{
    std::cout << "Game Over" << std::endl;
    bool draw = false;
    int topScore = 0;
    int playerScore = 0;
    std::string winnerName;

    for (Player *player : players)
    {
        /* Deals points penalty if needed */
        player->endPenalty();

        playerScore = player->getPlayerScore();
        if (playerScore > topScore)
        {
            topScore = playerScore;
            winnerName = player->getPlayerName();
        }
        else if (playerScore == topScore)
        {
            draw = true;
            winnerName += ", " + player->getPlayerName();
        }
        std::cout << "Score for " << player->getPlayerName() << ": " << player->getPlayerScore();
    }
    if (draw)
    {
        std::cout << "Players " << winnerName << " draw!" << std::endl;
    }
    else
    {
        std::cout << "Player " << winnerName << " won!" << std::endl;
    }
}
