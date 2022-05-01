
#include "GameEngine.h"

GameEngine::GameEngine()
{
    std::vector<std::vector<Tile *>> board{BOARD_DIM_ROW, std::vector<Tile *>(BOARD_DIM_COL, nullptr)};
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
    std::string winnerName;

    for (Player *player : players)
    {
        /* Deals points penalty if needed */
        player->endPenalty();

        if (player->getPlayerScore() > topScore)
        {
            topScore = player->getPlayerScore();
            winnerName = player->getPlayerName();
        }
        else if (player->getPlayerScore() == topScore)
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

void GameEngine::printBoard()
{
    // std::cout << currentPlayer->getPlayerName() << ", it's your turn!" << std::endl;

    for (int i = 0; i < numPlayers; i++)
    {
        std::cout << "Score for " << players[i]->getPlayerName() << ": " << players[i]->getPlayerScore() << std::endl;
    }
    for (int i = 0; i < BOARD_DIM_ROW; i++)
    {
        if (i == 0)
        {
            std::cout << "    " << i;
        }
        else if (i >= 10)
        {
            std::cout << "  " << i;
        }
        else
        {
            std::cout << "   " << i;
        }
    }

    std::cout << std::endl;

    for (int i = 0; i <= BOARD_DIM_COL; i++)
    {
        if (i == BOARD_DIM_COL)
        {
            std::cout << "-----";
        }
        else if (i == 0)
        {
            std::cout << "  ";
        }
        else
        {
            std::cout << "----";
        }
    }
    std::cout << std::endl;
    for (int row = 0; row < BOARD_DIM_ROW; row++)
    {
        char c = row + 65;
        std::cout << c << " ";
        for (int col = 0; col < BOARD_DIM_COL; col++)
        {
            if (board[row][col] != nullptr)
            {
                std::cout << "| " << board[row][col]->getLetter() << " ";
            }
            else
            {

                std::cout << "|   ";
            }
        }

        std::cout << "|" << std::endl;
    }

    // currentPlayer->printHand();
}
