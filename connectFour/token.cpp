#include "token.h"

Token::Token()
{
    x = 0;
    y = 0;
    filled = false;
    ascii = ' ';
}

void Token::setXY(int xL, int yL)
{
    x = xL;
    y = yL;
}

void Token::setFilled(int r, int g, int b)
{
    //col.set(r, g, b);
    filled = true;
}

void Token::setFilled(char x)
{
    filled = true;
    ascii = x;
}

void Token::draw()
{
	if (filled)
	{
        cout << ascii;
		/*ofFill();
		ofSetColor(col);
		ofDrawCircle(x, y, 45);

		ofNoFill();
		ofSetColor(100);
		ofDrawCircle(x, y, 38);*/
	}
	else
	{
        cout << '_';
		/*ofFill();
		ofSetColor(200);
		ofDrawCircle(x, y, 45);*/
	}
}


