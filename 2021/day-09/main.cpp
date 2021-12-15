
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Position {
public:

    int r;
    int c;

    Position();
    Position(int r_, int c_){
        r = r_;
        c = c_;
    }
};

bool toAdd(Position candidate, vector<Position> b) {
    bool res = true;

    for (Position p : b) {
        if (candidate.r == p.r & candidate.c == p.c) { res = false; }
    }

    return res;
}


int main()
{

    int nRow = 100; //5;
    int nCol = 100; //10;
    int map[nRow][nCol];

    for (int i = 0; i<nRow; i++) {
        string row;
        cin >> row; cin.ignore();
        for (int j = 0; j<nCol; j++) {
            map[i][j] = stoi(row.substr(j,1));
        }
    }

    vector<int> sizes;
    int n  = 0;
    for (int r=0; r<nRow; r++) {
        for (int c=0; c<nCol; c++) {
            // left
            bool found = true;
            if (c-1 >   -1) { if ( map[r][c-1] <= map[r][c] ) { found = false; } }
            if (c+1 < nCol) { if ( map[r][c+1] <= map[r][c] ) { found = false; } }
            if (r-1 >   -1) { if ( map[r-1][c] <= map[r][c] ) { found = false; } }
            if (r+1 < nRow) { if ( map[r+1][c] <= map[r][c] ) { found = false; } }

            if (found) {
 

                vector<Position> basin;
                basin.push_back(Position(r,c));

                int index = 0;

                while (index < basin.size()) {

                    int row = basin[index].r;
                    int col = basin[index].c;

                    if (col-1 >   -1) { if ( map[row][col-1] > map[row][col] & map[row][col-1] < 9 ) { Position p(row,col-1);  if (toAdd(p,basin)) {basin.push_back(p);} } }
                    if (col+1 < nCol) { if ( map[row][col+1] > map[row][col] & map[row][col+1] < 9 ) { Position p(row,col+1);  if (toAdd(p,basin)) {basin.push_back(p);} } }
                    if (row-1 >   -1) { if ( map[row-1][col] > map[row][col] & map[row-1][col] < 9 ) { Position p(row-1,col);  if (toAdd(p,basin)) {basin.push_back(p);} } }
                    if (row+1 < nRow) { if ( map[row+1][col] > map[row][col] & map[row+1][col] < 9 ) { Position p(row+1,col);  if (toAdd(p,basin)) {basin.push_back(p);} } }

                    index++;
                }

                sizes.push_back(basin.size());

                for (Position p : basin) {
                    cerr << p.r << " brc " << p.c << " " << map[p.r][p.c] << endl;
                }

                cerr << r << " " << c << " " << basin.size() << endl; 
                //n = n + (1 +  map[r][c]); 
            }
        }
    }

    // Perform the sort
    std::sort(sizes.begin(), sizes.end(), greater<int>() );
 
    for (int i : sizes) {
        cerr << i << endl;
    }

    cerr << sizes[0] * sizes[1] * sizes[2] << endl;

}
