
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

        int dx = end.x - start.x;
        int dy = end.y - start.y;
        int n = 1 + max(abs(dx),abs(dy));


        if (dx > 1 ) { dx =  1; }
        if (dx < -1 ) { dx = -1; }
        if (dy > 1 ) { dy =  1; }
        if (dy < -1 ) { dy = -1; }

        for (int i= 0; i<n; i++) {
            Position p(start.x + i*dx, start.y + i*dy);
            points.push_back(p);           
        }    
        
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
        
            // l.print();
            lines.push_back(l);
                
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
