/*
 * Byron D Moran
 * bdm37@zips.uakron.edu
 * CS1ProjectFinal
 * 
 * This is a game of battleship. It is extremely similar to the game 
 * introduced to us all as children. More information about the game
 * can be found at http://en.wikipedia.org/wiki/Battleship_(game)
 * All moves are randomly generated except the user's move. Good luck!
 * 
*/

//Includes:
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

//Constants I'll be using:
#define SIZE  10
#define shipOne 5
#define shipTwo 4
#define shipThree 3
#define shipFour 3
#define shipFive 2

//Prototypes for each function:
void introMessage();
void clearScreen();
void playerPlaceShip(int, char[SIZE][SIZE], char);
void compPlaceShip(int, char[SIZE][SIZE], char);
void clearArray(char[SIZE][SIZE]);
void initializePlayerBoards(char[SIZE][SIZE]);
void initializeCompBoards(char[SIZE][SIZE]);
void printBoards(char[SIZE][SIZE]);
void move(char[SIZE][SIZE], char[SIZE][SIZE],char[SIZE][SIZE],char[SIZE][SIZE],int&, int&);
void getPlayerMove(int &, int &, char[SIZE][SIZE]);
void getCompMove(int &, int &, char[SIZE][SIZE]);
bool isValidMove(int, int, char[SIZE][SIZE]);
bool isValidEntry(int, int);
bool allShipsHit(int);
int charConvert(char);
void printRules();
void copyArray(char[SIZE][SIZE], char[SIZE][SIZE]);

//Main function:
int main(){
    srand(time(NULL));
    char playerBoardOne[SIZE][SIZE];
    char playerBoardTwo[SIZE][SIZE];
    char compBoardOne[SIZE][SIZE];
    char compBoardTwo[SIZE][SIZE];
    int playerShipsHit = 0;
    int compShipsHit = 0;
    introMessage();
    printRules();
    clearArray(playerBoardOne);
    clearArray(playerBoardTwo);
    clearArray(compBoardOne);
    clearArray(compBoardTwo);
    initializePlayerBoards(playerBoardOne);
    initializeCompBoards(compBoardOne);
    copyArray(playerBoardOne, compBoardTwo);
    //Check to make sure the game is not over (Either win or lose):
    while((allShipsHit(playerShipsHit) == false) && (allShipsHit(compShipsHit) == false))
    {   
        //If the game is not over, the boards are printed, and a move is made.
        cout << "   Opponent's Board" << endl;
        printBoards(playerBoardTwo);
        cout << "      Your Board" << endl;
        printBoards(compBoardTwo);
        cout << endl;
        move(playerBoardTwo, playerBoardOne, 
             compBoardTwo, compBoardOne,
             playerShipsHit, compShipsHit);
        clearScreen();
    } 
    if(allShipsHit(playerShipsHit)) //If player has won:
        cout << "Congratulations, YOU WON!!!" << endl;
    if(allShipsHit(compShipsHit)) //If computer has won:
        cout << "Sorry, The computer won this time." << endl;
   
}

//Intro to the game:
void introMessage(){
    cout << "Welcome to Byron Moran's game of battleship. It's very similar to"
            " the game of battleship we've all undoubtedly played as children. "
            "In this version your boards will be displayed, at each round and "
            "you will be able to continue playing until the game is over. Good "
            "Luck!\n\n";
}

//Clears the screen to stop text build up:
void clearScreen(){
    #if defined(__CYGWIN__)
    printf("\e[1;1H\e[2J");
    #elif defined(WINDOWS)
    system("cls");
    #else
    system("clear");
    #endif
}

//Clears the array, initializing it to all empty spaces:
void clearArray(char arr[SIZE][SIZE]){
    for(int i = 0; i < (SIZE); i++)
    {
        for(int j = 0; j < (SIZE); j++)
        {
            arr[i][j] = '-';
        }
    }
}

/*This function places the ships for the computer. Random x and y coordinates 
 *are created and checked against a direction variable, also created by a 
 *random number. The spaces are checked and the ships are then placed.*/
