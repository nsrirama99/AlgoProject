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
public:
    Token();
    void setXY(int xL, int yL): x(xL), y(yL) {}
    void setFilled(int r, int g, int b);
    void draw();
};

#endif // TOKEN_H
