/* 
 * File:   main.cpp
 * Author: Heriberto Prieto
 * Created on June 09, 2017, 5:26 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

int *genCode(int);                  //Generates random 4-Digit Code
void prntCde(int *,int);            //Prints code
int **crtBrd(int,int);              //Allocates/'Creates' Mastermind code
void rsetBrd(int **,int,int);       //Resets Board to 0s
void prntBrd(int **,int,int);       //Prints Board
void destroy(int **,int,int);       //Deallocates Board Memory
void tkGuess(int *,int,int);        //Takes in players guess
bool gameWon(int *,int *,int);      //Returns true if code was correct
void chckGme(int *,int *,int *,int);//Check and set score after code guess
void prntGme(int **,int **,int,int);//Print board with guess score
void endGame(int **,int **,int *,int,int);//Deallocates memory

int main(int argc, char** argv) {
    //Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    bool won    = false; //False while code not guessed
    int cLength = 4;     //Length of character
    int turns   = 10;    //Number of turns in game
    int nTurn   = 9;     //Turn number, decreases per turn
    int *code   = genCode(cLength);
    int **board = crtBrd(cLength,turns);
    int **score = crtBrd(cLength,turns);
    //Output to User/Player
    cout<<"Welcome to MasterMind!"<<endl;
    //Begin Game
    while (nTurn >= 0 && !won) {
        //Print Game for Player Reference
        prntGme(board,score,cLength,turns);
        cout<<"Guesses Left: "<<nTurn+1<<endl;
        //Take player input
        tkGuess(board[nTurn],nTurn,cLength);
        //Check guesses
        chckGme(board[nTurn],score[nTurn],code,cLength);
        //Check if player won
        won = gameWon(board[nTurn],code,cLength);
        nTurn--;
    }
    prntGme(board,score,cLength,turns);
    //Output Message if player won
    if (won)
        cout<<"You got it! ";
    else
        cout<<"Sorry, try again!";
    cout<<"The code was: ";
    prntCde(code,cLength);
    //Destroy code, score and board
    endGame(board,score,code,cLength,turns);
    return 0;
}

int *genCode(int cLength) {
    int *code = new int[cLength];
    for (int i = 0; i < cLength; i++)
        code[i] = rand() % 8 + 1;
    return code;
}

void endGame(int **board,int **score,int *code,int cLength,int turns) {
    destroy(board,cLength,turns);
    destroy(score,cLength,turns);
    delete []code;
}

void prntCde(int *code,int cLength) {
    for (int i = 0; i < cLength; i++)
        cout<<code[i]<<" ";
    cout<<endl;
}

int **crtBrd(int cLength,int turns) {
    //Allocate Memory for Array
    int **board = new int*[turns];
    for (int row = 0; row < turns; row++)
        board[row] = new int[cLength];
    rsetBrd(board,cLength,turns);
    return board;
}

void rsetBrd(int **board,int cLength,int turns) {
    //Fill Board with 0's
    for (int row = 0; row < turns; row++)
        for (int col = 0; col < cLength; col++)
            board[row][col] = 0;
}

void prntBrd(int **board,int cLength,int turns) {
    for (int row = 0; row < turns; row++) {
        for (int col = 0; col < cLength; col++)
            cout<<board[row][col]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void prntGme(int **board,int **score,int cLength,int turns) {
    cout<<"|----------------------------------------------|"<<endl;
    cout<<"|----------------------------------------------|"<<endl;
    cout<<"| Mastermind Board     ||        Score Board   |"<<endl;
    for (int row = 0; row < turns; row++) {
        cout<<"|";
        for (int col = 0; col < cLength; col++)
            cout<<"| "<<board[row][col]<<" ";
        cout<<"||    ||    |";
        for (int col = 0; col < cLength; col++)
            if (score[row][col] == 0)
                cout<<"|   ";
            else if (score[row][col] == 1)
                cout<<"| X ";
            else if (score[row][col] == 2)
                cout<<"| $ ";
        cout<<"||"<<endl;
    }
    cout<<"$: Correct value and correct position"<<endl;
    cout<<"X: Correct value, different position"<<endl;
    cout<<endl;
}

void chckGme(int *board,int *score,int *code,int cLength) {
    int s = 0,c = 0;
    //Check how many characters they guessed correctly, regardless of position
    for (int i = 0; i < cLength; i++)
        for (int j = 0; j < cLength; j++)
            if (code[i] == board[j] && i != j)
                c++;
    //Check how many characters were in the right position
    for (int i = 0; i < cLength; i++)
        if (board[i] == code[i])
            s++;
    //Same value AND same index
    for (int i = 0; i < s; i++)
        score[i] = 2;
    //Same value, different index
    for (int i = s; i < s+c; i++)
        score[i] = 1;
}

void destroy(int **board,int cLength,int turns) {
    for (int row = 0; row < turns; row++)
        delete []board[row];
    delete []board;
}

void tkGuess(int *guess,int turn,int cLength) {
    int c = 0, i;
    while (c < cLength) {
        cout<<"Input your guess from 0 to 9:"<<endl;
        cin>>i;
        cin.clear();
        if (i >= 0 && i <= 9)
            guess[c] = i;
        else c--;//Invalid Entry, retake turn
        c++;
    }
}

bool gameWon(int *guess,int *code,int cLength) {
    for (int i = 0; i < cLength; i++)
        if (guess[i] != code[i]) return false;
    return true;
}