
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../util.h"

using namespace std;

class Pull {
public:

    Pull() {r=0; g=0; b=0;}
    int r;
    int g;
    int b;
};

int main()
{
    string line;
    int t = 0;
    int totalPower = 0;
    while (getline(cin, line)) {
        
        // PART 1
        vector<std::string> tokens = split(line,':');
        vector<std::string> game = split(tokens[0],' ');
        vector<std::string> pullsS = split(tokens[1],';');
        int id = stoi(game[1]);

        vector<Pull> pulls;
        pulls.clear();
        for (string p : pullsS) {
            vector<std::string> oneColor = split(p,',');
            Pull pull;

            for (string oc : oneColor) {
                vector<std::string> o = splitString(oc,' ');
                int n = stoi(o[0]);                
                if (o[1] == "red") { pull.r = n; }
                if (o[1] == "green") { pull.g = n; }
                if (o[1] == "blue") { pull.b = n; }                
            }
            pulls.push_back(pull);
        }

        Pull minPull;

        bool ok = true;
        for (Pull p : pulls) {
            
            if (p.r > 12) { ok = false;} 
            if (p.g > 13) { ok = false;} 
            if (p.b > 14) { ok = false;}

            if (p.r > minPull.r) { minPull.r = p.r;}
            if (p.g > minPull.g) { minPull.g = p.g;}
            if (p.b > minPull.b) { minPull.b = p.b;}
            
        }
        int power = minPull.r * minPull.g * minPull.b;
        totalPower = totalPower + power;
        if (ok) { t = t + id; } 
    }
    cout << t << endl;
    cout << totalPower << endl;
}
