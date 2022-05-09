
#include "GameEngine.h"

GameEngine::GameEngine()
{
    std::vector<std::vector<Tile *>> board{BOARD_DIM_ROW, std::vector<Tile *>(BOARD_DIM_COL, nullptr)};
    tile_bag = new LinkedList();
    num_players = 0;
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

void GameEngine::Engine()
{

    bool end_check = false;
    /* loops while the tilebag and players have tiles, eof is not parsed in and the current player has not passed twice in a row. */
    while (!end_check && !std::cin.eof() && !exit)
    {
        draw_hands();
        for (Player *player : players)
        {
            current_player = player;
            /* Checks if the tilebag or playerhands are empty, ends game if both are 0 */
            if ((current_player->get_player_hand()->getSize() == 0 && tile_bag->getSize() == 0))
            {
                end_check = true;
            }
            else if (!end_check && !exit)
            {
                /* Prints the board for each player turn and gets user inputs */
                print_board();
                user_inputs();

                /* Checks if the player has passed twice in a row and ends game if needed */
                if (current_player->get_player_passes() > 1)
                {
                    end_check = true;
                }
            }
        }
    }

    /* Only prints the game over screen if the reason it gets here is end_check, otherwise don't print and leave */
    if (end_check)
    {
        get_winner();
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
    char letter = '\0';
    while (!file.eof() && numRead < TILE_BAG_SIZE)
    {
        if (file.good())
        {
            file >> letter;
            file >> value;
            if (letter != '\0')
            {
                Tile *tile = new Tile(letter, value);
                tile_bag->add_front(tile);
            }
        }
    }
    /* Shuffling linked list by grabing random node within the none randomised section of the list and moving it to the back */
    srand(time(NULL));
    for (int i = 0; i < tile_bag->getSize(); i++)
    {
        /* get a random index within the un randomised section of the list */
        int random_index = rand() % (TILE_BAG_SIZE - i + 1);

        Tile *selected = new Tile(*tile_bag->get_tile_at_index(random_index));
        tile_bag->remove_at_index(random_index);
        tile_bag->add_back(selected);
    }
}

void GameEngine::get_winner()
{
    std::cout << "Game Over" << std::endl;

    bool draw = false;
    int topScore = -1;
    std::string winnerName;

    /* for each player check the scores and find the player/players with the highest score and add them to the winners as needed */
    for (Player *player : players)
    {

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
        std::cout << "Score for " << player->get_player_name() << ": " << player->get_player_score() << std::endl;
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

void GameEngine::user_inputs()
{
    int tiles_placed = 0;
    bool invalid = false;
    bool turn_done = false;
    /* Loopos while the turn is not done or EOF is not parsed in */
    while (!turn_done && !exit)
    {
        /* Resets invalid check at every input so it only triggers invalid for its own iteration */
        invalid = false;
        /* Gets the player input */
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "")
        {
            std::getline(std::cin, input);
        }
        if (std::cin.eof())
        {
            std::cout << std::endl;
            exit = true;
        }

        /* Checks if the input is a valid command */
        if (input.substr(0, 5) == "place" && input.substr(8, 2) == "at" && input.length() >= 13)
        {
            /* Checks if the player owns the tile they want to place */
            if (current_player->get_player_hand()->contains(input.at(6)))
            {
                /* Checks if the location the place wants is valid */
                std::string loc = input.substr(11);
                if ((loc[0] >= 'A' && loc[0] <= 'O') && loc.length() <= 3)
                {
                    std::stringstream intTmp;
                    intTmp << loc.substr(1, 2);
                    /* Checks if the location is an number */
                    if (!intTmp.fail() && intTmp.eof())
                    {
                        int col;
                        intTmp >> col;
                        /* converting the char to int */
                        int row = int(loc[0] - 65);
                        /* If valid then place tile otherwise toggle invalid */
                        if (col >= 0 && col < BOARD_DIM_ROW)
                        {
                            if (board[row][col] == nullptr)
                            {
                                /* If tilePlace returns false a tile was placed */
                                if (!tilePlace(row, col, current_player->get_player_hand()->get_first_inst(input.at(6))))
                                {
                                    tiles_placed += 1;
                                }
                            }
                            else
                            {
                                invalid = true;
                            }
                            /* increase the tile placed count */
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
        /* Checks if the player input replace AND a letter */
        else if (input.substr(0, 7) == "replace" && input.length() == 9 && tiles_placed == 0)
        {
            Letter tile = input.at(8);
            if (tile >= 'A' && tile <= 'Z')
            {
                if (current_player->get_player_hand()->contains(tile))
                {
                    /* Makes a copy of the tile that will be replaced and replacing tile and add them to their correct hand/bag */
                    Tile *replaced = new Tile(*current_player->get_player_hand()->get_first_inst(tile));
                    tile_bag->add_back(replaced);
                    current_player->get_player_hand()->remove_first_inst(tile);
                    Tile *new_tile = new Tile(*tile_bag->get_tile_at_index(0));
                    current_player->draw_tile(new_tile);
                    tile_bag->remove_front();
                    turn_done = true;
                    current_player->reset_passes();
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
        /* Checks for pass and only allows pass when the player has not started placing tiles */
        else if (input.substr(0, 4) == "pass" && tiles_placed == 0)
        {
            /* Adds to pass counter and passes turn */
            current_player->add_pass();
            turn_done = true;
        }
        else if (input.substr(0, 10) == "place Done")
        {
            /* Triggers the turn to be done and resets pass counter*/
            current_player->reset_passes();
            turn_done = true;
        }
        /* Checks for save and only allows save when the player has not started placing tiles */
        else if (input.substr(0, 4) == "save" && input.length() >= 6 && tiles_placed == 0)
        {
            /* Saves the game then exits */

            save_Game(input.substr(5));
            exit = true;
        }
        else if (input.substr(0, 4) == "quit" || std::cin.eof())
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
    /* Checks if the player placed 7 tiles , if so add the Bingo points */
    if (tiles_placed == 7)
    {
        std::cout << std::endl
                  << "BINGO!!!" << std::endl;
        current_player->add_points(50);
    }
}

void GameEngine::print_board()
{
    /* Prints the current player's name and then prints all the players scores */
    std::cout << std::endl;
    std::cout << current_player->get_player_name() << ", it's your turn!" << std::endl;
    for (int i = 0; i < num_players; i++)
    {
        std::cout << "Score for " << players[i]->get_player_name() << ": " << players[i]->get_player_score() << std::endl;
    }

    /* Prints the numbers boxing the board by adding 4, 2 or 3 spaces accordingly */
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

    /* Prints the --s boxing the board as needed*/
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

    /* Prints the board, prints empty or filed as needed*/
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

    /* Prints the current players hand */
    current_player->print_hand();
}
void GameEngine::draw_hands()
{
    /* For each player draws untill their hand is full or if tile bag is empty as many as they can */
    for (Player *player : players)
    {
        for (int i = player->get_player_hand()->getSize(); i <= MAX_HAND_SIZE && tile_bag->getSize() > 0; i++)
        {
            Tile *tile = new Tile(*tile_bag->get_tile_at_index(0));
            tile_bag->remove_front();
            player->draw_tile(tile);
        }
    }
}

bool GameEngine::tilePlace(int row, int col, Tile *tile)
{
    Tile *placed = new Tile(*tile);
    bool invalid = false;
    if (isEmpty() == true && row == 7 && col == 7)
    {
        board[row][col] = placed;
    }
    else if (row == 0 && col == 0) // checks if tile is top-left
    {
        if (board[row + 1][col] != nullptr || board[row][col + 1] != nullptr)
        {
            board[row][col] = placed;
        }
        else
        {
            invalid = true;
        }
    }
    else if (row == 0 && col <= 14) // checks if tile is top row excl. top-left and top-right
    {
        if (board[row + 1][col] != nullptr || board[row][col + 1] != nullptr || board[row][col - 1] != nullptr)
        {
            board[row][col] = placed;
        }
        else
        {
            invalid = true;
        }
    }
    else if (row == 0 && col == 14) // checks if tile is top-right
    {
        if (board[row + 1][col] != nullptr || board[row][col - 1] != nullptr)
        {
            board[row][col] = placed;
        }
        else
        {
            invalid = true;
        }
    }
    else if (row == 14 && col == 0) // checks if tile is bottom-left
    {
        if (board[row - 1][col] != nullptr || board[row][col + 1] != nullptr)
        {
            board[row][col] = placed;
        }
        else
        {
            invalid = true;
        }
    }
    else if (row == 14 && col <= 14) // checks if tile is bottom row excl. top-left and top-right
    {
        if (board[row - 1][col] != nullptr || board[row][col + 1] != nullptr || board[row][col - 1] != nullptr)
        {
            board[row][col] = placed;
        }
        else
        {
            invalid = true;
        }
    }
    else if (row == 14 && col == 14) // checks if tile is bottom-right
    {
        if (board[row - 1][col] != nullptr || board[row][col - 1] != nullptr)
        {
            board[row][col] = placed;
        }
        else
        {
            invalid = true;
        }
    }
    else if (col == 0 && row <= 14) // checks if tile is on left edge
    {
        if (board[row + 1][col] != nullptr || board[row - 1][col] != nullptr || board[row][col + 1] != nullptr)
        {
            board[row][col] = placed;
        }
        else
        {
            invalid = true;
        }
    }
    else if (col == 14 && col <= 14) // checks if tile is on right edge
    {
        if (board[row + 1][col] != nullptr || board[row - 1][col] != nullptr || board[row][col - 1] != nullptr)
        {
            board[row][col] = placed;
        }
        else
        {
            invalid = true;
        }
    }
    else if (row <= 14 && col <= 14) // checks if tile is in the middle
    {
        if (board[row + 1][col] != nullptr || board[row - 1][col] != nullptr || board[row][col + 1] != nullptr || board[row][col - 1] != nullptr)
        {
            board[row][col] = placed;
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
    /* If invalid delete the tile that was meant to be placed otherwise add the points */
    if (invalid == true)
    {
        std::cout << "Invalid Tile Input" << std::endl;
        delete placed;
    }
    else
    {
        current_player->get_player_hand()->remove_first_inst(placed->getLetter());
        current_player->add_points(placed->getValue());
    }
    /* Reusing invalid as the return value, if invalid is false tile was placed */
    return invalid;
}

bool GameEngine::isEmpty()
{
    bool isempty = true;
    for (int i = 0; i < BOARD_DIM_ROW; i++)
    {
        for (int j = 0; j < BOARD_DIM_COL; j++)
        {
            if (board[i][j] != nullptr)
            {
                isempty = false;
                return isempty;
            }
        }
    }
    return isempty;
}
void GameEngine::save_Game(std::string filename)
{
    std::ofstream save_file;
    save_file.open(filename);

    // goes through all players and prints their details
    for (int i = 0; i < num_players; i++)
    {
        save_file << players[i]->get_player_name() << std::endl;
        save_file << players[i]->get_player_score() << std::endl;
        LinkedList *player_hand = players[i]->get_player_hand();
        for (int j = 0; j < player_hand->getSize() - 1; ++j)
        {
            Letter letter = player_hand->get_tile_at_index(j)->getLetter();
            Value value = player_hand->get_tile_at_index(j)->getValue();
            save_file << letter << "-" << value << ", ";
        }
        // last player is printed here so theres no comma at the end
        Letter letter = player_hand->get_tile_at_index(player_hand->getSize() - 1)->getLetter();
        Value value = player_hand->get_tile_at_index(player_hand->getSize() - 1)->getValue();
        save_file << letter << "-" << value << std::endl;
    }
    // used the code above to print board to the save file
    /* Prints the numbers boxing the board by adding 4, 2 or 3 spaces accordingly */
    for (int i = 0; i < BOARD_DIM_ROW; i++)
    {
        if (i == 0)
        {
            save_file << "    " << i;
        }
        else if (i >= 10)
        {
            save_file << "  " << i;
        }
        else
        {
            save_file << "   " << i;
        }
    }

    save_file << std::endl;

    /* Prints the --s boxing the board as needed*/
    for (int i = 0; i <= BOARD_DIM_COL; i++)
    {
        if (i == BOARD_DIM_COL)
        {
            save_file << "-----";
        }
        else if (i == 0)
        {
            save_file << "  ";
        }
        else
        {
            save_file << "----";
        }
    }
    save_file << std::endl;

    /* Prints the board, prints empty or filed as needed*/
    for (int row = 0; row < BOARD_DIM_ROW; row++)
    {
        char c = row + 65;
        save_file << c << " ";
        for (int col = 0; col < BOARD_DIM_COL; col++)
        {
            if (board[row][col] != nullptr)
            {
                save_file << "| " << board[row][col]->getLetter() << " ";
            }
            else
            {

                save_file << "|   ";
            }
        }

        save_file << "|" << std::endl;
    }
    // prints the bag
    for (int j = 0; j < tile_bag->getSize() - 1; ++j)
    {
        Letter letter = tile_bag->get_tile_at_index(j)->getLetter();
        Value value = tile_bag->get_tile_at_index(j)->getValue();
        save_file << letter << "-" << value << ", ";
    }
    // last tile printed here to remove comma
    Letter letter = tile_bag->get_tile_at_index(tile_bag->getSize() - 1)->getLetter();
    Value value = tile_bag->get_tile_at_index(tile_bag->getSize() - 1)->getValue();
    save_file << letter << "-" << value << std::endl;

    // prints current player
    save_file << current_player->get_player_name() << std::endl;
}
