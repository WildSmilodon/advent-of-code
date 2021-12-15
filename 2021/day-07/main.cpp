
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int nnp1(int n) {
    return n*(n+1)/2;
}

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
    string s;
    cin >> s; cin.ignore();

    vector<string> hPosS;
    split( s, hPosS, ',' );

    vector<int> hPos;
    int minV = 100000;
    int maxV = -100000;
    for (string s : hPosS) {
        int v = stoi(s);
    //    cerr << v << endl;
        if (v < minV) {minV = v;}
        if (v > maxV) {maxV = v;}
        hPos.push_back(v);
    }

    cerr << hPos.size() << " " << minV << " " << maxV << endl;

    long long minFuel = 10000000000;
    for (int i = minV; i<maxV+1; i++) {
        long long fuel = 0;
        for (int v : hPos) {
            fuel = fuel + nnp1(abs(i-v));
        }
        if (fuel < minFuel) { minFuel = fuel;}
    }

    cerr << minFuel << endl;
    
}
