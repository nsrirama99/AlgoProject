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
public:
    Grid();
    ~Grid();
    void draw();
    bool drop(int col, char x);
};


#endif // GRID_H
