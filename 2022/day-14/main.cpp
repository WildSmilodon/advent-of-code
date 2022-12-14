
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;

int const EMPTY = 0;
int const WALL = 1;
int const PARTICLE = 2;
int const SOURCE = 3;
string const znak[4] = {".", "#", "o","+"};

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



int main()
{

    string line;
    ifstream myfile; 

    myfile.open("input.txt");


    getline (myfile,line);
    vector<string> s;
    split(line,s,' ');
    int maxRow = stoi(s[0]);    
    int minCol = stoi(s[1]);
    int maxCol = stoi(s[2]);

    int nRow = maxRow + 1;
    int nCol = maxCol - minCol + 3;

    int sRow = 0;
    int sCol = 500 - minCol + 1;


    int map[nRow][nCol];
    for (int r = 0; r < nRow; r++) {
        for (int c = 0; c < nCol; c++) {
            map[r][c] = EMPTY;
        }
    }
    map[sRow][sCol] = SOURCE;

    while ( getline (myfile,line) ) {
        vector<string> s;
        split(line,s,'>');

        int startCol = -1;
        int startRow = -1;
        int endRow = -1;
        int endCol = -1;


        for (int i = 0; i<s.size(); i++) {
            vector<string> ss;
            split(s[i],ss,',');

            if (startCol == -1) {
                startCol = stoi(ss[0]) - minCol + 1;
                startRow = stoi(ss[1]);
            } else {            
                // consider a segment
                endCol = stoi(ss[0]) - minCol + 1;
                endRow = stoi(ss[1]);  

                if (startCol == endCol) {
                    if (startRow < endRow) {
                        for (int r = startRow; r <= endRow; r++) { map[r][startCol] = WALL; }
                    }
                    if (startRow > endRow) {
                        for (int r = endRow; r <= startRow; r++) { map[r][startCol] = WALL; }
                    }
                }
                if (startRow == endRow) {
                    if (startCol < endCol) {
                        for (int c = startCol; c <= endCol; c++) { map[startRow][c] = WALL; }
                    }
                    if (startCol > endCol) {
                        for (int c = endCol; c <= startCol; c++) { map[startRow][c] = WALL; }
                    }                    
                }

                // prepare for next segment
                startCol = endCol;
                startRow = endRow;   
            }
        }
    }

    myfile.close();

    bool theEnd = false;

    while (!theEnd) {

        bool stopped = false;
        int cRow = sRow;
        int cCol = sCol;

        while (!stopped && !theEnd) {
            bool moved = false;
            if (map[cRow + 1][cCol] == EMPTY) { cRow++; moved = true; }
            if (!moved && map[cRow + 1][cCol - 1] == EMPTY ) { cRow++; cCol--; moved = true; }
            if (!moved && map[cRow + 1][cCol + 1] == EMPTY ) { cRow++; cCol++; moved = true; }
            if (!moved) {
                stopped = true;
                map[cRow][cCol] = PARTICLE;
            }
            if (cRow == maxRow) {
                    theEnd = true;
            }

            if (cRow == sRow)  {
                    theEnd = true;
            }
        }

    }

    int nParticles = 0;

    for (int r = 0; r < nRow; r++) {
        for (int c = 0; c < nCol; c++) {
            if (map[r][c] == PARTICLE) { nParticles++; }
        }
    }

    cout << nParticles << endl;

}






