
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

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

class Tile {
public:
    int row;
    int col;
    vector<int> links;
    int height;
    int dist;
};

int main()
{

    string line;
    ifstream myfile; 

    myfile.open("input.txt");

    getline (myfile,line);
    vector<string> s;
    split(line,s,' ');
    int nRow = stoi(s[0]);
    int nCol = stoi(s[1]);

    int map[nRow][nCol];
    int start;
    vector<int> starts;
    int end;
    vector<Tile> grid;

    for (int r = 0; r<nRow; r++) {
        getline (myfile,line);
        for (int c = 0; c<nCol; c++) {
            char ch = line.at(c);
            if (ch == 'S') {
                ch = 'a';
                start = r * nCol + c;
            }
            if (ch == 'E') {
                ch = 'z';
                end = r * nCol + c;
            }
            if (ch == 'a') { starts.push_back(r * nCol + c); }
            map[r][c] = int(ch);
            Tile t;
            t.row = r;
            t.col = c;
            t.dist = 1000000;
            t.height = map[r][c];
            t.links.clear();
            grid.push_back(t);            
        }        
    }

    myfile.close();

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            bool neib = false;
            if (grid[j].row == grid[i].row + 1 && grid[j].col == grid[i].col && grid[j].height - grid[i].height <= 1 ) { neib = true; }
            if (grid[j].row == grid[i].row - 1 && grid[j].col == grid[i].col && grid[j].height - grid[i].height <= 1 ) { neib = true; }
            if (grid[j].row == grid[i].row && grid[j].col == grid[i].col + 1 && grid[j].height - grid[i].height <= 1 ) { neib = true; }
            if (grid[j].row == grid[i].row && grid[j].col == grid[i].col - 1 && grid[j].height - grid[i].height <= 1 ) { neib = true; }
            if (neib) { grid[i].links.push_back(j);}
        }
    }

    vector<int> q;
    q.push_back(start);
    grid[start].dist = 0;
    int current = 0;

    while (current < q.size() ) {
        int node = q[current];
        current++;

        if (node == end) {
            break;
        }

        for (int neib : grid[node].links) {
            if (grid[neib].dist > grid[node].dist + 1) { grid[neib].dist = grid[node].dist + 1; q.push_back(neib); }           
        }
    }

    cerr << grid[end].dist << endl;

    int minD = 1000000;
    for (int s : starts) {
        q.clear();
        q.push_back(s);

        for (Tile& t : grid) {
            t.dist = 100000;
        }
        grid[s].dist = 0;
        current = 0;

        while (current < q.size() ) {
            int node = q[current];
            current++;

            if (node == end) { break; }

            for (int neib : grid[node].links) {
                if (grid[neib].dist > grid[node].dist + 1) { grid[neib].dist = grid[node].dist + 1; q.push_back(neib); }           
            }
        }
        if (grid[end].dist < minD) {minD = grid[end].dist;}
    }
    cerr << minD << endl;




}






