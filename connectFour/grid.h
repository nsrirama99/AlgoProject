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
    bool wonHorizontal(int row, int p);
    bool wonVertical(int col, int p);
    bool wonDiagonal(int col, int row, int p);
public:
    Grid();
    ~Grid();
    void draw();
    bool drop(int col, char x, int p);
    void setScore(int col, int p);
    int getScore();
    int checkHorizontal(int row, int p);
    int checkVertical(int col, int p);
    int checkDiagonal(int row, int col, int p);
    void unDrop(int col);
    bool won(int col, int p);

};


#endif // GRID_H
