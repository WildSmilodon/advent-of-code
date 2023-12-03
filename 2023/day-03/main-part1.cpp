
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../util.h"

using namespace std;

class Tile {
public:
    Tile () { s=""; isSymbol = false; isNumber = false; hasSymbol = false; }

    string s;
    bool isSymbol;
    bool isNumber;
    bool hasSymbol;

    void set() {
        if ( s == "." ) { return; }
        if ( s == "0" ||  s == "1" ||  s == "2" ||  s == "3" ||  s == "4" ||  s == "5" ||  s == "6" ||  s == "7" ||  s == "8" ||  s == "9" ) {
            isNumber = true;
        }
        if ( !isNumber) { isSymbol = true; }
    }

};

bool onMap(int row, int col, int n) {
    bool r = true;

    if ( row  < 0 ) { r = false; }
    if ( row  >= n ) { r = false; }
    if ( col  < 0 ) { r = false; }
    if ( col  >= n ) { r = false; }

    return r;
}

int main()
{
    string line;
    int n = 10;
    n = 140;
    Tile tiles[n][n];


    int row = 0;
    while (getline(cin, line)) {
        // PART 1
        for (int col = 0; col < n; col++) {
            tiles[row][col].s = line.substr(col,1);
            tiles[row][col].set();
        }
        row++;  
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            
            if (tiles[row][col].isSymbol) {
                if ( onMap(row + 1,col - 1,n) ) { tiles[row + 1][col - 1].hasSymbol = true; }
                if ( onMap(row + 1,col    ,n) ) { tiles[row + 1][col    ].hasSymbol = true; }
                if ( onMap(row + 1,col + 1,n) ) { tiles[row + 1][col + 1].hasSymbol = true; }
                if ( onMap(row - 1,col - 1,n) ) { tiles[row - 1][col - 1].hasSymbol = true; }
                if ( onMap(row - 1,col    ,n) ) { tiles[row - 1][col    ].hasSymbol = true; }
                if ( onMap(row - 1,col + 1,n) ) { tiles[row - 1][col + 1].hasSymbol = true; }
                if ( onMap(row    ,col - 1,n) ) { tiles[row    ][col - 1].hasSymbol = true; }
                if ( onMap(row    ,col + 1,n) ) { tiles[row    ][col + 1].hasSymbol = true; }
            }
        }
    }

    string sn = "";
    bool composing = false;
    bool hasSymbol = false;
    int total = 0;
    for (int row = 0; row < n; row++) {
        if (composing) {
            composing = false;
            int val = stoi(sn);
            if (hasSymbol) { total = total + val;}
            hasSymbol = false;
        }
        for (int col = 0; col < n; col++) {

            if (tiles[row][col].isNumber) {
                if (!composing) {
                    composing = true;
                    sn = tiles[row][col].s;
                } else {
                    sn = sn + tiles[row][col].s;
                }
                if (tiles[row][col].hasSymbol) { hasSymbol = true; }
            } else {
                if (composing) {
                    composing = false;
                    int val = stoi(sn);
                    if (hasSymbol) { total = total + val;}
                    hasSymbol = false;
                }
            }
        }
    }
    cout << total << endl;
}
