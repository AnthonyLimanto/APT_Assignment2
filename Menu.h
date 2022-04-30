
#ifndef ASSIGN2_MENU_H
#define ASSIGN2_MENU_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//namespace
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define BOARD_DIM_ROW 15
#define BOARD_DIM_COL 15


class Menu
{
public:
    Menu();
    void print_grid(std::vector <std::vector<char> > grid);

    

private:
    std::vector <std::vector<char> > grid;
  
    string player1 , player2 ;
    string filename;
};

#endif // ASSIGN2_MENU_H
