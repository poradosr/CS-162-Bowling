
/******************************************************
Program: Bowling.cpp
Author: Raz Poradosu
Date: 10/09/2022
Description: Simulates a single player bowling game, prompting the user to generate random numbers for each roll. The program's logic works along the rules of bowling.
** Input: User's name, enter clicks
** Output: 10-11 Bowling game frames according to the rules of bowling.
 ******************************************************/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
using namespace std;

/*
Function: random_num
Description: Generates a random number from 0-10. The sum of 2 randomly generated numbers does not exceed 10.
Parameters: A previously generated score
Pre-Conditions: Variable names must be created prior to generating the random scores.
Post-Conditions: The sum of the previously rolled random number and the following one must be less than 10.
*/
int random_num(int prevScore)
{
    int rollScore = rand()% (11-prevScore);
    return rollScore;
}

/*
Function:rollScoreString
Description: Receives roll score and returns string explaining what the user rolled.
Parameters: integer with the value of generated random number.
Pre-Conditions: A random number was generated and stored in a variable
Post-Conditions: N/A
*/
int rollScoreString(int num)
{
    if (num == 10) {
        cout << "You got a strike, 10 pins." << endl;
    }
    if (num < 10) {
        cout << "You knocked down " << num << " pins." << endl;
    }
    return 0;
}

/*
Function: CurrentFrame1
Description: Generates frame table with current scores, frame scores and total score.
Parameters: Current score, array of current scores, array of frame scores, array of state of frame.
Pre-Conditions: A current score was generated and stored in a variable, all arrays initialized to store values of -1,
                state of frame function was used prior.
Post-Conditions: Indexes of different length arrays must be alligned through logic.
*/
int currentFrame1(int currentScore, int array[], int frameScores[], int stateOfArray[])
{
    cout << "Name    |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 | Total " << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Player1 |";
    
    
    for (int i = 0; i < 11; i++){
        if (array[2*i] == -1)
            cout << "     |";
        else {
            if (array[2*i] == 10){
                cout << "X  ";
            }
            else if (array[2*i] == 0){
                cout << "-  ";
            }
            else {
                cout << array[2*i] << "  ";
            }
            if (array[2*i+1] == -1) {
                cout << "  |";
            }
            else if (array[2*i+1] == 0) {
                cout << "- |";
            }
            else {
                if (array[2*i+1] + array[2*i] == 10) {
                    cout << "/ |"; }
                else {
                    cout << array[2*i+1] << " |"; }
            }
        }
    }
    cout << endl << "        |";
    
    int totalScore = 0;
    for (int j=0; j < 10; ++j) {
        if (frameScores[j] == -1){
            cout << "     |";
        }
        else {
            totalScore += frameScores[j];
                    if ((stateOfArray[j] == 1) && stateOfArray[j+1] == -1) { // Will not print frame score if strike
                    cout << "     |";
                }
                    else if ((stateOfArray[j] == 2) && (stateOfArray[j+1] == -1)) { // Will not print frame score if spare
                        cout << "     |";
                    }
                
                    else {
                        cout << setw(5) << totalScore << "|"; // Will print frame score if regular roll
                    }

            }

    }
    cout << setw(5) << totalScore << "|" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    return 0;
}


/*
Function:gameLogic
Description: Populates the state of the frame array according to rules of bowling.
Parameters: both roll scores of each frame, array of frame scores, array of frame states, the index of frame run in main.
Pre-Conditions: all arrays initialized to -1, 2 random numbers were generated in the frame and stored in variables.
Post-Conditions: logic in frame generating funtion takes this function's populated array output as input.
*/
int gameLogic(int score1, int score2, int frameScoreArray[], int stateOfScoreArray[], int frame)
{

    if (score1 == 10) {
        stateOfScoreArray[frame] = 1; // if 1: state of strike
    }
    else if (score1 + score2 == 10) {
        stateOfScoreArray[frame] = 2; // if 2: state of spare
    }
    else {
        stateOfScoreArray[frame] = 0; // if 0: state of regular roll
    }
    
    return 0;
}


int main()
{
    // Seeds the random numbers for the game rolls
    srand(time(NULL));
    string name;
    
    // Inroduction to game and player
    cout << "Welcome to bowling!" << endl;
    cout << "What's your name? ";
    cin >> name;
    cout << endl;
    cout << "Hello " << name << "!" << endl;
    cout << endl;
    
    int j = 0;
    
    int currentScoreArray[21]; // Array of current scores
    int frameScoreArray[11]; // Array of Frame scores
    int stateOfScoreArray[11]; // Array of state of frame (strike/spare/regular)
    
   // Initializing all array values to -1
    for (int i = 0; i < 21; i++) {
        currentScoreArray[i] = -1;
        if(i < 10) {
           frameScoreArray[i] = -1;
           stateOfScoreArray[i] = -1;
        }
    }
    
    // Loop running frames of the game
    for (int i=0; i<=10; ++i) {

        if (frameScoreArray[9] == 10) { // Special case of rolling strike or spare on 10th frame
            cout << "You get another roll! Press enter to roll" << endl;
            cin.get();
            int extraRoll = random_num(0);
            currentScoreArray[20] = extraRoll;
            cout << "You knocked down " << extraRoll << " pins." << endl << endl;
            frameScoreArray[10] = extraRoll;
            stateOfScoreArray[9] = 2;
            frameScoreArray[9] += extraRoll; // Adding 11th frame score to total score
            currentFrame1(j, currentScoreArray, frameScoreArray, stateOfScoreArray);
            cout << "Game Over." << endl;
            break;
        }
        
        cout << endl << "frame " << i+1 << "..." << endl << endl;
        cout << "Press enter to roll." << endl;
        cin.get();
    
        int score1 = random_num(0); // Generating first random number of frame
        rollScoreString(score1); // Outputting what the user rolled
        cout << endl;
        currentScoreArray[j] = score1; // Adding score 1 of frame to array of scores
        j++;
        if (score1 == 10) {
            j++;
        }

        currentFrame1(j, currentScoreArray, frameScoreArray, stateOfScoreArray); // Displaying score board after roll 1
        if (score1 == 10) { // After strike skip to next frame
            frameScoreArray[i] = 10;
            if ((i > 0) && frameScoreArray[i-1] == 10) {
                frameScoreArray[i-1] += frameScoreArray[i];
            }
            stateOfScoreArray[i] = 1;
            continue;
        }
            
        cout << endl << "Press enter to roll.";
        cin.get();
        
        int score2 = random_num(score1); // Generating second random number of frame
        rollScoreString(score2); // Outputting what the user rolled
        currentScoreArray[j] = score2; // Adding score 2 of frame to array of scores
        frameScoreArray[i] = score1 + score2; // Calculating frame score and adding it to array
        if (i > 0) {
            if (stateOfScoreArray[i-1] == 2) {
                frameScoreArray[i-1] += score1; // logic of scoring after rolling spare
    
            }
            else if (stateOfScoreArray[i-1] == 1) {
                frameScoreArray[i-1] += score1 + score2; // logic of scoring after rolling strike
        }
    }
        gameLogic(score1, score2, frameScoreArray, stateOfScoreArray, i); // assigning state of frame
        j++;
        
        cout << endl;
        currentFrame1(j, currentScoreArray, frameScoreArray, stateOfScoreArray); // Displaying score board after roll 2
        
        if ((i==9) && (stateOfScoreArray[9] == 0)) { // Regular roll on final frame - ending game
            cout << "Game over." << endl;
            break;
        }
    }
}
