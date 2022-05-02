
#include "GameEngine.h"
#include <sstream>
GameEngine::GameEngine()
{
    std::vector<std::vector<Tile *>> board{BOARD_DIM_ROW, std::vector<Tile *>(BOARD_DIM_COL, nullptr)};
    tile_bag = new LinkedList();
    num_players = 0;
    turn_done = false;
    exit = false;
}
GameEngine::~GameEngine()
{
    delete tile_bag;

    for (unsigned int i = 0; i < players.size(); i++)
    {
        delete players[i];
    }
    for (int row = 0; row < BOARD_DIM_ROW; row++)
    {
        for (int col = 0; col < BOARD_DIM_COL; col++)
        {
            delete board[row][col];
            board[row][col] = nullptr;
        }
    }
}

void GameEngine::addPlayer(std::string name)
{
    players.push_back(new Player(name));
    num_players++;
}

void GameEngine::create_tile_bag()
{
    std::ifstream file("ScrabbleTiles.txt");
    int numRead = 0;
    int value = 0;
    char letter;
    while (!file.eof() && numRead < TILE_BAG_SIZE)
    {
        if (file.good())
        {
            file >> letter;
            file >> value;
            Tile *tile = new Tile(letter, value);
            tile_bag->add_front(tile);
        }
    }
    /* TODO: Add random order to tile_bag */
}

void GameEngine::get_winner()
{
    std::cout << "Game Over" << std::endl;
    bool draw = false;
    int topScore = 0;
    std::string winnerName;

    for (Player *player : players)
    {
        /* Deals points penalty if needed */
        player->end_penalty();

        if (player->get_player_score() > topScore)
        {
            topScore = player->get_player_score();
            winnerName = player->get_player_name();
        }
        else if (player->get_player_score() == topScore)
        {
            draw = true;
            winnerName += ", " + player->get_player_name();
        }
        std::cout << "Score for " << player->get_player_name() << ": " << player->get_player_score();
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

void GameEngine::user_inputs(std::string input)
{
    /* Check for EOF if not check if valid, Best way to check is substrings */
    bool invalid = false;
    /* Checks if the input is a valid command */
    if (input.substr(0, 5) == "place" && input.substr(8, 2) == "at" && input.length() == 13)
    {
        /* Checks if the player owns the tile they want to place */
        // if (currentPlayer->getPlayerHand().contains(input.at(6)))
        // {
        /* Checks if the location the place wants is valid */
        std::string loc = input.substr(11, 3);
        if ((loc[0] >= 'A' && loc[0] <= 'Z'))
        {

            int locInt;
            std::stringstream intTmp;
            intTmp << loc.substr(1, 2);
            intTmp >> locInt;
            /* If valid then place tile otherwise toggle invalid */
            if (locInt >= 0 || locInt <= 15)
            {
                // tilePlace();
            }
            else
            {
                invalid = true;
            }
        }
        else
        {
            invalid = true;
        }
        // }else{
        //     invalid = true;
        // }
    }
    else if (input.substr(0, 7) == "replace" && input.length() == 9)
    {
        Letter tile = input.at(8);
        std::cout << tile << std::endl;
        if (tile >= 'A' && tile <= 'Z')
        {
            if (current_player->get_player_hand()->contains(input.at(8)))
            {
                Tile *replaced = new Tile(*current_player->get_player_hand()->get_first_inst(tile));
                tile_bag->add_back(replaced);
                current_player->get_player_hand()->remove_first_inst(tile);
                Tile *new_tile = new Tile(*tile_bag->get_tile_at_index(0));
                current_player->get_player_hand()->add_back(new_tile);
                tile_bag->remove_front();
            }
            else
            {
                invalid = true;
            }
        }
        else
        {
            invalid = true;
        }
    }
    else if (input.substr(0, 4) == "done")
    {
        /* Triggers the turn to be done */
        turn_done = true;
    }
    else if (input.substr(0, 4) == "save")
    {
        /* Saves the game then exits */
        exit = true;
    }
    else if (input.substr(0, 4) == "quit")
    {
        /* Triggers the exit for the whole game */
        exit = true;
    }
    else
    {
        invalid = true;
    }

    /* Checks if a invalid command was placed */
    if (invalid)
    {
        std::cout << "Invalid Input" << std::endl;
    }
}

void GameEngine::print_board()
{

    std::cout << std::endl;
    std::cout << current_player->get_player_name() << ", it's your turn!" << std::endl;
    for (int i = 0; i < num_players; i++)
    {
        std::cout << "Score for " << players[i]->get_player_name() << ": " << players[i]->get_player_score() << std::endl;
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

    current_player->print_hand();
}
void GameEngine::draw_hands()
{
    /* For each player draws untill their hand is full or if tile bag is empty as many as they can */
    for (Player *player : players)
    {
        for (int i = player->get_player_hand()->getSize(); i < MAX_HAND_SIZE && tile_bag->getSize() > 0; i++)
        {
            Tile *tile = new Tile(*tile_bag->get_tile_at_index(0));
            tile_bag->remove_front();
            player->draw_tile(tile);
        }
    }
}