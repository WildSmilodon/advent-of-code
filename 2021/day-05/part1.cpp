
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


class Position {
public:
    int x;
    int y;
    int n;

    Position() { n=0; }

    Position(int x_, int y_) {
        x = x_;
        y = y_;
        n = 0;
    }
};


class Line {
    public:

    Position start; 
    Position end;
    vector<Position> points;

    void findPoints() {
        points.clear();
        points.push_back(start);

        if (start.x == end.x) {
            if (end.y > start.y) {
                for (int i=start.y + 1; i<end.y; i++) {
                    Position p(start.x,i);
                    points.push_back(p);
                }
            }
            if (end.y < start.y) {
                for (int i=end.y + 1; i<start.y; i++) {
                    Position p(start.x,i);
                    points.push_back(p);
                }
            }
        }

        if (start.y == end.y) {
            if (end.x > start.x) {
                for (int i=start.x + 1; i<end.x; i++) {
                    Position p(i,start.y);
                    points.push_back(p);
                }
            }
            if (end.x < start.x) {
                for (int i=end.x + 1; i<start.x; i++) {
                    Position p(i,start.y);
                    points.push_back(p);
                }
            }
        }


        points.push_back(end);
    }

    void print() {
        for (Position p : points) {
            cerr << p.x << " " << p.y << endl;
        }
    }

};

int main()
{
    int nLines = 500;
    vector<Line> lines;

    for (int i=0; i<nLines; i++) {
        Line l;
        cin >> l.start.x >> l.start.y >> l.end.x >> l.end.y; cin.ignore();
        cerr << l.start.x << " " << l.start.y << " " << l.end.x << " " << l.end.y << endl;
        l.findPoints();
        
        if ( l.start.x == l.end.x || l.start.y == l.end.y) {
          //  l.print();
            lines.push_back(l);
        }        
    }

    vector<Position> points;
    points.clear();


    for (Line l : lines) {
        for (Position pp : l.points) {
            // find if exists
            // cerr << pp.x << " pp " << pp.y << endl;
            bool found = false;
            for (Position &p : points) {
                if (p.x == pp.x & p.y == pp.y) {
                    found = true;
                    p.n++;
                    cerr << p.n << endl;
                }
            }
            if (!found) {
                pp.n = 1;
                points.push_back(pp);
            }
        }
    }
    
    int nn = 0;
    for (Position p : points) {
        if (p.n>1) { nn++; }
    }

    cerr << "nn= " << nn << endl;

    
}
