#include <iostream>
#include "grid.h"

using namespace std;

//0 is the real player
//1 is CPU
int main()
{
    Grid* g = new Grid();
    g->draw();
    bool dropping = true;
    int play = 0;
    while (dropping)
    {
        int col;
        cout << "choose column (0 to exit)" << endl;
        cin >> col;

        if (col == 0)
        {
            dropping = false;
            break;
        }

        char tok;
        //cout << "choose token" << endl;
        //cin >> tok;
        if(play == 1)
            tok = 'x';
        else
            tok = 'o';

        g->drop(col, tok, play);
        g->draw();
        cout << g->checkVertical(0, play);

        if(play == 0)
            play = 1;
        else
            play = 0;
    }
    delete[] g;
    g = nullptr;




    return 0;
}
