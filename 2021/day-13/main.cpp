
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


class Dot  {

public:
    int row;
    int col;

    Dot(int r, int c) {
        row = r;
        col = c;
    }

    Dot () {}

};

class Paper {
public:
    vector<Dot> dots;

    Paper() {
        dots.clear();
    }


void foldR(int foldRow) {
    
    vector<Dot> copy;
    
    for (Dot d : dots) {
        Dot newDot;
        if (d.row < foldRow) {
            newDot = Dot(d.row,d.col);
        } else {
            newDot = Dot(foldRow - (d.row-foldRow),d.col);
        }

        bool found = false;
        for (Dot dd : copy) {
            if (dd.row == newDot.row & dd.col == newDot.col ) {
                found = true;
            }
        }

        if (!found) {copy.push_back(newDot);}

    }

    dots = copy;
}

void foldC(int foldCol) {
    
    vector<Dot> copy;

    copy.clear();
    
    for (Dot d : dots) {
        Dot newDot;

        if (d.col < foldCol) {
            newDot = Dot(d.row,d.col);
        } else {
            newDot = Dot(d.row,foldCol - (d.col-foldCol));
        }

        bool found = false;
        for (Dot dd : copy) {
            if (dd.row == newDot.row & dd.col == newDot.col ) {
                found = true;
            }
        }

        if (!found) {copy.push_back(newDot);}

    }

    dots = copy;
}

bool exists(int r, int c) {
    bool found = false;
    for (Dot d : dots) {
        if (d.row == r & d.col == c) {
            found = true;
        }
    }
    return found;
}

void print() {
    int maxR=-1;
    int maxC=-1;

    for (Dot d : dots) {
        if (d.row > maxR)  {maxR = d.row; }
        if (d.col > maxC) { maxC = d.col; }
    }
    //cerr << maxR << " " << maxC << "   " << dots.size() << endl;

    for (int r = 0; r<maxR+1; r++) {
        for (int c = 0; c<maxC+1; c++) {
            if (exists(r,c)) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

};



int main()
{

    int nLines = 1022; //18;
    Paper paper;

    for (int i = 0; i<nLines; i++) {
        int r;
        int c;
        cin >> c >> r;  cin.ignore();
        paper.dots.push_back(Dot(r,c));
    }


 //  cerr << paper.dots.size() << endl;
 //  paper.print();
 //  paper.foldR(7);
 //  cerr << paper.dots.size() << endl;
 //  paper.print();
 //  paper.foldC(5);
 //  cerr << paper.dots.size() << endl;
 //  paper.print();



    cerr << paper.dots.size() << endl;
    paper.foldC(655);
    cerr << paper.dots.size() << endl;
    paper.foldR(447);
    cerr << paper.dots.size() << endl;
    paper.foldC(327);
    cerr << paper.dots.size() << endl;
    paper.foldR(223);
    cerr << paper.dots.size() << endl;
    paper.foldC(163);
    cerr << paper.dots.size() << endl;
    paper.foldR(111);
    cerr << paper.dots.size() << endl;
    paper.foldC(81);
    cerr << paper.dots.size() << endl;
    paper.foldR(55);
    cerr << paper.dots.size() << endl;
    paper.foldC(40);
    cerr << paper.dots.size() << endl;
    paper.foldR(27);
    cerr << paper.dots.size() << endl;
    paper.foldR(13);
    cerr << paper.dots.size() << endl;
    paper.foldR(6);

    cerr << paper.dots.size() << endl;
    paper.print();


}
