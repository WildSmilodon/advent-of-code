
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

    getline (myfile,line);

    int start;
    int start2;

    for (int i = 0; i < line.size()-3 ; i++) {

        if (line.substr(i, 1) != line.substr(i+1,1) &&
            line.substr(i ,1) != line.substr(i+2,1) &&
            line.substr(i ,1) != line.substr(i+3,1) &&
            line.substr(i+1,1)!= line.substr(i+2,1) &&
            line.substr(i+1,1)!= line.substr(i+3,1) &&
            line.substr(i+2,1)!= line.substr(i+3,1)      
         ) {
            start = i + 4;
            break;
         }
    }


    for (int i = 0; i < line.size()-14 ; i++) {

        bool found = true;
        for (int j = 0; j<14; j++) {
            for (int k = j + 1; k<14; k++) {
                if (line.substr(i+j, 1) == line.substr(i+k,1)) {
                    found = false;
                }
            }
        }
        if (found) { start2 = i+14; break; }
    }

    cout << start << endl;
    cout << start2 << endl;

}






