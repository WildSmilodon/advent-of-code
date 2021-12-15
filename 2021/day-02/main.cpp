
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Inp {
public:

    string direction;
    int distance;
};

int main()
{

    vector<Inp> input;

    int x = 0;
    int depth = 0;

    int n = 1000;

    for (int i = 0; i<n; i++) {
        Inp inp; 
        cin >> inp.direction >> inp.distance; cin.ignore();
        input.push_back(inp);
    }


    for (Inp i : input) {
        // cerr << i.direction << " " << i.distance << endl;
        if (i.direction == "forward") { x = x + i.distance; }
        if (i.direction == "down") { depth = depth + i.distance; }
        if (i.direction == "up") { depth = depth - i.distance; }
    }

    cout << x << " " << depth << endl;

    cout << x*depth << endl;


// down X increases your aim by X units.
// up X decreases your aim by X units.
// forward X does two things:
// It increases your horizontal position by X units.
// It increases your depth by your aim multiplied by X.

    int aim = 0;
    x = 0;
    depth = 0;

    for (Inp i : input) {
        // cerr << i.direction << " " << i.distance << endl;
        if (i.direction == "forward") { x = x + i.distance; depth = depth +  i.distance * aim; }
        if (i.direction == "down") {  aim = aim + i.distance; }
        if (i.direction == "up") {  aim = aim - i.distance; }
    }

    cout << x << " " << depth << " " << aim << endl;
    cout << x*depth << endl;


}
