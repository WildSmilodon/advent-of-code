
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;



int main()
{

    string line;
    ifstream myfile; 

    myfile.open("input.txt");
    int size = 99;


    int grid[size][size];

    for (int r = 0; r<size; r++) {
        getline (myfile,line);
        for (int c = 0; c<size; c++) {
            grid[r][c] = stoi(line.substr(c,1));
        }    
    }
    myfile.close();

    bool visible;
    int nVisible = 0;
    for (int r = 0; r<size; r++) {
        for (int c = 0; c<size; c++) {
            
            bool done = false;
            visible = true;
            for (int i = c + 1; i < size; i++) {
                if (grid[r][i] >= grid[r][c]) { visible = false; }
            }
            if (visible) { nVisible++; done = true; }

            visible = true;
            if (!done) {
                for (int i = c - 1; i > -1; i--) {
                    if (grid[r][i] >= grid[r][c]) { visible = false; }
                }
                if (visible) { nVisible++; done = true; }
            }
            
            visible = true;
            if (!done) {
                for (int i = r + 1; i < size; i++) {
                    if (grid[i][c] >= grid[r][c]) { visible = false; }
                }
                if (visible) { nVisible++; done = true; }
            }

            visible = true;
            if (!done) {
                for (int i = r - 1; i > -1; i--) {
                    if (grid[i][c] >= grid[r][c]) { visible = false; }
                }
                if (visible) { nVisible++; done = true; }
            }
        }    
    }

    cout << nVisible << endl;


    int score;
    int maxScore = 0;

    for (int r = 0; r<size; r++) {
        for (int c = 0; c<size; c++) {
            
            int nLeft = 0;
            int nRight = 0;
            int nUp = 0;
            int nDown = 0;

            for (int i = c + 1; i < size; i++) {
                nRight++;
                if (grid[r][i] >= grid[r][c]) { break; }
            }

            for (int i = c - 1; i > -1; i--) {
                nLeft++;
                if (grid[r][i] >= grid[r][c]) { break; }
            }
            
            for (int i = r + 1; i < size; i++) {
                nDown++;
                if (grid[i][c] >= grid[r][c]) { break; }
            }
            for (int i = r - 1; i > -1; i--) {
                nUp++;
                if (grid[i][c] >= grid[r][c]) { break; }
            }

            score = nUp * nDown * nLeft * nRight;
            if (score > maxScore) {maxScore = score;}

        }    
    }


    cout << maxScore << endl;

}






