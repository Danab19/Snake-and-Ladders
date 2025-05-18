#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

//Functions prototypes
void Play();
int SnakesOrLadders(int &);
int SpecifyRow(int &);
void GameBoard(int, int, char, char);
int RollDice();
void DiceDraw(int);
void SaveScores(char, char, int, int);

int main()
{
    //Introduce the user
    cout << endl << "Hello, this is the Snake and Ladders game for two players" << endl;
    cout << "or one player vs. computer" << endl;
    cout << "Please choose an option from the main menu" << endl;
    cout << "-------------------------" << endl;

    //Define the variable that will hold the user's menu choice
    int MenuChoice;

    //Keep the main menu repeating until the player chooses quit
    do
    {
        //Display the main menu to the user
        cout << "Main Menu" << endl;
        cout << "1. How to Play" << endl;
        cout << "2. Play" << endl;
        cout << "3. Last Game Dice Rolls" << endl;
        cout << "4. Quit" << endl;
        cout << "Choice: ";
    
        //Take the user's menu choice and validate it    
        do
        {
            //Take the user's choice
            cin >> MenuChoice;

            //Validate the user's choice
            if ( !(MenuChoice >= 1 && MenuChoice <= 4) )
            {
            //Display that the user's choice is invalid
            cout << "Invalid Input" << endl
            << "Please enter a valid choice: ";
            }
        } while (!(MenuChoice >= 1 && MenuChoice <= 4));

        //Use a switch statement to take the user to the appropriate choice
        switch (MenuChoice)
        {
            //This is the "How to Play" case
            case 1: cout << "The goal is to be the person who gets to the last square." << endl;
                    cout << "If you got caught up in a snake, you will go backwards," << endl;
                    cout << "and if you got on a ladder, you will go upwards." << endl;
                    cout << "Player one will be the first one to play, then player two." << endl;
                    cout << "If you got six, you will roll the dice again." << endl;
                    cout << "You will need the exact number that will get you to the last square to win." << endl;
                    cout << "If you didn't get it. You will stay on the same square." << endl << endl;
;
            break;

            //This is the "Play" case
            case 2: Play();
            break;

            //This is the "Last Game Dice Rolls" case
            case 3: //Define a string variable to hold the lines of text
                    string DisplayText;

                    //Define and open the file that we will input the scores from
                    ifstream ScoresFile("Scores.txt");

                    //Check if the file was opened successfully
                    //Do this if the file failed to open
                    if (ScoresFile.fail())
                    {
                        cout << "Error opening the file." << endl 
                        << "The file might not exist." << endl << endl;
                    }

                    //Do this if the file was opened successfully
                    else
                    {
                        //Read the data from the input file and display them
                        while (ScoresFile)
                        {
                            getline(ScoresFile, DisplayText);
                            cout << DisplayText << endl;
                        }

                        //Close the file
                        ScoresFile.close();
                    }
            break;
        }
    } while(MenuChoice != 4);

    cout << "Program ended" << endl;
    
    return 0;
}

