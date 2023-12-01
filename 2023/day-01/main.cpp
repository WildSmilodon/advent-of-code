
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int t = 0;
    int tt = 0;
    string line;
    while (getline(cin, line)) {
        
        // PART 1
        string r = "";
        for (char c : line) {
            if ( (int)c >= 49 && (int)c <= 57 ) {
                r = r + c;
            }            
        }
        string nS = r.substr(0,1) + r.substr(r.length()-1);
        t = t + stoi(nS);

        // PART 2
        r = "";
        for (int i = 0; i < line.length(); i++) {
            string ch = line.substr(i,1);
            if (line.substr(i,1) == "1") { r = r + "1"; }
            if (line.substr(i,1) == "2") { r = r + "2"; }
            if (line.substr(i,1) == "3") { r = r + "3"; }
            if (line.substr(i,1) == "4") { r = r + "4"; }
            if (line.substr(i,1) == "5") { r = r + "5"; }
            if (line.substr(i,1) == "6") { r = r + "6"; }
            if (line.substr(i,1) == "7") { r = r + "7"; }
            if (line.substr(i,1) == "8") { r = r + "8"; }
            if (line.substr(i,1) == "9") { r = r + "9"; }
            if (line.substr(i,3) == "one") { r = r + "1"; }
            if (line.substr(i,3) == "two") { r = r + "2"; }
            if (line.substr(i,5) == "three") { r = r + "3"; }
            if (line.substr(i,4) == "four") { r = r + "4"; }
            if (line.substr(i,4) == "five") { r = r + "5"; }
            if (line.substr(i,3) == "six") { r = r + "6"; }
            if (line.substr(i,5) == "seven") { r = r + "7"; }
            if (line.substr(i,5) == "eight") { r = r + "8"; }
            if (line.substr(i,4) == "nine") { r = r + "9"; }
        }

        nS = r.substr(0,1) + r.substr(r.length()-1);
        tt = tt + stoi(nS);

    }
    cout << t << endl;
    cout << tt << endl;
}
