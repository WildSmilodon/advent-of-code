
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../util.h"

using namespace std;

int main()
{
    //int n = 3;
    //int times[] = {7 , 15 ,  30};
    //int dist[] = {9 , 40 , 200}; 

    //int n = 1;
    //int times[] = {71530};
    //int dist[] = {940200}; 

    //int n = 4;
    //int times[] = {47   ,  98 ,    66  ,   98};
    //int dist[] = {400  , 1213  , 1011 ,  1540}; 

    long long n = 1;
    long long times[] = {47986698};
    long long dist[] = {400121310111540}; 

    long long r = 1;
    for (int i = 0; i<n; i++) {
        long long nWin = 0;
        for (long v = 0; v < times[i]+1; v++) {
            long d = v * (times[i] - v);
            if ( d > dist[i] ) {
                nWin++;
            }
        }
        r = r * nWin;
    }

    cerr << "Result = " << r << endl;
}
