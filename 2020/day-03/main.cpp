
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
    
    int n = 323;
    int m = 31;

    int map[n][m];

    for (int i = 0; i<n; i++) {
        string s;
        cin >> s; cin.ignore();

        int j = 0;
        for (char c : s) {
            if (c == '.' ) { cerr << "."; map[i][j] = 0; }
            if (c == '#' ) { cerr << "#"; map[i][j] = 1; }
            j++;
        }
        cerr << endl;

    }

    int j = -3;
    int nTrees = 0;
    for (int i = 0; i<n; i++) {
    
        j = j + 3;
        j = j % m;
    
        if (map[i][j] == 1) { nTrees++; }

    }

    cerr <<  "Part 1 = " << nTrees << endl;

    // PART 2
    int nTrees1 = 0;
    int nTrees2 = 0;
    int nTrees3 = 0;
    int nTrees4 = 0;
    int j1 = -1;
    int j2 = -3;
    int j3 = -5;
    int j4 = -7;
    int i = -1;

    while (i < n - 1) {
        i = i + 1;
        j1 = (j1 + 1) % m;
        j2 = (j2 + 3) % m;
        j3 = (j3 + 5) % m;
        j4 = (j4 + 7) % m;

        if (map[i][j1] == 1) { nTrees1++; }
        if (map[i][j2] == 1) { nTrees2++; }
        if (map[i][j3] == 1) { nTrees3++; }
        if (map[i][j4] == 1) { nTrees4++; }

    }

    int nTrees5 = 0;
    int j5 = -1;
    i = -2;
    while (i < n - 1) {
        i = i + 2;
        j5 = (j5 + 1) % m;
        if (map[i][j5] == 1) { nTrees5++; }
    }

    long long result = 1;
    result *= nTrees1;
    result *= nTrees2;
    result *= nTrees3;
    result *= nTrees4;
    result *= nTrees5;

    cerr << "Part 2 : " << result << endl;    

}