void Play()
{
    //Variable to hold the player's menu choice
    int choice;

    //Let the user choose the playing mode
    cout << "1. Player vs. Player" << endl
    << "2. Player vs. Computer" << endl
    << "Playing Mode: ";

    //Take and validate the user's choice
    do
    {
        //Take the user's choice
        cin >> choice;

        //Validate the user's choice
        if ( !(choice >= 1 && choice <= 2) )
        {
        //Display that the user's choice is invalid
        cout << "Invalid Input" << endl
        << "Please enter a valid choice: ";
        }
    } while (!(choice >= 1 && choice <= 2));

    //Take the user to the corresponding choice
    switch (choice)
    {
        //Do this when the user chooses a player vs player
        case 1: {
                //Define character variables to identify each player
                char Player1, Player2;

                //Variables that will hold the players' positions
                int Player1Position = 0, Player2Position = 0;
 
                //Variables that will count the number of times each player rolled the dice
                int Player1RollsCounter = 0, Player2RollsCounter = 0;

                //A variable that will hold the random number that the players get from the dice
                int DiceValue;

                cout << "Please enter a character to identify player 1: ";
                cin >> Player1;
                cout << "Please enter a character to identify player 2: ";
                cin >> Player2;
                cin.ignore();

                //Keep the game going until a player reaches the last square
                do 
                {
                    cout << "It is the round of player \"" << Player1 
                    << "\". Press enter to roll the dice.";
                    cin.get();

                    do
                    {
                        //Generate a random number from 1 to 6
                        //and put it in the DiceValue variable
                        DiceValue = RollDice();

                        //Increment the counter each time player 1 rolls the dice
                        Player1RollsCounter++;

                        //Show the number that the player got
                        DiceDraw(DiceValue);

                        //If we added the dice value to the player's position, will it exceed 100?
                        if ((Player1Position + DiceValue) <= 100)
                        //If it will not, add the dice value to the player's position
                            Player1Position += DiceValue;
                        //If it will, don't add it to the player's position
                        else 
                            cout << "Sorry player \"" << Player1 << "\", your position can't reach 100" << endl << endl;

                        //If the player reached a hundred after rolling the dice, stop the game
                        if(Player1Position == 100)
                        {
                            cout << "Congratulations player \"" << Player1 << "\", you have won!" << endl << endl;
                            break;
                        }
                        
                        //Check if the player has stepped on a snake or a ladder
                        SnakesOrLadders(Player1Position);

                        if (DiceValue == 6)
                        {
                            cout << "You got 6, press enter to play again";
                            cin.get();
                        }
                    } while (DiceValue == 6);
        
                //If the first player reached the 100th square, draw the board and don't let the second player play
                if(Player1Position == 100)
                {
                    GameBoard(Player1Position, Player2Position, Player1, Player2);
                    break;
                }
                    
                cout << "It is the round of player \"" << Player2 
                << "\". Press enter to roll the dice.";
                cin.get();

                do
                {
                    //Generate a random number from 1 to 6
                    //and put it in the DiceValue variable
                    DiceValue = RollDice();

                    //Increment the counter each time player 2 rolls the dice
                    Player2RollsCounter++;

                    //Show the number that the player got
                    DiceDraw(DiceValue);

                    //If we added the dice value to the player's position,
                    //will it exceed 100?
                    if ((Player2Position + DiceValue) <= 100)
                    //If it will not exceed 100, add the dice value to the player's position
                        Player2Position += DiceValue;
                    //If it will exceed 100, don't add it to the player's position
                    else 
                        cout << "Sorry player \"" << Player2 << "\", your position can't reach 100" << endl << endl;

                    //If the player reached a hundred after rolling the dice, stop the game
                    if(Player2Position == 100)
                    {
                        cout << "Congratulations player \"" << Player2 << "\", you have won!" << endl << endl;
                        break;
                    }

                    //Check if the player has stepped on a snake or a ladder
                    SnakesOrLadders(Player2Position);

                    if (DiceValue == 6)
                    {
                        cout << "You got 6, press enter to play again";
                        cin.get();
                    }
                } while (DiceValue == 6);

                //Show the game board
                GameBoard(Player1Position, Player2Position, Player1, Player2);
                } while ( Player1Position != 100 && Player2Position != 100 );

                //Write the data of the game to the text file
                SaveScores(Player1, Player2, Player1RollsCounter, Player2RollsCounter);
                break;
                }

        //Do this when the user chooses a player vs. computer
        case 2: {
                //Define character variables to identify the player and the computer
                char Player, Computer = '@';

                //Variables that will hold the player and the computer positions
                int PlayerPosition = 0, ComputerPosition = 0;
 
                //Variables that will count the number of times the player and copmuter rolled the dice
                int PlayerRollsCounter = 0, ComputerRollsCounter = 0;

                //A variable that will hold the random number from rolling the dice
                int DiceValue;

                //Let the player enter a character to identify him/herself
                cout << "Please enter a character to identify the player: ";
                cin >> Player;
                cin.ignore();

                //Keep the game going until the player or the computer reaches the last square
                do 
                {
                    cout << "It is the round of player \"" << Player 
                    << "\". Press enter to roll the dice.";
                    cin.get();

                    do
                    {
                        //Generate a random number from 1 to 6
                        //and put it in the DiceValue variable
                        DiceValue = RollDice();

                        //Increment the counter each time the player rolls the dice
                        PlayerRollsCounter++;

                        //Show the number that the player got
                        DiceDraw(DiceValue);

                        //If we added the dice value to the player's position, will it exceed 100?
                        if ((PlayerPosition + DiceValue) <= 100)
                            //If it will not, add the dice value to the player's position
                            PlayerPosition += DiceValue;
                        //If it will, don't add it to the player's position
                        else 
                            cout << "Sorry player \"" << Player << "\", your position can't reach 100" << endl << endl;

                        //If the player reached a hundred after rolling the dice, stop the game
                        if(PlayerPosition == 100)
                        {
                            cout << "Congratulations player \"" << Player << "\", you have won!" << endl << endl;
                            break;
                        }
                        
                        //Check if the player has stepped on a snake or a ladder
                        SnakesOrLadders(PlayerPosition);

                        if (DiceValue == 6)
                        {
                            cout << "You got 6, press enter to play again";
                            cin.get();
                        }
                    } while (DiceValue == 6);
        
                //If the player reached the 100th square, draw the board,
                //stop the game, and don't let the computer play

                if(PlayerPosition == 100)
                {
                    GameBoard(PlayerPosition, ComputerPosition, Player, Computer);
                    break;
                }
                    
                cout << "It is the round of the computer \"" << Computer << "\"" << endl;

                do
                {
                    //Generate a random number from 1 to 6
                    //and put it in the DiceValue variable
                    DiceValue = RollDice();

                    //Increment the counter each time the computer rolls the dice
                    ComputerRollsCounter++;

                    //Show the number that the computer got
                    DiceDraw(DiceValue);

                    //If we added the dice value to the computer's position,
                    //will it exceed 100?
                    if ((ComputerPosition + DiceValue) <= 100)
                        //If it will not exceed 100, add the dice value to the player's position
                        ComputerPosition += DiceValue;
                    //If it will exceed 100, don't add it to the computer's position
                    else
                        cout << "The computer \"" << Computer << "\" position can't reach 100" << endl << endl;

                    //If the computer reached a hundred after rolling the dice, stop the game
                    if(ComputerPosition == 100)
                    {
                        cout << "Congratulations computer \"" << Computer << "\", you have won!" << endl 
                        << "Sorry player " << Player << " :(" << endl << endl;
                        break;
                    }

                    //Check if the computer has stepped on a snake or a ladder
                    SnakesOrLadders(ComputerPosition);

                    //Display that the computer will play again because it got 6
                    if (DiceValue == 6)
                        cout << "The computer \"" << Computer << "\" got 6. It will play again" << endl;
                } while (DiceValue == 6);

                //Show the game board
                GameBoard(PlayerPosition, ComputerPosition, Player, Computer);
                } while ( PlayerPosition != 100 && ComputerPosition != 100 );

                //Write the data of the game to the text file
                SaveScores(Player, Computer, PlayerRollsCounter, ComputerRollsCounter);
                break;
                }
        break;
    }
}

