
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


class Element {

public:
    int row;
    int col;
    int id;
    int value;
    bool explored;
    vector<int> neighbors;
    int dist;

    Element(int id_, int r, int c) { 
        value = 0; 
        id = id_;
        row = r;
        col = c;
        explored = false;
        dist = 999999999;
    }

};


class Matrix {
    public:

    int nRow;
    int nCol;

    vector<Element> elements;

    Matrix(int nR, int nC) {
        nRow = nR;
        nCol = nC;

        for (int r = 0; r < nRow; r++ ) {
            for (int c = 0; c < nCol; c++ ) {
                elements.push_back(Element(getId(r,c),r,c));
            }
        }

        setNeibNoDiag(0,nRow-1,0,nCol-1);
    }

    int getId(int r, int c) {
        return r*(nRow)+c;
    }

    int get(int row, int col) {
        return elements[getId(row,col)].value;
    }

    void set(int row, int col, int value) {
        elements[getId(row,col)].value = value;
    }

    Element getElement(int row, int col) {
        return elements[getId(row,col)];
    }

    void print() {
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                cerr << get(r,c);
            }
            cerr << endl;
        }
    }

    void printDist() {
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                cerr << elements[getId(r,c)].dist << " ";
            }
            cerr << endl;
        }
    }

    void setNeibNoDiag(int rMin, int rMax, int cMin, int cMax) {

        for (int row = rMin; row < rMax+1; row++ ) {
            for (int col = cMin; col < cMax+1; col++ ) {

                if ( row > rMin & row < rMax & col > cMin & col < cMax ){
                    // Inside
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                }
                if (row == rMin & col > cMin & col < cMax ) {
                    // top row
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));            
                }
                if (row == rMax & col > cMin & col < cMax ) {
                    // bottom row
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                }
                if ( row > rMin & row < rMax & col == cMin  ){
                    // left col
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                }   
                if ( row > rMin & row < rMax & col == cMax ) {
                    // right col
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                } 
                if ( row == rMin & col == cMin ){
                    // corner
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                }
                if ( row == rMax & col == cMin ){
                    // corner
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                }  
                if ( row == rMin & col == cMax ){
                    // corner
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                }  
                if ( row == rMax & col == cMax ){
                    // corner
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                }                                                      
            }    
        }
    }


    void printNeib() {
        for (Element e : elements) {
            cerr << e.id << " ";
            for (int i : e.neighbors) {
                cerr << i << " "; 
            }
            cerr << endl;
        }
    }

    void setNeib(int rMin, int rMax, int cMin, int cMax) {

        for (int row = rMin; row < rMax; row++ ) {
            for (int col = cMin; col < cMax; col++ ) {

                if ( row > rMin & row < rMax & col > cMin & col < cMax ){
                    // Inside
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col+1));
                }
                if (row == rMin & col > cMin & col < cMax ) {
                    // top row
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col+1));            
                }
                if (row == rMax & col > cMin & col < cMax ) {
                    // bottom row
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                }
                if ( row > rMin & row < rMax & col == cMin  ){
                    // left col
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col+1));
                }   
                if ( row > rMin & row < rMax & col == cMax ) {
                    // right col
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                } 
                if ( row == rMin & col == cMin ){
                    // corner
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col+1));
                }
                if ( row == rMax & col == cMin ){
                    // corner
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col+1));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col+1));
                }  
                if ( row == rMin & col == cMax ){
                    // corner
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row+1,col  ));
                }  
                if ( row == rMax & col == cMax ){
                    // corner
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col-1));
                    elements[getId(row,col)].neighbors.push_back(getId(row-1,col  ));
                    elements[getId(row,col)].neighbors.push_back(getId(row  ,col-1));
                }                                                      
            }    
        }
    }


// 1  procedure BFS(G, root) is
// 2      let Q be a queue
// 3      label root as explored
// 4      Q.enqueue(root)
// 5      while Q is not empty do
// 6          v := Q.dequeue()
// 7          if v is the goal then
// 8              return v
// 9          for all edges from v to w in G.adjacentEdges(v) do
//10              if w is not labeled as explored then
//11                  label w as explored
//12                  Q.enqueue(w)

    void findPath(int start, int end) {
        vector<int> queue;
        elements[start].dist = 0;
        queue.push_back(start);
        int index = 0;


        while (index < queue.size()) {

            int me = queue[index];

            if ( me == end ) {
                return;
            }

            for (int nn : elements[me].neighbors) {
                if (elements[me].dist + elements[nn].value < elements[nn].dist) {
                    elements[nn].dist = elements[me].dist + elements[nn].value;
                    queue.push_back(nn);
                }
            }
            index++;
        }
    }

    int printPath(int end, int start) {

        int pos = end;
        int d = elements[pos].value - elements[start].value;
        cout << pos << " " << elements[pos].row << " " << elements[pos].col  << " " <<  elements[pos].dist << endl;

        while (pos != start) {
            int minDist = elements[pos].dist;
            int novi;
            for (int nn : elements[pos].neighbors) {
                if (elements[nn].dist < minDist) { novi = nn; minDist = elements[nn].dist; }
            }
            pos = novi;
            d = d + elements[pos].value;
            cout << pos << " " << elements[pos].row << " " << elements[pos].col << " " <<  elements[pos].dist << endl;
        }

        return d;
    }



};



int main()
{

    int n = 500;
    Matrix map(n,n);

    for (int r = 0; r < n; r++) {
        string s;
        cin >> s; cin.ignore();
        for (int c = 0; c<n; c++) {
            map.set(r,c,stoi(s.substr(c,1)));
        }
    }

    // create part 2 input file
//    for (int i = 0; i<5; i++) {
//        for (int r = 0; r < n; r++) {
//            for (int j=0; j<5; j++) {
//                for (int c=0;c<n;c++) {
//                    int val = map.get(r,c) + j + i;
//                    if (val > 9) { val = val - 9;}
//                    if (val > 9) { val = val - 9;}
//                    cout << val;
//                }
//            }
//            cout << endl;
//        }
//    }


    map.findPath(0,n*n-1);
    int d = map.printPath(n*n-1,0);
    
    cerr << d << endl;


}
