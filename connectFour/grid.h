#ifndef GRID_H
#define GRID_H
#include "token.h"

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
};

#endif // GRID_H
