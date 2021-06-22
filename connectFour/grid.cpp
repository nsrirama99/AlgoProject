#include "grid.h"
//prefer middle and bottom as ai when there is not a clear choice
Grid::Grid()
{
    srand(time(0));
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
            return;
        }
    }
}

int Grid::makeAIMove() {
    int col;
    if((int)rand()%4 == 3) {
        col = makeRandomMove();
    } else {
        col = makeIntelMove();
    }
    return col;
    //drop(col, 'x', 1);
}//makeAIMove

int Grid::makeIntelMove() {
    int scores[7][8];
    for(int j = 0; j < 7; j++) {
        if(!drop(j+1, 'x', 1))
            continue;
        if(won(j+1, 1)) {
            unDrop(j+1);
            return j+1;
        }
        scores[j][0] = setScore(j+1, 1);
        for(int k = 1; k < 8; k++) {
            if(!drop(k, 'o', 0))
                scores[j][k] = -1000;
            else {
                if(won(k, 0) && j != k+1) {
                    unDrop(j+1);
                    unDrop(k);
                    return k;
                }
                scores[j][k] = setScore(k, 0) + scores[j][0];
                unDrop(k);
            }
        }
        unDrop(j+1);
        scores[j][0] = scores[j][1];
        for(int k = 2; k < 8; k++) {
            if(scores[j][0] > scores[j][k])
                scores[j][0] = scores[j][k];
        }
    }
    int finalCol = 0;
    int max = scores[0][0];
    for(int j = 1; j < 7; j++) {
        if(scores[j][0] > max) {
            max = scores[j][0];
            finalCol = j;
        }
    }
    return finalCol + 1;
}

int Grid::makeRandomMove(){
    int a = 0; //i
    int b = 0; //p
    int c =0; //q
    bool notDrop = true;
    int arr[3];
    int arrX[3] = {100,100,100};
    int arrY[3] = {100,100,100};
    while(notDrop){
        a = (rand()%7 + 1);
        do{
            b = (rand()%7 + 1);
        }while(b==a);
        do{
             c = (rand()%7 + 1);
        }while(c==a || c==b);
        arr[0] = a;
        arr[1] = b;
        arr[2] = c;
        int row;
        for(int j =0; j<3;j++){
            if(drop(arr[j], 'x', 1)){
                notDrop = false;
                for (int i{}; i < 6; i++)
                {
                    if (toks[i][arr[j]-1].filled)
                    {
                        row = i;
                        break;
                    }
                }
                arrX[j] = arr[j]-1;
                arrY[j] = row;
                unDrop(arr[j]);
            }
        }
     }
     int positionScore = abs(8-arrX[0]+arrY[0]);
     int position = 0;
     if(abs(8-arrX[1] + arrY[1]) < positionScore){
         positionScore = abs(8-arrX[1] + arrY[1]);
         position = 1;
     }
     if(abs(8-arrX[2] + arrY[2]) < positionScore){
         positionScore = abs(8-arrX[2] + arrY[2]);
         position = 2;
     }
     return arr[position];
     //heuristic - manhattan distance
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
        score = 1000;
    } else {
        score = checkHorizontal(row, p) + checkVertical(col, p) + checkDiagonal(row, col, p);
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






