#include "grid.h"

Grid::Grid()
{
    height = 640;
    width = 740;
    //x = (ofGetWidth() - width) / 2;
	//y = (ofGetHeight() - height) / 2;
    
    //initialize tokens(grid) 6 by 7
	toks = new Token*[6];
	for (int i{}; i < 6; i++)
	{
		toks[i] = new Token[7]{};
		for (int j{}; j < 7; j++)
		{
			toks[i][j].setXY(x + 70 + j * 100, y + 70 + i*100);
		}
	}
}

Grid::~Grid()
{
	for (int i{}; i < 6; i++)
	{
		delete[] toks[i];
	}
	delete[] toks;
    toks = nullptr;
}

void Grid::draw()
{
    /*
	ofFill();
	ofSetColor(0, 0, 255);
	ofDrawRectangle(x, y, width, height);
	ofDrawRectangle(x - 20, y + height, width / 8, height / 10);
	ofDrawRectangle(x + width - width/8 + 20, y + height, width / 8, height / 10);
    */
    for (int i{1}; i < 8; i++)
    {
        cout << " " << i;
    }
    cout << endl;
	for (int i{}; i < 6; i++)
	{
		for (int j{}; j < 7; j++)
		{
            cout << '|';
			toks[i][j].draw();
		}
        cout << '|' << endl;
	}
}

bool Grid::drop(int col, char x)
{
    col--;
    for(int i{5}; i >=0; i--)
    {
        if (!toks[i][col].filled)
        {
            toks[i][col].setFilled(x);
            return true;
        }
    }
    cout << "full" << endl;
    return false;
}