int SnakesOrLadders(int &PlayerPosition)
{
    //Check if the player has came across a snake
    if (PlayerPosition == 36)
    {
        cout << "Sorry, you've been caught in the 36 → 6 snake" << endl << endl;
        PlayerPosition = 6;
    }
    else if (PlayerPosition == 48)
    {
        cout << "Sorry, you've been caught in the 48 → 26 snake" << endl << endl;
        PlayerPosition = 26;
    }
    else if (PlayerPosition == 62)
    {
        cout << "Sorry, you've been caught in the 62 → 18 snake" << endl << endl;
        PlayerPosition = 18;
    }
    else if (PlayerPosition == 88)
    {
        cout << "Sorry, you've been caught in the 88 → 24 snake" << endl << endl;
        PlayerPosition = 24;
    }
    else if (PlayerPosition == 95)
    {
        cout << "Sorry, you've been caught in the 95 → 56 snake" << endl << endl;
        PlayerPosition = 56;
    }

    //Check if the player has came across a ladder
    if (PlayerPosition == 4)
    {
        cout << "You climbed the 4 → 14 ladder!" << endl << endl;
        PlayerPosition = 14;
    }
    else if (PlayerPosition == 8)
    {
        cout << "You climbed the 8 → 30 ladder!" << endl << endl;
        PlayerPosition = 30;
    }
    else if (PlayerPosition == 21)
    {
        cout << "You climbed the 21 → 42 ladder!" << endl << endl;
        PlayerPosition = 42;
    }
    else if (PlayerPosition == 28)
    {
        cout << "You climbed the 28 → 76 ladder!" << endl << endl;
        PlayerPosition = 76;
    }
    else if (PlayerPosition == 50)
    {
        cout << "You climbed the 50 → 67 ladder!" << endl << endl;
        PlayerPosition = 67;
    }
    else if (PlayerPosition == 71)
    {
        cout << "You climbed the 71 → 92 ladder!" << endl << endl;
        PlayerPosition = 92;
    }

    return PlayerPosition;
}

