
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;



int main()
{
    int nFish = 300;
    long long nStartVal[9];
    //int nTime = 80;
    int nTime = 256;

    for (int i=0; i<9; i++) {
        nStartVal[i]=0;
    }

    for (int i=0; i<nFish; i++) {
        int v;
        cin >> v; cin.ignore();
        nStartVal[v]++;
    }

    for (int i=0; i<9; i++) {
        cerr << nStartVal[i] << endl;
    }

    for (int t = 0; t<nTime; t++) {
        // Decrease by 1
        long long  givingBirth = nStartVal[0];
        for (int i=0; i<8; i++) {
            nStartVal[i] = nStartVal[i+1];
        }
        nStartVal[8] = givingBirth;
        nStartVal[6] = nStartVal[6] + givingBirth;
    }

    long long sum = 0;
    for (int i=0; i<9; i++) {
        sum = sum + nStartVal[i];
    }

    cerr << "nn= " << sum << endl;

    
}
