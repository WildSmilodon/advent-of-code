
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../util.h"

using namespace std;

class Pari {
public:
    int v;
    int symbolID;

    static bool compareByValue(const Pari& a, const Pari& b) {
        return a.symbolID < b.symbolID;
    }
};

class Tile {
public:
    Tile () { s=""; isSymbol = false; isNumber = false; hasSymbol = false; id = -1;}

    string s;
    bool isSymbol;
    bool isNumber;
    bool hasSymbol;
    int id;

    void set(int r, int c) {
        if ( s == "." ) { return; }
        if ( s == "0" ||  s == "1" ||  s == "2" ||  s == "3" ||  s == "4" ||  s == "5" ||  s == "6" ||  s == "7" ||  s == "8" ||  s == "9" ) {
            isNumber = true;
        }
        if (s == "*") { isSymbol = true; }
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
            tiles[row][col].set(row,col);
        }
        row++;  
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            
            if (tiles[row][col].isSymbol) {
                if ( onMap(row + 1,col - 1,n) ) { tiles[row + 1][col - 1].hasSymbol = true; tiles[row + 1][col - 1].id = col + n * row; }
                if ( onMap(row + 1,col    ,n) ) { tiles[row + 1][col    ].hasSymbol = true; tiles[row + 1][col    ].id = col + n * row; }
                if ( onMap(row + 1,col + 1,n) ) { tiles[row + 1][col + 1].hasSymbol = true; tiles[row + 1][col + 1].id = col + n * row; }
                if ( onMap(row - 1,col - 1,n) ) { tiles[row - 1][col - 1].hasSymbol = true; tiles[row - 1][col - 1].id = col + n * row; }
                if ( onMap(row - 1,col    ,n) ) { tiles[row - 1][col    ].hasSymbol = true; tiles[row - 1][col    ].id = col + n * row; }
                if ( onMap(row - 1,col + 1,n) ) { tiles[row - 1][col + 1].hasSymbol = true; tiles[row - 1][col + 1].id = col + n * row; }
                if ( onMap(row    ,col - 1,n) ) { tiles[row    ][col - 1].hasSymbol = true; tiles[row    ][col - 1].id = col + n * row; }
                if ( onMap(row    ,col + 1,n) ) { tiles[row    ][col + 1].hasSymbol = true; tiles[row    ][col + 1].id = col + n * row; }
            }
        }
    }

    vector<Pari> pari;
    pari.clear();
    string sn = "";
    bool composing = false;
    bool hasSymbol = false;
    int symbolID = -1;

    for (int row = 0; row < n; row++) {
        if (composing) {
            composing = false;
            int val = stoi(sn);
            if (hasSymbol) { Pari par; par.v=val; par.symbolID = symbolID; pari.push_back(par); }
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
                if (tiles[row][col].hasSymbol) { hasSymbol = true; symbolID = tiles[row][col].id;  }
            } else {
                if (composing) {
                    composing = false;
                    int val = stoi(sn);
                    if (hasSymbol) { Pari par; par.v=val; par.symbolID = symbolID; pari.push_back(par); }
                    hasSymbol = false;
                }
            }
        }
    }

    sort(pari.begin(), pari.end(), Pari::compareByValue);


   // for (Pari p : pari) {
   //     cout << p.symbolID << " " << p.v << endl;
   // }

    long long total = 0;
    //for (int i = 0; i<pari.size()-1; i++) {
    //    if (pari[i].symbolID == pari[i+1].symbolID) {
    //        total = total + pari[i].v * pari[i+1].v;
    //    }
    //}

    
    int curID = -1;
    int curVAL = 0;
    int curN = 0;
    for (int i = 0; i<pari.size(); i++) {
        if (pari[i].symbolID == curID) {
            curVAL = curVAL * pari[i].v;
            curN++;
        } else {
          //  cerr << " s" << i << " " << curN << " " << curVAL << endl;
            if (curN == 2) { total = total + curVAL; }
            curN = 1;
            curVAL = pari[i].v;
            curID = pari[i].symbolID;
        }
        cerr << pari[i].symbolID << " " << pari[i].v << " " << curVAL << " "  << total << endl;
    }
    if (curN == 2) { total = total + curVAL; }
     

    cout << total << endl;
}
