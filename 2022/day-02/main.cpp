
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric> // for accumulate
#include <fstream>


using namespace std;

const int ABC[] = {0,1,2};
const int XYZ[] = {0,1,2};
const int pScore[3] = {1,2,3};
const int score[3][3] = {{3,0,6}, {6,3,0}, {0,6,3}};
const int score2[3][3] = {{2,0,1}, {0,1,2}, {1,2,0}};
const int LDW[3] = {0,3,6};



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

    int abc = -1;
    int xyz = -1;

    int totScore = 0;
    int totScore2 = 0;

    while ( getline (myfile,line) ) {

        vector<string> s;
        split(line,s,' ');

        if (s[0] == "A") { abc = ABC[0]; }
        if (s[0] == "B") { abc = ABC[1]; }
        if (s[0] == "C") { abc = ABC[2]; }
        if (s[1] == "X") { xyz = XYZ[0]; }
        if (s[1] == "Y") { xyz = XYZ[1]; }
        if (s[1] == "Z") { xyz = XYZ[2]; }

        totScore = totScore + score[xyz][abc] + pScore[xyz];
        totScore2 = totScore2 + LDW[xyz] + pScore[score2[abc][xyz]];
    }

    cout << totScore << endl;
    cout << totScore2 << endl;

    myfile.close();



}






