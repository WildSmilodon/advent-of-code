
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}


class Board {
    public:

    int values[5][5];
    bool marked[5][5];
    bool hasWon;

    void init() {
        hasWon = false;
        for (int r = 0; r<5; r++) {
            for (int c = 0; c<5; c++) {
                marked[r][c]=false;
            }
        }
    }


    void read() {
        for (int r = 0; r<5; r++) {
            for (int c = 0; c<5; c++) {
                cin >> values[r][c]; cin.ignore();
            }
        }
    }

    void print() {
        for (int r = 0; r<5; r++) {
            for (int c = 0; c<5; c++) {
                if (marked[r][c]) {
                    cerr << values[r][c] << "x ";
                } else {
                    cerr << values[r][c] << " ";
                }
            }
            cerr << endl;
        }
    }

    bool win() {
        bool res = false;

        for (int r = 0; r<5; r++) {
            bool rc = marked[r][0] & marked[r][1] & marked[r][2] & marked[r][3] & marked[r][4];
            if (rc) { res = true; } 
        }
        
        for (int c = 0; c<5; c++) {
            bool rc = marked[0][c] & marked[1][c] & marked[2][c] & marked[3][c] & marked[4][c];
            if (rc) { res = true; } 
        }

        return res;

    }

    int sumAll() {
        int s = 0;
         for (int r = 0; r<5; r++) {
            for (int c = 0; c<5; c++) {
                s = s + values[r][c];
            }
        }         
        return s;
    }


    int sumUnmarked() {
        int s = 0;
         for (int r = 0; r<5; r++) {
            for (int c = 0; c<5; c++) {
                if (!marked[r][c]) {s = s + values[r][c];}
            }
        }         
        return s;
    }

    void markValue(int v) {
        for (int r = 0; r<5; r++) {
            for (int c = 0; c<5; c++) {
                if (v == values[r][c]) {  marked[r][c] = true; }
            }
        }        
    }
};

int main()
{

    int nBoards = 100;
    vector<Board> boards;

    vector<string> numbersDrawnS;
    vector<int> numbersDrawn;
    string s;
    cin >> s; cin.ignore();
    split( s, numbersDrawnS, ',' );

    for (string s : numbersDrawnS) {
       int i = stoi(s);
       numbersDrawn.push_back(i);
      // cerr << i << endl;
    }

    for (int i = 0; i<nBoards; i++) {
        Board b;
        b.init();
        b.read();
        boards.push_back(b);
    }


    // Part I

//    bool done = false;
//    for (int  v : numbersDrawn) {
//        for (Board &b : boards) {
//            b.markValue(v);
//            
//            if (b.win()) {
//                cerr << "win  = " << v << " sum=" << b.sumUnmarked() << " sol= " << v*b.sumUnmarked() << endl;
//                b.print();
//                done = true;
//                break;
//            }
//        }
//        if (done) { break;}
//    }


    // Part II


    int nWin = 0;
    for (int  v : numbersDrawn) {
        for (Board &b : boards) {
            if (b.hasWon == false) {
                b.markValue(v);
                if (b.win()) {
                    b.hasWon = true;
                    nWin++;
                    if (nWin == nBoards) {
                        cerr << "last win  = " << v << " sum=" << b.sumUnmarked() << " sol= " << v*b.sumUnmarked() << endl;
                    }
                }
            }   
        }
    }



}