void compPlaceShip(int shipSize, char currentBoard[SIZE][SIZE],char shipType){
        int startingPositionx = 0;
        int startingPositiony = 0;
        bool isClear = true;
        do 
        { 
            do
            {
                startingPositionx = (rand() % 10);
                startingPositiony = (rand() % 10);
            }
            while (currentBoard[startingPositionx][startingPositiony] != '-');
            int directionChoice = ((rand()%4) +1);
            int i = startingPositionx;
            int j = startingPositiony;
            //If statement to handle the 4 possible directions:
            if(directionChoice == 1)
            {
                do
                {
                    if(currentBoard[i][startingPositiony] == '-')
                    {
                        isClear = true;
                        i++;
                    }
                    else
                        isClear = false;
                    if((j >= SIZE) || (j < 0) ||
                       (i >= SIZE) || (i < 0))
                        isClear = false;
                }
                while((isClear) && i <= (startingPositionx + (shipSize-1)));
               
                if(isClear)
                {
                    for(i = startingPositionx; 
                        i <= (startingPositionx + (shipSize-1)); i++)
                        currentBoard[i][startingPositiony] = shipType;
                }
            }
            else if(directionChoice == 2) 
            {
                do
                {
                    if(currentBoard[i][startingPositiony] == '-')
                    {
                        isClear = true;
                        i--;
                    }
                    else
                        isClear = false;                                       
                     if((j >= SIZE) || (j < 0) || (i >= SIZE) || (i < 0))
                     {
                         isClear = false;
                     }
                }
                while((isClear) && (i >= (startingPositionx -(shipSize-1))));
                if(isClear == true)
                {
                    for(i = startingPositionx;i >= (startingPositionx -(shipSize-1)); i--)
                    {
                        currentBoard[i][startingPositiony] = shipType;
                    }
                }
        
            }
            else if(directionChoice == 3) // up
            {                
                do
                {
                    if(currentBoard[startingPositionx][j] == '-')
                    {
                        isClear = true;
                        j++;
                    }
                    else
                        isClear = false;
                     if((j >= SIZE) || (j < 0) ||
                        (i >= SIZE) || (i < 0))
                         isClear = false;
                }
                while((isClear) && j <= (startingPositiony +(shipSize-1)));
                if(isClear)
                {
                    for(j = startingPositiony;
                        j <= (startingPositiony +(shipSize-1)); j++)
                        currentBoard[startingPositionx][j] = shipType;
                }
            }
            else if(directionChoice == 4)
            {
                do
                {
                    if(currentBoard[startingPositionx][j] == '-')
                    {
                        isClear = true;
                        j--;
                    }
                    else
                        isClear = false;
                    if((j >= SIZE) || (j < 0) ||
                       (i >= SIZE) || (i < 0))
                        isClear = false;
                }
                while((isClear) && j >= (startingPositiony -(shipSize-1)));
                if(isClear)
                {
                    for(j = startingPositiony;
                        j >= (startingPositiony -(shipSize-1)); j--)
                        currentBoard[startingPositionx][j] = shipType;
                }
            }
        }
        while (isClear == false);
}

/*This function is the same as above (compPlaceShip()) but was supposed to have
 *user input to generate the ship placement. I was not able to do that in time.*/
