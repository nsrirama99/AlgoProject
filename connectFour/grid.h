#ifndef GRID_H
#define GRID_H
#include "token.h"
#include <iostream>

using namespace std;

class Grid
{
private:
    Token** toks;

    //gui stuff
    int height;
    int width;
    int x;
    int y;
    int score;
public:
    Grid();
    ~Grid();
    void draw();
    bool drop(int col, char x, int p);
    void setScore(int p);
    int getScore();
    int checkHorizontal(int row, int p);
    int checkVertical(int col, int p);
    int checkDiagonal(int row, int col);
    void unDrop(int col);
};


#endif // GRID_H