int SpecifyRow(int &Position)
{
    int RowNum;

    if (Position <= 100 && Position >= 91)
        RowNum = 2;
    else if (Position <= 90 && Position >= 81)
        RowNum = 5;
    else if (Position <= 80 && Position >= 71)
        RowNum = 8;
    else if (Position <= 70 && Position >= 61)
        RowNum = 11;
    else if (Position <= 60 && Position >= 51)
        RowNum = 14;
    else if (Position <= 50 && Position >= 41)
        RowNum = 17;
    else if (Position <= 40 && Position >= 31)
        RowNum = 20;
    else if (Position <= 30 && Position >= 21)
        RowNum = 23;
    else if (Position <= 20 && Position >= 11)
        RowNum = 26;
    else if (Position <= 10 && Position >= 1)
        RowNum = 29;
    else
    {
        cout << "I've set the row number to -1 because" << endl
        << "there is a problem with the position value" << endl;
        RowNum = -1;
    }

    return RowNum;
}

void GameBoard(int FirstPlayerPosition, int SecondPlayerPosition, char Player1Letter, char Player2Letter)
{
    //Make sure the board is on a line by itself
    cout << endl;

    //Define a variable to hold the numbers that will appear on the board
    int board_num=100;

    //Define the variables that will specify in which row each player's letter should appear
    int Player1LetterRow = SpecifyRow(FirstPlayerPosition), Player2LetterRow = SpecifyRow(SecondPlayerPosition);

    //Use an outer loop to draw all the rows of the board
    for (int row = 0; row < 31; row++)
    {
        //For the rows 0, 3, 6, ..... do this
        if (row % 3 == 0)
        {
            for (int i = 0; i < 10; i++)
            {
                cout << " ----- ";
            }

            cout << endl;
        }

        //For the rows 1, 4, 7, ..... do this
        if (((row - 1) % 3) == 0)
        {
            for (int j = 0; j < 10; j++, board_num--)
            {
                if (board_num <= 9)
                    cout << "|  " << board_num << "  |";
                else if (board_num >= 10)
                    cout << "| " << left << setw(3) << board_num << " |";
            }
            cout << endl;
        }

        //For the rows 2, 5, 8, ..... do this
        if (((row - 2) % 3) == 0)
        {
            for (int k = 0; k < 10; k++)
            {
                cout << "| ";

                /*Check if the current row is the row that the player's letter 
                should appear in (specified according to the player's position),
                if not, just skip this if statment and put a space instead*/
                if (row == Player1LetterRow)
                {
                    /*Check if the player's position falls in this range. 
                    If yes, the formula inside this if statement will be
                    suitable to specify where to display the player's position*/
                    if (FirstPlayerPosition <= 100 && FirstPlayerPosition >= 91)
                    {
                        /*The "k" will repeat ten times to draw the ten squares for each row.
                        Using the calculation below, specify in which one of these ten squares
                        the player's letter should appear*/
                        if (abs(FirstPlayerPosition - 100) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 90 && FirstPlayerPosition >= 81)
                    {
                        if (abs(FirstPlayerPosition - 90) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 80 && FirstPlayerPosition >= 71)
                    {
                        if (abs(FirstPlayerPosition - 80) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 70 && FirstPlayerPosition >= 61)
                    {
                        if (abs(FirstPlayerPosition - 70) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 60 && FirstPlayerPosition >= 51)
                    {
                        if (abs(FirstPlayerPosition - 60) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 50 && FirstPlayerPosition >= 41)
                    {
                        if (abs(FirstPlayerPosition - 50) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 40 && FirstPlayerPosition >= 31)
                    {
                        if (abs(FirstPlayerPosition - 40) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 30 && FirstPlayerPosition >= 21)
                    {
                        if (abs(FirstPlayerPosition - 30) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 20 && FirstPlayerPosition >= 11)
                    {
                        if (abs(FirstPlayerPosition - 20) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                    else if (FirstPlayerPosition <= 10 && FirstPlayerPosition >= 1)
                    {
                        if (abs(FirstPlayerPosition - 10) == k)
                            cout << Player1Letter;
                        else
                            cout << " ";
                    }
                }
                else 
                    cout << " ";

                cout << " ";

                if (row == Player2LetterRow)
                {
                    if (SecondPlayerPosition <= 100 && SecondPlayerPosition >= 91)
                    {
                        if (abs(SecondPlayerPosition - 100) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 90 && SecondPlayerPosition >= 81)
                    {
                        if (abs(SecondPlayerPosition - 90) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 80 && SecondPlayerPosition >= 71)
                    {
                        if (abs(SecondPlayerPosition - 80) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 70 && SecondPlayerPosition >= 61)
                    {
                        if (abs(SecondPlayerPosition - 70) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 60 && SecondPlayerPosition >= 51)
                    {
                        if (abs(SecondPlayerPosition - 60) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 50 && SecondPlayerPosition >= 41)
                    {
                        if (abs(SecondPlayerPosition - 50) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 40 && SecondPlayerPosition >= 31)
                    {
                        if (abs(SecondPlayerPosition - 40) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 30 && SecondPlayerPosition >= 21)
                    {
                        if (abs(SecondPlayerPosition - 30) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 20 && SecondPlayerPosition >= 11)
                    {
                        if (abs(SecondPlayerPosition - 20) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                    else if (SecondPlayerPosition <= 10 && SecondPlayerPosition >= 1)
                    {
                        if (abs(SecondPlayerPosition - 10) == k)
                            cout << Player2Letter;
                        else
                            cout << " ";
                    }
                }
                else 
                    cout << " ";

                cout << " |";
            }
            cout << endl;
        }
    }

    //Make sure the board is on a line by itself
    cout << endl;

    //Show the squares where the snakes and ladders are
    cout << left;
    cout << setw(13) << "Ladders:" << "Snakes:" << endl;
    cout << setw(15) << "4 → 14" << "36 → 6" << endl;
    cout << setw(15) << "8 → 30" << "48 → 26" << endl;
    cout << setw(15) << "21 → 42" << "62 → 18" << endl;
    cout << setw(15) << "28 → 76" << "88 → 24" << endl;
    cout << setw(15) << "50 → 67" << "95 → 56" << endl;
    cout << setw(15) << "71 → 92" << endl << endl;
}

int RollDice()
{
    unsigned seed = time(0);
    srand(seed);

    const int MAX_NUMBER = 6, MIN_NUMBER = 1;

    int Random_Number = (rand()%(MAX_NUMBER-MIN_NUMBER+1))+MIN_NUMBER;

    return Random_Number;
}

void DiceDraw(int PlayerDiceValue)
{
    cout << endl;

    switch (PlayerDiceValue)
    {
        case 1: cout << " --- " << endl;
                cout << "| " << PlayerDiceValue << " |" << endl;
                cout << " --- " << endl;
        break;

        case 2: cout << " --- " << endl;
                cout << "| " << PlayerDiceValue << " |" << endl;
                cout << " --- " << endl;
        break;

        case 3: cout << " --- " << endl;
                cout << "| " << PlayerDiceValue << " |" << endl;
                cout << " --- " << endl;
        break;

        case 4: cout << " --- " << endl;
                cout << "| " << PlayerDiceValue << " |" << endl;
                cout << " --- " << endl;
        break;

        case 5: cout << " --- " << endl;
                cout << "| " << PlayerDiceValue << " |" << endl;
                cout << " --- " << endl;
        break;

        case 6: cout << " --- " << endl;
                cout << "| " << PlayerDiceValue << " |" << endl;
                cout << " --- " << endl;
        break;
    }

    cout << endl;
}

void SaveScores(char Player1Character, char Player2Character, int Player1Rolls, int Player2Rolls)
{
    //Define and open the file that we will output the scores to
    ofstream ScoresFile("Scores.txt");

    //Check if the file was opened successfully
    if (ScoresFile.fail())
    {
        cout << "Error opening the file.\n";
        return;
    }

    //Write the scores for the first player in the output file
    ScoresFile << "Player \"" << Player1Character << "\" rolled the dice "
    << Player1Rolls << " times." << endl;

    //Write the scores for the second player in the output file
    ScoresFile << "Player \"" << Player2Character << "\" rolled the dice "
    << Player2Rolls << " times." << endl << endl;

    //Close the file
    ScoresFile.close();
    cout << "Data have been written successfully to the \"Scores.txt\" file." << endl << endl;
}