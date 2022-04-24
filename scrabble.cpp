
// #include "LinkedList.h"

#include <iostream>
#define EXIT_SUCCESS    0

//namespace
using std::cin;
using std::cout;
using std::endl;
using std::string;

//variable 
string player1 , player2 ;
string filename;


#define EXIT_SUCCESS    0

int main(void) {
   // LinkedList* list = new LinkedList();
   // delete list;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;
   int  choice;
   cout << "Welcome to Scrabble! \n" ;
   cout << "-------------------- \n" ;
   cout << "Menu \n" ;
   cout << "---- \n" ;
   cout << "1. New Game \n" ;
   cout << "2. Load Game \n" ;
   cout << "3. Credits (Show student information) \n" ;
   cout << "4. Quit \n" ;
   cout << "\n" ;
   cout << "Please choose your MENU choice : " ;
   cin >> choice ;
   if(choice==1) {
      cout << "Starting a New Game!!! \n" ; 
      cout << "\n" ;
      cout << "Enter a name for player 1(uppercase characters only) \n";
      cin >> player1 ;
      cout << "\n" ;
      cout << "Enter a name for player 2(uppercase characters only) \n";
      cin >> player2 ;
      cout << "\n" ;
      cout << "\n";
      cout << "Lets Play!!! \n";
        
    }
         
    else if(choice==2){    
      cout << "Load game!!!" << endl;
      cout << "\n" ;
      cout << "Enter the filename from which load a game : \n";
      //cin >> #filename ;
      cout << "\n" ;
      cin >> filename ;
      cout << "Scrabble game successfully loaded!!!! \n";
      //cin >> #game play continue from here ;
    }  
    else if(choice==3){
      cout << "Credits(Show student information)" << endl;
      cout << "---------------------------------\n" ;
      cout << "Name : " << "Anthony Limanto\n" ;
      cout << "Student ID : " << "s3898395\n" ;
      cout << "Email : "<< "s3898395@student.rmit.edu.au\n" ;
      cout << "\n" ;
      cout << "Name : " << "Pawat Kusonchukul\n" ;
      cout << "Student ID : " << "s3779279\n" ;
      cout << "Email : "<< "s3779279@student.rmit.edu.au\n" ;
      cout << "\n" ;

      cout << "Name : " << "Richard Quach\n" ;
      cout << "Student ID : " << "s3784866\n" ;
      cout << "Email : "<< "s3784866@student.rmit.edu.au\n" ;
      cout << "\n" ;
      cout << "Name : " << "Cesar Jude Quitazol\n" ;
      cout << "Student ID : " << "s3844561\n" ;
      cout << "Email : "<< "s3844561@student.rmit.edu.au\n" ;

    }
    else if(choice==4){
      cout << "Quit!!!" << endl;
    }
    else{  
      cout << "Your choice is " << choice ;
      cout << " is Invalid choice" << endl;
    }  


   return EXIT_SUCCESS;
}
