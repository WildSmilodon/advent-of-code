
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../util.h"

using namespace std;

int main()
{
    string line;

    int nCards = 213; //6;
    int cards[nCards];
    for (int i = 0; i<nCards; i++) {
        cards[i] = 1;
    }
 
    int t = 0;
    int id = 0;
    while (getline(cin, line)) {

        vector<int> card;
        vector<int> my;
        vector<string> ss = splitString(line);
        bool pipe = false;
        for (string s : ss) {
            if (s == "|") {
                pipe = true;
            } else {
                if (pipe) {
                    my.push_back(stoi(s));
                } else {
                    card.push_back(stoi(s));
                }
            }
        }

        int n = 0;
        for (int x : my) {
            for (int c : card) {
                if (x==c) {
                    n++;
                }
            } 
        }
        if ( n > 0 ) {

            for (int i = 1; i<n+1; i++) {
                cards[id+i] = cards[id+i] + cards[id];
            }

            t = t + pow(2,n-1);
        }
        id++;
    }
    cerr << "Part 1 = " << t << endl;

    t = 0;
    for (int i = 0; i<nCards; i++) {
        t = t + cards[i];
    }
    cerr << "Part 2 = " << t << endl;
}
