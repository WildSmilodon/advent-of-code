
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;


int getPriority(string s) {
    const char* c = s.c_str();
    int priority = int(c[0]);
    if (priority < 97) { priority = priority - 38;} else {priority = priority - 96;}
    return priority;
}

int main()
{

    string line;
    ifstream myfile; 
    myfile.open("input.txt");

    int totalPriority = 0;
    int totalPriority2 = 0;
    int lineNo = 0;

    int p[53][3];
    for (int i = 0; i<53; i++) { 
        for (int j = 0; j<3; j++) { 
            p[i][j] = 0;
        } 
    }


    while ( getline (myfile,line) ) {

        int l = line.length() / 2;
        string r1 = line.substr(0,l);
        string r2 = line.substr(l,l);

        int priority = 0;

        for (int i = 0; i<l; i++) {
            string c1 = r1.substr(i,1);
            for (int j = 0; j<l; j++) {
                string c2 = r2.substr(j,1);
                if (c1 == c2) { priority = getPriority(c1); }
            }
        }
        totalPriority += priority;

        for (int i = 0; i<line.length(); i++) {        
            p[ getPriority(line.substr(i,1))   ][lineNo] = 1;
        }

        if (lineNo < 2) {
            lineNo++;
        } else {
            
            for (int i = 1; i<53; i++) { 
                if (p[i][0] == 1 && p[i][1] == 1 && p[i][2] == 1 ) {
                    totalPriority2 += i; 
                }
            }

            lineNo = 0;
            for (int i = 0; i<53; i++) { 
                for (int j = 0; j<3; j++) { 
                    p[i][j] = 0;
                } 
            }
        }
        


    }

    myfile.close();

    cout << totalPriority << endl;
    cout << totalPriority2 << endl;


}






