
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n = 200;
    int values[n];


    for (int i = 0; i<n; i++) {
        cin >> values[i]; cin.ignore();
    }


    // PART 1
    for (int i = 0; i<n; i++) {
        for (int j = i + 1; j<n; j++) {
            int s = values[i] + values[j];
            //cerr << i << " " << j << " " << s << endl;
            if ( s == 2020) {
                cout << values[i] * values[j] << endl; 
            }
        }
    }

    // PART 2
    for (int i = 0; i<n; i++) {
        for (int j = i + 1; j<n; j++) {
            for (int k = j + 1; k<n; k++) {
                int s = values[i] + values[j] + values[k];
                //cerr << i << " " << j << " " << s << endl;
                if ( s == 2020) {
                    cout << values[i] * values[j] * values[k] << endl; 
                }
            }
        }
    }

}
