#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// const----------- //
const int aRandom[] = {2, 2, 2, 2, 2, 2, 2, 4}; // In order to make the times random 2 more than random 4
struct Game
{
    int Board[4][4]; // A square board from 1 to 4
    int TempBoard[4][4]; // Store the board before doing move
    int PrevBoard[4][4]; // Store the previous board in order to use undo move
    long long score;
    long long tmpscore;
    long long prevscore;
    vector <int> DoMove; // Step by step for each column or row
};

void RandBoard(Game& game);
void createGame(Game& game);
void drawGame(Game& game);
void drawTempBoard(Game& game);
bool GameOver(Game& game);
bool checkMove(Game& game);
void Up(Game& game);
void Down(Game& game);
void Right(Game& game);
void Left(Game& game);
void StoreBoard(Game& game);
void SavePreBoard(Game& game);
void ClearScreen();

int main()
{
    Game game;
    srand(time(NULL));


    char n;
    createGame(game);
    drawGame(game);

    while (cin >> n){
    StoreBoard(game);

    //drawTempBoard(game);
    switch(n){
        case 'w':{
            Up(game);
            break;
        }

        case 's': {
            Down(game);
            break;
        }
        case 'a': {
            Left(game);
            break;
        }
        case 'd': {
            Right(game);
            break;
        }

    }


    if (GameOver(game) == true) cout << "Game Over";
    if (checkMove(game) == 1) RandBoard(game);

    SavePreBoard(game);
    system("CLS");
    drawGame(game);
    }
    return 0;
}


void createGame(Game& game)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
    {
        game.Board[i][j] = 0;
        game.TempBoard[i][j] = 0;
        game.PrevBoard[i][j] = 0;
    }
    RandBoard(game);
}
void drawGame(Game& game)
{
    cout << " _____ _____ _____ _____";
    for (int i = 0; i <4; i++){
        cout << endl << "|     |     |     |     |" <<  endl;
        for (int j = 0; j <4; j++)
        {

            cout << "|  " << game.Board[i][j] << "  ";

        }
        cout << "|" << endl << "|_____|_____|_____|_____|";
    }

    cout << endl;
}
void drawTempBoard(Game& game)
{
    cout << " _____ _____ _____ _____";
    for (int i = 0; i <4; i++){
        cout << endl << "|     |     |     |     |" <<  endl;
        for (int j = 0; j <4; j++)
        {

            cout << "|  " << game.TempBoard[i][j] << "  ";

        }
        cout << "|" << endl << "|_____|_____|_____|_____|";
    }

    cout << endl;
}

void RandBoard(Game& game)
{
     int i = rand() % 4;
    int j = rand() % 4;

    while (game.Board[i][j] != 0)
    {
        i = rand() % 4;
        j = rand() % 4;
    }
    game.Board[i][j] = aRandom[rand() % 8];

}

bool checkMove(Game& game)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) if (game.Board[i][j] != game.TempBoard[i][j]) return 1;
    return 0;
}

bool GameOver(Game& game)
{
    // Check available space
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        if (game.Board[i][j] == 0) // If this box is empty then the board is not full yet, return GameOver = False
            return false;
    }
    // Check if there are two boxes have a same number when the board is full
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (game.Board[i][j] == game.Board[i - 1][j] || game.Board[i][j] == game.Board[i][j - 1])
                return false;
        }
    }

    return true;
}

void Up(Game& game){
    int canMove = true;
    bool canPlus[4][4];
    for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) canPlus[i][j] = true;
    while(canMove)
    {
        canMove = false;
        for (int i = 1; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (game.Board[i][j] == 0)  continue;

            if (game.Board[i - 1][j] == 0)
            {
                game.Board[i - 1][j] = game.Board[i][j];
                game.Board[i][j] = 0;
                canMove = true;
            }
            else
            if (game.Board[i - 1][j] == game.Board[i][j] && canPlus[i - 1][j] == true && canPlus[i][j] == true)
            {
                game.Board[i - 1][j] *= 2;
                game.score += game.Board[i - 1][j];
                game.Board[i][j] = 0;
                canPlus[i - 1][j] = false;
                canMove = true;
            }
        }
    }

}
void Down(Game& game){
    int canMove = true;
    bool canPlus[4][4];
    for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) canPlus[i][j] = true;
    while(canMove)
    {
        canMove = false;
        for (int i = 2; i >= 0; i--)
        for (int j = 0; j < 4; j++)
        {
            if (game.Board[i][j] == 0) continue;

            if (game.Board[i + 1][j] == 0)
            {
                game.Board[i + 1][j] = game.Board[i][j];
                game.Board[i][j] = 0;
                canMove = true;
            }
            else
            if (game.Board[i + 1][j] == game.Board[i][j] && canPlus[i + 1][j] == true && canPlus[i][j] == true)
            {
                game.Board[i + 1][j] *= 2;
                game.score += game.Board[i + 1][j];
                game.Board[i][j] = 0;
                canPlus[i + 1][j] = false;
                canMove = true;
            }
        }
    }
}

void Right(Game& game){
    int canMove = true;
    bool canPlus[4][4];
    for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
            canPlus[i][j] = true;
    while(canMove)
    {
        canMove = false;
        for (int j = 2; j >= 0; j--)
        for (int i = 0; i < 4; i++)
        {
            if (game.Board[i][j] == 0)  continue;

            if (game.Board[i][j + 1] == 0)
            {
                game.Board[i][j + 1] = game.Board[i][j];
                game.Board[i][j] = 0;
                canMove = true;
            }
            else
            if (game.Board[i][j + 1] == game.Board[i][j] && canPlus[i][j + 1] == true && canPlus[i][j] == true)
            {
                game.Board[i][j + 1] *= 2;
                game.score += game.Board[i][j + 1];
                game.Board[i][j] = 0;
                canPlus[i][j + 1] = false;
                canMove = true;
            }
        }
    }
}

void Left(Game& game){
    int canMove = true;
    bool canPlus[4][4];
    for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
            canPlus[i][j] = true;
    while(canMove)
    {
        canMove = false;
        for (int j = 1; j < 4; j++)
        for (int i = 0; i < 4; i++)
        {
            if (game.Board[i][j] == 0)  continue;

            if (game.Board[i][j - 1] == 0)
            {
                game.Board[i][j - 1] = game.Board[i][j];
                game.Board[i][j] = 0;
                canMove = true;
            }
            else
            if (game.Board[i][j - 1] == game.Board[i][j] && canPlus[i][j - 1] == true && canPlus[i][j] == true)
            {
                game.Board[i][j - 1] *= 2;
                game.score += game.Board[i][j - 1];
                game.Board[i][j] = 0;
                canPlus[i][j - 1] = false;
                canMove = true;
            }
        }
    }
}

void StoreBoard(Game& game)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) game.TempBoard[i][j] = game.Board[i][j];
    game.tmpscore = game.score;
}

void SavePreBoard(Game& game)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) game.PrevBoard[i][j] = game.TempBoard[i][j];
    game.prevscore = game.tmpscore;
}


