
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <iostream>
#include <vector>


using std::vector;

#define BOARD_DIM_ROW 15
#define BOARD_DIM_COL 15


class Board
{
public:
    void print_grid(std::vector <std::vector<char> > grid);

    

private:
    std::vector <std::vector<char> > grid;
  
};

#endif // ASSIGN2_BOARD_H
