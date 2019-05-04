#include "grid.h"
//prefer middle and bottom as ai when there is not a clear choice
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

int Grid::setScore(int col, int p) {
    col--;
    int row{};
    for (int i{}; i < 6; i++)
    {
        if (toks[i][col].filled)
        {
            row = i;
            break;
        }
    }

    if(won(col, p)) {
        score = 100;
    } else {
        score = max(max(checkHorizontal(row, p), checkVertical(col, p)), checkDiagonal(row, col, p));
    }

    if(p == 0)
        score*=-1;
    return score;
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

int Grid::checkDiagonal(int row, int col, int p)
{
    int tinRow{};
    int tinRowt{};
    int lastPlayerDist{4};
    //check top left to bottom right
    if ((row > 2 && col < 3) || (row < 3 && col > 3))
    {
        //bad
        goto rtol;
    }
    else
    {
        int trow = row-6;
        int tcol = col-6;
        while (trow < 0 || tcol < 0)
        {
            trow++;
            tcol++;
        }
        while (trow < 6 && tcol < 7)
        {
            if (toks[trow][tcol].player == p)
            {
                tinRowt++;
                lastPlayerDist = 1;
            }
            else if (!toks[trow][tcol].filled)
            {
                lastPlayerDist++;
                if (lastPlayerDist > 3)
                {
                    if (tinRowt > tinRow) {tinRow = tinRowt;}
                    tinRowt = 0;
                }
            }
            else
            {
                if (tinRowt > tinRow) {tinRow = tinRowt;}
                tinRowt = 0;
            }
            trow++;
            tcol++;
        }
        if (tinRowt > tinRow) {tinRow = tinRowt;}
        tinRowt = 0;
    }
rtol: //check top right to bottom left
    if ((row < 3 && col < 3) || (row > 2 && col > 3))
    {
        return false;
    }
    else
    {
        int trow = row-6;
        int tcol = col+6;
        while (trow < 0 || tcol > 6)
        {
            trow++;
            tcol--;
        }
        while (trow < 6 && tcol >= 0)
        {
            if (toks[trow][tcol].player == p)
            {
                tinRowt++;
                lastPlayerDist = 1;
            }
            else if (!toks[trow][tcol].filled)
            {
                lastPlayerDist++;
                if (lastPlayerDist > 3)
                {
                    if (tinRowt > tinRow) {tinRow = tinRowt;}
                    tinRowt = 0;
                }
            }
            else
            {
                if (tinRowt > tinRow) {tinRow = tinRowt;}
                tinRowt = 0;
            }
            trow++;
            tcol--;
        }
        if (tinRowt > tinRow) {tinRow = tinRowt;}
        tinRowt = 0;
    }
    return tinRow;
}

int Grid::getScore() { return score; }

bool Grid::won(int col, int p)
{
    col--;
    int row{};
    for (int i{}; i < 6; i++)
    {
        if (toks[i][col].filled)
        {
            row = i;
            break;
        }
    }

    if (wonHorizontal(row, p))
        return true;
    else if (wonVertical(col, p))
        return true;
    else
        return wonDiagonal(col, row, p);
}

bool Grid::wonHorizontal(int row, int p)
{
    for (int i{}; i < 4; i++)
    {
        if (toks[row][i].player == p && toks[row][i+1].player == p && toks[row][i+2].player == p && toks[row][i+3].player == p)
            return true;
    }
    return false;
}

bool Grid::wonVertical(int col, int p)
{
    for (int i{}; i < 3; i++)
    {
        if (toks[i][col].player == p && toks[i+1][col].player == p && toks[i+2][col].player == p && toks[i+3][col].player == p)
            return true;
    }
    return false;
}

bool Grid::wonDiagonal(int col, int row, int p)
{
    //check top left to bottom right
    if ((row > 2 && col < 3) || (row < 3 && col > 3))
    {
        //bad
        goto rtol;
    }
    else
    {
        int trow = row-3;
        int tcol = col-3;
        while (trow < 0 || tcol < 0)
        {
            trow++;
            tcol++;
        }
        while (trow + 3 < 6 && tcol + 3 < 7)
        {
            if (toks[trow][tcol].player == p && toks[trow + 1][tcol + 1].player == p && toks[trow+2][tcol+2].player == p && toks[trow + 3][tcol + 3].player == p)
                return true;
            trow++;
            tcol++;
        }
    }
rtol: //check top right to bottom left
    if ((row < 3 && col < 3) || (row > 2 && col > 3))
    {
        return false;
    }
    else
    {
        int trow = row-3;
        int tcol = col+3;
        while (trow < 0 || tcol > 6)
        {
            trow++;
            tcol--;
        }
        while (trow + 3 < 6 && tcol - 3 >= 0)
        {
            if (toks[trow][tcol].player == p && toks[trow + 1][tcol - 1].player == p && toks[trow+2][tcol-2].player == p && toks[trow + 3][tcol - 3].player == p)
                return true;
            trow++;
            tcol--;
        }
    }
    return false;
}






