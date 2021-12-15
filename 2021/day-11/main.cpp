
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

const int rMin = 0;
const int rMax = 9;
const int cMin = 0;
const int cMax = 9;


int getId(int r, int c) {
    return r*(rMax+1)+c;
}

class Octopus {

public:
    int energy;
    bool hasFlashed;
    int row;
    int col;
    int id;
    vector<int> neighbors;

    Octopus() {
        energy = 0;
        hasFlashed = false;
        row = 0;
        col  = 0;
        neighbors.clear();
    }

    Octopus(int e, int r, int c) {
        energy = e;
        row = r;
        col = c;
        hasFlashed = false;
        neighbors.clear();
        id = getId(r,c);
        setNeib();
    }

    void setNeib() {
        if ( row > rMin & row < rMax & col > cMin & col < cMax ){
            // Inside
            neighbors.push_back(getId(row-1,col-1));
            neighbors.push_back(getId(row-1,col  ));
            neighbors.push_back(getId(row-1,col+1));
            neighbors.push_back(getId(row  ,col-1));
            neighbors.push_back(getId(row  ,col+1));
            neighbors.push_back(getId(row+1,col-1));
            neighbors.push_back(getId(row+1,col  ));
            neighbors.push_back(getId(row+1,col+1));
        }
        if (row == rMin & col > cMin & col < cMax ) {
            // top row
            neighbors.push_back(getId(row  ,col-1));
            neighbors.push_back(getId(row  ,col+1));
            neighbors.push_back(getId(row+1,col-1));
            neighbors.push_back(getId(row+1,col  ));
            neighbors.push_back(getId(row+1,col+1));            
        }
        if (row == rMax & col > cMin & col < cMax ) {
            // bottom row
            neighbors.push_back(getId(row-1,col-1));
            neighbors.push_back(getId(row-1,col  ));
            neighbors.push_back(getId(row-1,col+1));
            neighbors.push_back(getId(row  ,col-1));
            neighbors.push_back(getId(row  ,col+1));
        }
        if ( row > rMin & row < rMax & col == cMin  ){
            // left col
            neighbors.push_back(getId(row-1,col  ));
            neighbors.push_back(getId(row-1,col+1));
            neighbors.push_back(getId(row  ,col+1));
            neighbors.push_back(getId(row+1,col  ));
            neighbors.push_back(getId(row+1,col+1));
        }   
        if ( row > rMin & row < rMax & col == cMax ) {
            // right col
            neighbors.push_back(getId(row-1,col-1));
            neighbors.push_back(getId(row-1,col  ));
            neighbors.push_back(getId(row  ,col-1));
            neighbors.push_back(getId(row+1,col-1));
            neighbors.push_back(getId(row+1,col  ));
        } 
        if ( row == rMin & col == cMin ){
            // corner
            neighbors.push_back(getId(row  ,col+1));
            neighbors.push_back(getId(row+1,col  ));
            neighbors.push_back(getId(row+1,col+1));
        }
        if ( row == rMax & col == cMin ){
            // corner
            neighbors.push_back(getId(row-1,col  ));
            neighbors.push_back(getId(row-1,col+1));
            neighbors.push_back(getId(row  ,col+1));
        }  
        if ( row == rMin & col == cMax ){
            // corner
            neighbors.push_back(getId(row  ,col-1));
            neighbors.push_back(getId(row+1,col-1));
            neighbors.push_back(getId(row+1,col  ));
        }  
        if ( row == rMax & col == cMax ){
            // corner
            neighbors.push_back(getId(row-1,col-1));
            neighbors.push_back(getId(row-1,col  ));
            neighbors.push_back(getId(row  ,col-1));

        }                                                      
    }
};

int main()
{

    int nLines = 10;
    int nSteps = 2000;
    vector<Octopus> octopuses;

    for (int r = 0; r<nLines; r++) {
        string line;
        cin >> line;  cin.ignore();
        cerr << line << endl;

        for (int c = 0; c<line.length(); c++) {
            int e = stoi(line.substr(c,1));
            Octopus o(e,r,c);
            cerr << o.row << o.col << " " << o.energy << " " << o.id << " "; 
            for (int n : o.neighbors) {
                cerr << n << " ";
            }
            cerr << endl;
            octopuses.push_back(o);
        }
    }

    int nFlash = 0;
    cout << "nSteps " << nSteps  << endl;
    for (int i=0; i<nSteps; i++) {
        //First, the energy level of each octopus increases by 1.
        for (Octopus &o : octopuses) {
            o.energy++;
        }
        //Then, any octopus with an energy level greater than 9 flashes. 
        //This increases the energy level of all adjacent octopuses by 1, 
        //including octopuses that are diagonally adjacent. 
        //If this causes an octopus to have an energy level greater than 9, 
        //it also flashes. This process continues as long as new octopuses keep 
        // having their energy level increased beyond 9. 
        //(An octopus can only flash at most once per step.)
        bool done = false;
        while (!done) {
            done = true;
            for (Octopus &o : octopuses) {
                if (o.energy > 9 & o.hasFlashed == false) {
                    o.hasFlashed = true;
                    done = false;
                    for (int i : o.neighbors) {
                        octopuses[i].energy++;
                    }
                }
            }
        }
        //Finally, any octopus that flashed during this step has its energy level set to 0, 
        // as it used all of its energy to flash.
        int tsFlash = 0;
        for (Octopus &o : octopuses) {
            if (o.hasFlashed) {
                o.energy = 0;
                o.hasFlashed = false;
                nFlash++;
                tsFlash++;
            }
           // cerr << o.row << o.col << " " << o.energy << endl;
        }
        if (tsFlash == 100) { cout << "tsFlash100 " << i+1 << endl; }
    }

    cout << "nFlash " << nFlash  << endl;
}
