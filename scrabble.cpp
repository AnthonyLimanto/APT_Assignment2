

#include <iostream>

#include "GameEngine.h"

void print_student_info();
void start_game();
void load_game(std::string filename);
bool upper_case_check(std::string name);
int letter_to_row(char c);
GameEngine *game_engine;
int main(void)
{
  game_engine = new GameEngine();
  std::cout << "Menu" << std::endl
            << "----" << std::endl
            << "1. New Game" << std::endl
            << "2. Load Game" << std::endl
            << "3. Credits (Show Student Information)" << std::endl
            << "4. Quit" << std::endl;

  bool exit = false;
  char choice = 0;

  while (!std::cin.eof() && !exit)
  {
    std::cout << std::endl
              << "> ";
    std::cin >> choice;
    std::cout << std::endl;
    if (choice == '1')
    {
      start_game();
      exit = true;
    }
    else if (choice == '2')
    {
      std::cout << "Enter the filename from which to load a game" << std::endl;
      std::string filename;
      std::cin >> filename;
      load_game(filename);

      exit = true;
    }
    else if (choice == '3')
    {
      print_student_info();
    }
    else if (choice == '4' || std::cin.eof())
    {
      exit = true;
    }
    else
    {
      std::cout << "Invalid Input";
    }
  }

  std::cout << std::endl;
  std::cout << "Goodbye!" << std::endl;
  delete game_engine;
  return EXIT_SUCCESS;
}

void print_student_info()
{
  std::cout << "----------------------------------" << std::endl
            << "Name: Anthony Limanto" << std::endl
            << "Student ID: s3898395" << std::endl
            << "Email: s3898395@student.rmit.edu.au" << std::endl
            << std::endl
            << "Name: Pawat Kusonchukul" << std::endl
            << "Student ID: s3779279" << std::endl
            << "Email: s3779279@student.rmit.edu.au" << std::endl
            << std::endl
            << "Name: Richard Quach" << std::endl
            << "Student ID: s3784866" << std::endl
            << "Email: s3784866@student.rmit.edu.au" << std::endl
            << std::endl
            << "Name: Cesar Jude Quitazol" << std::endl
            << "Student ID: s3844561" << std::endl
            << "Email: s3844561@student.rmit.edu.au" << std::endl
            << "----------------------------------" << std::endl;
}

void start_game()
{
  bool exit = false;
  std::string player_name;
  int player_count = 2;
  bool is_upper = false;
  std::cout << "Starting a New Game" << std::endl;

  for (int i = 0; i < player_count && !std::cin.eof(); i++)
  {
    is_upper = false;
    while (!is_upper)
    {
      std::cout << "Enter a name for player " << i << " (uppercase characters only)"
                << std::endl
                << " > ";
      std::cin >> player_name;
      is_upper = upper_case_check(player_name);

      if (!is_upper)
      {
        std::cout << "Invalid Input" << std::endl;
      }
      if (std::cin.eof())
      {
        exit = true;
      }
    }
    game_engine->addPlayer(player_name);
  }
  if (!exit)
  {
    std::cout << "Let's Play!" << std::endl;

    game_engine->create_tile_bag();
    game_engine->Engine();
  }
}

bool upper_case_check(std::string name)
{
  bool ret = true;
  for (char c : name)
  {
    if (!isupper(c))
    {
      ret = false;
    }
  }
  return ret;
}

int letter_to_row(char c) {
  int num;
  if (c == 'A') {
    num = 0;
  }
  if (c == 'B') {
    num = 1;
  }
  if (c == 'C') {
    num = 2;
  }
  if (c == 'D') {
    num = 3;
  }
  if (c == 'E') {
    num = 4;
  }
  if (c == 'F') {
    num = 5;
  }
  if (c == 'G') {
    num = 6;
  }
  if (c == 'H') {
    num = 7;
  }
  if (c == 'I') {
    num = 8;
  }
  if (c == 'J') {
    num = 9;
  }
  if (c == 'K') {
    num = 10;
  }
  if (c == 'L') {
    num = 11;
  }
  if (c == 'M') {
    num = 12;
  }
  if (c == 'N') {
    num = 13;
  }
  if (c == 'O') {
    num = 14;
  }
  return num;
}


void load_game(std::string filename) {
  std::ifstream save_file_reader;
    

    save_file_reader.open(filename);

    if (!save_file_reader) {
        std::cout << "File does not exist";
    }
    else {

      // reads file and fills vector
        std::vector<std::string> file;
        std::string line;
        while (getline(save_file_reader, line)) {
            file.push_back(line);
        }

        if (upper_case_check(file[0])) {

            LinkedList* hand = new LinkedList();
            
            std::string tile_string;
            std::istringstream ss(file[2]);


            // hand
            while (ss >> tile_string) {
              Letter letter = tile_string[0];
              Value value = tile_string[2] - '0';
              Tile* tile = new Tile(letter, value);
              hand->add_back(tile);
            }
            // new player with name, score and hand
            Player* player1 = new Player(file[0], std::stoi(file[1]), hand);
            game_engine->addPlayer(player1);
        }

        if (upper_case_check(file[3])) {

            LinkedList* hand = new LinkedList();
            
            
            std::string tile_string;
            std::istringstream ss(file[5]);


            // hand
            while (ss >> tile_string) {
              Letter letter = tile_string[0];
              Value value = tile_string[2] - '0';
              Tile* tile = new Tile(letter, value);
              hand->add_back(tile);
            }

            Player* player2 = new Player(file[3], std::stoi(file[4]), hand);
            game_engine->addPlayer(player2);
        }

        std::string tile_at_pos_string;
        std::istringstream ss(file[6]);


        // loading board IS FIXED but super messy ill clean up later
        while (ss >> tile_at_pos_string) {
          
          if (isupper(tile_at_pos_string[0])) {
             
            if (isupper(tile_at_pos_string[2])) {
              
              // if(isdigit(tile_at_pos_string[3] - '0')) {
                // std::cout << "here4" << tile_at_pos_string[3] << std::endl;
                Letter letter = tile_at_pos_string[0];
                // Value value = tile_at_pos_string[2] - '0';
                Tile* tile = new Tile(letter);
                
                int row = letter_to_row(tile_at_pos_string[2]);
                int col = tile_at_pos_string[3] - '0';
                
                game_engine->tilePlace(row, col ,tile);
              // }
            }
          }
        }

        LinkedList* bag = new LinkedList();

        std::string bag_tiles;
        std::istringstream strings(file[7]);

        while (strings >> bag_tiles) {
            Letter letter = bag_tiles[0];
            Value value = bag_tiles[2] - '0';

            Tile* tile = new Tile(letter, value);
            // std::cout << tile->getLetter() << tile->getValue() << std::endl;
            bag->add_back(tile);
        }

        game_engine->set_tile_bag(bag);


        // curr player
        
        


        game_engine->set_curr_player(file[8]);

        std::cout << "Scrabble game successfully loaded" << std::endl;
        game_engine->Engine();
        



    }



}