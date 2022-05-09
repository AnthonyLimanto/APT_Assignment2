

#include <iostream>
#include "GameEngine.h"

void print_student_info();
void start_game();
bool upper_case_check(std::string name);
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
    if (choice == '1')
    {
      start_game();
      exit = true;
    }
    else if (choice == '2')
    {
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
      std::cout << "Invalid Input" << std::endl;
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
      std::cout << "Enter a name for player " << i + 1 << " (uppercase characters only)"
                << std::endl
                << " > ";
      std::cin >> player_name;
      std::cout << std::endl;

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
