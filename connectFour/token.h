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
    //ofColor col;
    bool filled;
    char ascii;
public:
    Token();
    void setXY(int xL, int yL);
    void setFilled(int r, int g, int b);
    void draw();
    void setFilled(char x);
};

#endif // TOKEN_H
