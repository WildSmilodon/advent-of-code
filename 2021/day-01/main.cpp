
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n = 2000;
    int values[n];

    int nInc = 0;

    for (int i = 0; i<n; i++) {
        cin >> values[i]; cin.ignore();

        if (i>0) {
            if (values[i]>values[i-1]) {nInc++;}
        }

     //   cerr << values[i] << endl;
    }

    cout << nInc << endl;

    // Part II

    int nn = n-2;
    int threeSums[nn];
    for (int i = 0; i<nn; i++) {
        threeSums[i] = values[i] + values[i+1] + values[i+2]; 
         //   cerr << threeSums[i] << endl;
    }

    nInc = 0;
    for (int i = 1; i<nn; i++) {
        if (threeSums[i] > threeSums[i-1]) { nInc++; } 
    }

    cout << nInc << endl;



}
