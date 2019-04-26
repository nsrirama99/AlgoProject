#ifndef TOKEN_H
#define TOKEN_H


class Token
{
private:
    //screen location for GUI
    int x;
    int y;
    //ofColor col;
    bool filled;
    char ascii;
public:
    Token();
    void setXY(int xL, int yL): x(xL), y(yL) {}
    void setFilled(int r, int g, int b);
    void draw();
    void setFilled(char x);
};

#endif // TOKEN_H