void playerPlaceShip(int shipSize, char currentBoard[SIZE][SIZE],char shipType){
        int startingPositionx = 0;
        int startingPositiony = 0;
        bool isClear = true;
        string tempInput;
        do 
        { 
            do
            {
//                cout << "Please input the x an y coordinates in which you would "
//                        "like to place your ship at as integers from 0-9.";
//                getline(cin, tempInput);
//                startingPositionx = tempInput[0];
//                startingPositiony = tempInput[1];
                startingPositionx = (rand() % 10);
                startingPositiony = (rand() % 10);
            }
            while (currentBoard[startingPositionx][startingPositiony] != '-');
            int directionChoice = ((rand()%4) +1);
            int i = startingPositionx;
            int j = startingPositiony;
           
            if(directionChoice == 1)
            {
                do
                {
                    if(currentBoard[i][startingPositiony] == '-')
                    {
                        isClear = true;
                        i++;
                    }
                    else
                        isClear = false;
                    if((j >= SIZE) || (j < 0) ||
                       (i >= SIZE) || (i < 0))
                        isClear = false;
                }
                while((isClear) && i <= (startingPositionx + (shipSize-1)));
               
                if(isClear)
                {
                    for(i = startingPositionx; 
                        i <= (startingPositionx + (shipSize-1)); i++)
                        currentBoard[i][startingPositiony] = shipType;
                }
            }
            else if(directionChoice == 2) 
            {
                do
                {
                    if(currentBoard[i][startingPositiony] == '-')
                    {
                        isClear = true;
                        i--;
                    }
                    else
                        isClear = false;                                       
                     if((j >= SIZE) || (j < 0) || (i >= SIZE) || (i < 0))
                     {
                         isClear = false;
                     }
                }
                while((isClear) && (i >= (startingPositionx -(shipSize-1))));
                if(isClear == true)
                {
                    for(i = startingPositionx;i >= (startingPositionx -(shipSize-1)); i--)
                    {
                        currentBoard[i][startingPositiony] = shipType;
                    }
                }
        
            }
            else if(directionChoice == 3) // up
            {                
                do
                {
                    if(currentBoard[startingPositionx][j] == '-')
                    {
                        isClear = true;
                        j++;
                    }
                    else
                        isClear = false;
                     if((j >= SIZE) || (j < 0) ||
                        (i >= SIZE) || (i < 0))
                         isClear = false;
                }
                while((isClear) && j <= (startingPositiony +(shipSize-1)));
                if(isClear)
                {
                    for(j = startingPositiony;
                        j <= (startingPositiony +(shipSize-1)); j++)
                        currentBoard[startingPositionx][j] = shipType;
                }
            }
            else if(directionChoice == 4)
            {
                do
                {
                    if(currentBoard[startingPositionx][j] == '-')
                    {
                        isClear = true;
                        j--;
                    }
                    else
                        isClear = false;
                    if((j >= SIZE) || (j < 0) ||
                       (i >= SIZE) || (i < 0))
                        isClear = false;
                }
                while((isClear) && j >= (startingPositiony -(shipSize-1)));
                if(isClear)
                {
                    for(j = startingPositiony;
                        j >= (startingPositiony -(shipSize-1)); j--)
                        currentBoard[startingPositionx][j] = shipType;
                }
            }
        }
        while (isClear == false);
}

//Initializes the player board with the ships on it:
void initializePlayerBoards(char board[SIZE][SIZE]){
    // Place Destroyer
    playerPlaceShip(shipFive, board, 'D');
    
    // Place Battleship
    playerPlaceShip(shipTwo, board, 'B');
    
    // Place Submarine
    playerPlaceShip(shipFour, board, 'S');
    
    // Place Cruiser
    playerPlaceShip(shipThree, board, 'C');
   
    // Place Aircraft carrier
    playerPlaceShip(shipOne, board, 'A');
}

//Initializes the comp board with the ships on it:
void initializeCompBoards(char board[SIZE][SIZE]){
    // Place Destroyer
    compPlaceShip(shipFive, board, 'D');
    
    // Place Battleship
    compPlaceShip(shipTwo, board, 'B');
    
    // Place Submarine
    compPlaceShip(shipFour, board, 'S');
    
    // Place Cruiser
    compPlaceShip(shipThree, board, 'C');
   
    // Place Aircraft carrier
    compPlaceShip(shipOne, board, 'A');
}

//Prints the boards out:
void printBoards(char board[SIZE][SIZE]){    
    cout <<  "   A  B  C  D  E  F  G  H  I  J" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << i << "  ";
        for (int j = 0; j < SIZE; j++)
            cout << board[i][j] << "  ";
        cout << endl;
    }
    cout << endl;
}

