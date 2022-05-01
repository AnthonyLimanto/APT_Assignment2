
#include "Board.h"


//grid
void Board::print_grid(vector <vector<char> > grid)
{
   
            
        for(int i = 0; i < BOARD_DIM_ROW; i++)
        {
            vector<char> temp1;
            for(int j = 0; j < BOARD_DIM_COL; j++)
            { 
                temp1.push_back('|');
                
            }
            grid.push_back(temp1);
        }
        for(int j = 0; j < BOARD_DIM_COL; j++) {
            if(j%4==1 || j%4==3){
                grid[0][j]=' ';
            }
            else{
            grid[0][0]=' ';grid[0][2]='0';grid[0][4]='1';grid[0][6]='2';grid[0][8]='3';grid[0][10]='4';grid[0][12]='5';grid[0][14]=' ';
            grid[2][0]='A';grid[2][2]=' ';grid[2][4]=' ';grid[2][6]=' ';grid[2][8]=' ';grid[2][10]=' ';grid[2][12]=' ';grid[2][14]=' ';
            grid[3][0]='B';grid[3][2]=' ';grid[3][4]=' ';grid[3][6]=' ';grid[3][8]=' ';grid[3][10]=' ';grid[3][12]=' ';grid[3][14]=' ';
            grid[4][0]='C';grid[4][2]=' ';grid[4][4]=' ';grid[4][6]=' ';grid[4][8]=' ';grid[4][10]=' ';grid[4][12]=' ';grid[4][14]=' ';
            grid[5][0]='D';grid[5][2]=' ';grid[5][4]=' ';grid[5][6]=' ';grid[5][8]=' ';grid[5][10]=' ';grid[5][12]=' ';grid[5][14]=' ';
            grid[6][0]='E';grid[6][2]=' ';grid[6][4]=' ';grid[6][6]=' ';grid[6][8]=' ';grid[6][10]=' ';grid[6][12]=' ';grid[6][14]=' ';
            grid[7][0]='F';grid[7][2]=' ';grid[7][4]=' ';grid[7][6]=' ';grid[7][8]=' ';grid[7][10]=' ';grid[7][12]=' ';grid[7][14]=' ';
            grid[8][0]='G';grid[8][2]=' ';grid[8][4]=' ';grid[8][6]=' ';grid[8][8]=' ';grid[8][10]=' ';grid[8][12]=' ';grid[8][14]=' ';
            grid[9][0]='H';grid[9][2]=' ';grid[9][4]=' ';grid[9][6]=' ';grid[9][8]=' ';grid[9][10]=' ';grid[9][12]=' ';grid[9][14]=' ';
            grid[10][0]='I';grid[10][2]=' ';grid[10][4]=' ';grid[10][6]=' ';grid[10][8]=' ';grid[10][10]=' ';grid[10][12]=' ';grid[10][14]=' ';
            grid[11][0]='J';grid[11][2]=' ';grid[11][4]=' ';grid[11][6]=' ';grid[11][8]=' ';grid[11][10]=' ';grid[11][12]=' ';grid[11][14]=' ';
            grid[12][0]='K';grid[12][2]=' ';grid[12][4]=' ';grid[12][6]=' ';grid[12][8]=' ';grid[12][10]=' ';grid[12][12]=' ';grid[12][14]=' ';
            grid[13][0]='L';grid[13][2]=' ';grid[13][4]=' ';grid[13][6]=' ';grid[13][8]=' ';grid[13][10]=' ';grid[13][12]=' ';grid[13][14]=' ';
            grid[14][0]='M';grid[14][2]=' ';grid[14][4]=' ';grid[14][6]=' ';grid[14][8]=' ';grid[14][10]=' ';grid[14][12]=' ';grid[14][14]=' ';
            }
        }
        for(int j = 0; j < BOARD_DIM_COL; j++) {
                grid[1][j]='-';
        }
        for(int i = 0; i < BOARD_DIM_ROW; i++) {
                    for(int j = 0; j < BOARD_DIM_COL; j++) {
                        std::cout << grid[i][j] << " ";
                    }
                    std::cout << std::endl;
                }      
 }   



