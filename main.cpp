#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

int board[4][4];
int dirLine[]= {1, 0, -1, 0};
int dirColumn[]= {0, 1, 0, -1};

pair<int, int> generateUnoccupiedPosition()
{
    int occupied = 1, line, column;
    while (occupied)
    {
        line = rand() % 4;
        column = rand() % 4;
        if(board[line][column] == 0)
            occupied=0;
    }
    return make_pair(line,column);
}

void addPiece () {
    pair<int, int> pos = generateUnoccupiedPosition();
    board[pos.first][pos.second] = 2;
}

void newGame()
{
    for(int i = 0; i < 4; ++i)
        for(int j =0; j < 4; ++j)
            board[i][j]=0;
    addPiece();
}

void printMenu ()
{
    system("cls");
    for(int i = 0; i < 4; ++i)
    {
        for(int j= 0; j < 4; ++j)
            if(board[i][j] == 0)
                cout << setw(4) << ".";
            else
                cout << setw(4) << board[i][j];
        cout << '\n';
    }
    cout << "n: new game, u: up, d: down, r: right, l: left, q: quit\n";
}

bool canDoMove(int line, int column, int nextLine, int nextColumn){
    if(nextLine < 0 || nextLine >=4 || nextColumn < 0 || nextColumn >=4 || board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0)
        return false;
    return true;
}

void applyMove (int direction)
{
    /// u: up = 2, d: down = 0, r: right = 1, l: left = 3, q: quit\n
    int startLine = 0, startColumn = 0, stepLine = 1, stepColumn = 1;
    if(direction == 0){
        startLine = 3;
        stepLine = -1;
    }
    if(direction == 1){
        startColumn = 3;
        stepColumn = -1;
    }
    int possible,canAddPiece =0;
    do{
            possible = 0;
    for(int i = startLine; i >= 0 && i < 4; i += stepLine)
        for(int j = startColumn; j >= 0 && j < 4; j += stepColumn){
            int nextI= i + dirLine[direction], nextJ = j + dirColumn[direction];
            if(board[i][j] && canDoMove(i, j, nextI, nextJ))
            {
                board[nextI][nextJ] += board[i][j];
                board[i][j] = 0;
                possible = canAddPiece = 1;
            }
        }
    }
    while(possible);

    if(canAddPiece)
        addPiece();


}
int main()
{
    srand(time(0));
    char commandToDir[128];
    commandToDir['d'] = 0;
    commandToDir['r'] = 1;
    commandToDir['u'] = 2;
    commandToDir['l'] = 3;
    newGame();
    while (true)
    {
        printMenu();
        char command;
        cin >> command;
        if (command == 'n')
            newGame();
        else if(command == 'q')
            break;
        else {
            int currentDirection = commandToDir[command];
            applyMove(currentDirection);
        }
    }
}