//Function for the player and computer to make a move:
void move(char playerHitBoard[SIZE][SIZE], char playerShipBoard[SIZE][SIZE],
          char computerHitBoard[SIZE][SIZE], char computerShipBoard[SIZE][SIZE],
          int &playerHitCount, int &computerHitCount){
    int column = 0;
    int row = 0;
    getPlayerMove(column, row, playerHitBoard); //Gets input and checks the move:
    if(computerShipBoard[row][column] == '-')
    {
        playerHitBoard[row][column] = 'M'; //Prints a miss
    }
    else
    {
        playerHitBoard[row][column] = computerShipBoard[row][column]; //Registers a hit
        playerHitCount += 1; //Raises the hit count for every hit registered
    }
        
    getCompMove(column, row, computerHitBoard);
    if(playerShipBoard[row][column] == '-')
        computerHitBoard[row][column] = 'M'; //Prints a miss
    else
    {
        computerHitBoard[row][column] = 'X'; //Registers a hit
        computerHitCount += 1; //Raises the hit count for every hit registered
    }
    clearScreen();
}

//Function to get a move from the user (called from move()):
void getPlayerMove(int &columnNum, int &row, char board[SIZE][SIZE]){
    char column;
    string input;
    bool isValid = false;
    do
    {
        cout << "Input Move(<A-J><0-9> A0-J9)\n>>>";
        getline(cin, input); //Get the input from user
        column = input[0]; //Column = first element of input string
        row = (input[1] - '0'); //Row = second element of input string
        columnNum = charConvert(column); //Convert char to int for array call
        isValid = ((input[1] >= '0') && (input [1] <= '9')); //Check if it's valid
        if(isValid == false || (input.length() > 2)) //If it's not valid, set values as such
        {
            columnNum = -999;
            row = -999;
        }
    }
    while((isValidMove(columnNum, row, board) == false));
}

//Gets the computers move from a random int and checks the validity of it
void getCompMove(int &column, int &row, char board[SIZE][SIZE]){
    do
    {
        column = (rand()%10);
        row = (rand() %10);
    }
    while(board[column][row] == 'X' || board[column][row] == 'M');
    
}

//Function to check the validity of each move. 
bool isValidMove(int column, int row, char board[SIZE][SIZE]){
    if((board[row][column] != '-') && (isValidEntry(column, row)))
    {
        cout << "Invalid Entry - Already been guessed.\n";
        return false;
    }
    if(isValidEntry(column, row) == false)
    {
        cout << "Invalid Entry. Please try Again.\n";
        return false;
    }
    else
        return true;
    
}

//Checks each move for validity by the bounds of the array:
bool isValidEntry(int column, int row){
    if((column < SIZE) && (column >= 0)
       && (row < SIZE) && (row >= 0))
        return true;
    else
        return false;
}

//Checks the hit count of a certain player (comp or user):
bool allShipsHit(int hitCount){
    if (hitCount == (shipOne + shipTwo + shipThree + shipFour + shipFive))
        return true;
    else
        return false;
}

//Converts the user input of a char for each column to an integer:
int charConvert(char column){       
    if(column == 'A' || column == 'a')
        return 0;
    else if(column == 'B' || column == 'b')
        return 1;
    else if(column == 'C' || column == 'c')
        return 2;
    else if(column == 'D' || column == 'd')
        return 3;
    else if(column == 'E' || column == 'e')
        return 4;
    else if(column == 'F' || column == 'f')
        return 5;
    else if(column == 'G' || column == 'g')
        return 6;
    else if(column == 'H' || column == 'h')
        return 7;
    else if(column == 'I' || column == 'i')
        return 8;
    else if(column == 'J' || column == 'j')
        return 9;
    else 
        return -1; 
}


void printRules(){    
    cout << "Ships: \n";
    cout << "A- Aircraft Carrier (5 spaces)\n";
    cout << "B- Battleship (4 spaces)\n";
    cout << "C- Cruiser (3 spaces)\n";
    cout << "D- Destroyer (2 spaces)\n";
    cout << "S- Submarine (3 spaces)\n\n";
    cout << "Key: \n";
    cout << "Ship Type - Player hit\n";
    cout << "X - Computer hit\n";
    cout << "M - Miss\n\n";
}

//Function to copy the arrays:
void copyArray(char fromArray[SIZE][SIZE],char toArray[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
            toArray[i][j] = fromArray[i][j];
    }
}
