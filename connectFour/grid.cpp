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
    if(toks != nullptr) {
/*        for (int i{}; i < 6; i++)
        {
            if(toks[i] != nullptr)
                delete[] toks[i];
        }*/
        delete[] toks;
        toks = nullptr;
    }
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

bool Grid::drop(int col, char x, int p)
{
    col--;
    for(int i{5}; i >=0; i--)
    {
        if (!toks[i][col].filled)
        {
            toks[i][col].setFilled(x);
            toks[i][col].setPlayer(p);
            return true;
        }
    }
    if(p == 0)
        cout << "full" << endl;
    return false;
}

void Grid::unDrop(int col) {
    col--;
    for(int i{}; i < 6; i++) {
        if(toks[i][col].filled) {
            toks[i][col].filled = false;
            toks[i][col].ascii = ' ';
            toks[i][col].setPlayer(-1);
        }
    }
}

void Grid::setScore(int p) {
    int scor = 0;
    int inRow = 1;
    for(int j = 0; j < 6; j++){
                checkHorizontal(j, p);
    } //end loop through rows
} //end set score

int Grid::checkHorizontal(int row, int p) {
        int tinRow = 0;
        int tinRowt = 0;
        int lastPlayerPos = 0;
        for(int a = 0; a < 6; a++) {
            if(toks[row][a].player == p && (toks[row][a+1].player == p || !toks[row][a+1].filled)) {
                if(!toks[row][a+1].filled)
                    tinRow++;
                else {
                    tinRow++;
                    lastPlayerPos = a+1;
                }
            } else if(toks[row][a].filled) {//if space is held by opponent
                if(tinRow > tinRowt) {
                    tinRowt = tinRow;
                    tinRow = 0;
                }
            }
            if(a - lastPlayerPos > 3) {
                if(tinRow > tinRowt) {
                    tinRowt = tinRow;
                    tinRow = 0;
                }
            }
        }
        if(toks[row][6].player == p)
            tinRow++;

        if(tinRow > tinRowt) {
            tinRowt = tinRow;
            tinRow = 0;
        }
        return tinRowt;
} //end checkHorizontal

int Grid::checkVertical(int col, int p) {
    int tinRow = 0;
    int tinRowt = 0;
    int lastPlayerPos = 0;
    for(int a = 5; a > 0; a--) {
        if(toks[a][col].player == p && (toks[a-1][col].player == p || !toks[a-1][col].filled)) {
            if(!toks[a-1][col].filled)
                tinRow++;
            else {
                tinRow++;
                lastPlayerPos = a-1;
            }
        } else if(toks[a][col].filled) {//if space is held by opponent
            if(tinRow > tinRowt) {
                tinRowt = tinRow;
                tinRow = 0;
            }
        }
        if(lastPlayerPos - a> 3) {
            if(tinRow > tinRowt) {
                tinRowt = tinRow;
                tinRow = 0;
            }
        }
    }
    if(toks[0][col].player == p)
        tinRow++;

    if(tinRow > tinRowt) {
        tinRowt = tinRow;
        tinRow = 0;
    }
    return tinRowt;
}

int Grid::getScore() { return score; }
