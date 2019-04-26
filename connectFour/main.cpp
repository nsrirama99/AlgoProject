#include <iostream>
#include "grid.h"

using namespace std;

int main()
{
    Grid* g = new Grid();
    g->draw();
    bool dropping = true;
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
        cout << "choose token" << endl;
        cin >> tok;

        g->drop(col, tok);
        g->draw();
    }
    delete[] g;
    g = nullptr;




    return 0;
}
