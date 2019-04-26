#include "token.h"

Token::Token()
{
    x = 0;
    y = 0;
    filled = false;
}

void Token::setFilled(int r, int g, int b)
{
    //col.set(r, g, b);
    filled = true;

}


