/**************************************************************
/ AUTHOR: Ryan Levitt
/ PURPOSE: Capstone Project for CSC-160
/ DESCRIPTION: This is a mini version of the board battleship,
/              in which a user plays against the computer
/              trying to guess the placement of the computers
/              battleship before their ship get sunk!
/ DATE: Summer 2021

s*************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std; 

void displayBoard(char board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{

    // 4. VARIABLES
    char a;
    bool userTurn = true;
    int rowGuess;
    int colGuess;
    char result;
    int userHitCount = 0;
    int computerHitCount = 0;
    string compFile;
    string compLetter;

    // ARRAYS
    int destroyer[2][2] = { {1,1}, {1,1} };

    char userBoard[4][4] = {
     {' ','1','2','3'}, {'1','o','o','o'},
     {'2','o','o','o'}, {'3','o','o','o'}};

    char shadowBoard[4][4] = {
     {' ','1','2','3'}, {'1','x','x','x'},
     {'2','x','x','x'}, {'3','x','x','x'}};


    char computerBoard[4][4] = {
    {' ','1','2','3'}, {'1','o','o','o'},
    {'2','o','o','o'}, {'3','o','o','o'}};


    // load computer's board from file
    // 6. FILE I/O
    cout << "Choose a comptuer Board! Type either A, B, C: ";
    cin >> compLetter;
    compFile = "computerBoard_" + compLetter + ".txt";
    ifstream myfile(compFile);
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            myfile >> a;
            computerBoard[i][j] = a;
        }
    }

    // Game Description
    cout << "\n" << setfill('*') << setw(80) << "\n";
    cout << "\n\nWelcome to mini battleship! You will play on a 3 x 3 grid, with one ship, and try to guess the computer's ship before your ship gets sunk!" << "\n\n";
    cout << "The game relies on the following codes to display the board:" << "\n";
    cout << "o = open space" << "\n";
    cout << "s = ship" << "\n";
    cout << "x = unknown" << "\n";
    cout << "h = hit" << "\n";
    cout << "m = miss" << "\n";
    cout << "\n" << "The program will output two gameboards, your board, and what you have learned of your opponents board (shadow board). Since you don't know their setup, your opponents board will initially be filled with x's." << "\n";

    cout << "\n" << "Your board" << "\n\n";
    displayBoard(userBoard);
    cout << "\n" << "Opponent's shadow board" << "\n\n";
    displayBoard(shadowBoard);

    // Input User's Board Set Up
    // 3. INPUTS AND OUTPUT
    // 8. INTERACTION
    cout << "\n" << setfill('*') << setw(80) << "\n";
    cout << "\n";
    cout << "Let's set up your board.\n\n";
    cout << "Enter two sets of adjacent coordinates for your battleship\n\n";
    cout << "First coordinate:\n";
    cout << "Row:";
    cin >> destroyer[0][0];
    cout << "Column:";
    cin >> destroyer[0][1];
    cout << "\n";
    cout << "Second coordinate:\n";
    cout << "Row:";
    cin >> destroyer[1][0];
    cout << "Column:";
    cin >> destroyer[1][1];
    cout << "\n";

    // Add ships to the board and display
    userBoard[destroyer[0][0]][destroyer[0][1]] = 's';
    userBoard[destroyer[1][0]][destroyer[1][1]] = 's';

    cout << "\n" << "Here's your board setup" << "\n\n";
    displayBoard(userBoard);


    cout << "\n" << setfill('*') << setw(80) << "\n";
    cout << "\n" << "Let's begin!" << "\n";
    cout << "\n" << setfill('*') << setw(80) << "\n";

    // game play
    // 7. ITERATION (LOOPS)
    while ( computerHitCount < 2 && userHitCount < 2 ) {

        // user turn
        // 9. CONTROL
        if (userTurn) {

            cout << "IT'S YOUR TURN\n\n";

            // user guess
            cout << "Enter the row coordinate for your guess:";
            cin >> rowGuess;
            cout << "Enter the column coordinate for your guess:";
            cin >> colGuess;

            // get results
            result = computerBoard[rowGuess][colGuess];

            // 9. CONTROL
            if (result == 's') {

                // user hit
                computerHitCount += 1;
                cout << "\nHIT!\n";
                computerBoard[rowGuess][colGuess] = 'h';
                shadowBoard[rowGuess][colGuess] = 'h';
                cout << "\n" << "Shadow board" << "\n\n";
                displayBoard(shadowBoard);

                // switch to the computer
                userTurn = false;
                cout << "\n" << setfill('*') << setw(80) << "\n";

            }
            else if (result == 'o') {

                // user miss
                cout << "\nMISS!\n";
                computerBoard[rowGuess][colGuess] = 'm';
                shadowBoard[rowGuess][colGuess] = 'm';
                cout << "\n" << "Shadow board" << "\n\n";
                displayBoard(shadowBoard);

                // switch to the computer
                userTurn = false;
                cout << "\n" << setfill('*') << setw(80) << "\n";
            }
            else {
                // repeat guess

                cout << "\nTry again! You either entered something out of bounds or already guessed that space.\n";
                cout << "\n" << "Shadow board" << "\n\n";
                displayBoard(shadowBoard);

                // stay with the user
                userTurn = true;
            }
        }
        else {

            // computer guess
            rowGuess = rand() % 3 + 1;
            colGuess = rand() % 3 + 1;

            // get results
            result = userBoard[rowGuess][colGuess];

            // 9. CONTROL
            if (result == 's') {

                // computer hit
                cout << "COMPUTER'S TURN\n\n";

                userHitCount += 1;
                cout << "\nHIT!\n";
                userBoard[rowGuess][colGuess] = 'h';
                cout << "\n" << "Your board" << "\n\n";
                displayBoard(userBoard);

                // switch to the user
                userTurn = true;
                cout << "\n" << setfill('*') << setw(80) << "\n";

            }
            else if (result == 'o') {

                // computer miss
                cout << "COMPUTER'S TURN\n\n";

                cout << "\nMISS!\n";
                userBoard[rowGuess][colGuess] = 'm';
                cout << "\n" << "Your board" << "\n\n";
                displayBoard(userBoard);

                // switch to the user
                userTurn = true;
                cout << "\n" << setfill('*') << setw(80) << "\n";
            }
            else {
                // repeat guess

                // stay with the computer
                userTurn = false;
            }
        }
    }

    // Let the user know who won
    if (userHitCount < 2) {
        cout << "\n\nYou sunk the Computer's battleship! Congratulations!" << endl;
    }
    else {
        cout << "\n\nSorry, the Computer has annihilated your battleship. :(" << endl;
    }
    cout << "\n" << setfill('*') << setw(80) << "\n";

    // 6. FILE I/O
    cout << "\n\nYou can see the game's results outputed to the text file: computer_board_results.txt" << endl;
    ofstream outFile("computer_board_results.txt");

    // reveal computer's board
    outFile << "Results: Computer's Board.\n\n";

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            outFile << computerBoard[i][j] << " ";
        }
        outFile << "\n";
    }
    outFile.close();

    return 0;

}
