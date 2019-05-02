#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

using namespace std;

class Token
{
    friend class Grid;
private:
    //screen location for GUI
    int x;
    int y;
    int player;
    //ofColor col;
    bool filled;
    char ascii;
public:
    Token();
    void setXY(int xL, int yL);
    void setFilled(int r, int g, int b);
    void draw();
    void setFilled(char x);
    void setPlayer(int x);
};

#endif // TOKEN_H
