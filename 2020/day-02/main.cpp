
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class pass {
public:
    int start;
    int end;
    char letter;
    string password;
};

int main()
{
    vector<pass> gesla;
    
    int n = 1000;

    for (int i = 0; i<n; i++) {
        pass p;
        cin >> p.start >> p.end >> p.letter >> p.password; cin.ignore();
        gesla.push_back(p);
    }

    // PART 1
    int valid = 0;
    for (pass p : gesla) {
        n = 0;
        for (char c : p.password) {
            if (p.letter == c) {
                n++;
            }
        }
        if (n >= p.start && n <= p.end) {
            valid++;
        }
    }
    cerr << valid << endl;

    // PART 2
    valid = 0;

    for (pass p : gesla) {
        n = 0;
        if (p.letter == p.password[p.start - 1]) {n++;}
        if (p.letter == p.password[p.end - 1]) {n++;}      
        if (n == 1) { valid++; }
    }
    cerr << valid << endl;

}
