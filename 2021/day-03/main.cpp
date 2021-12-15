
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


class Data {
public:
    string binary;
    int decimal;
    bool active;

    bool isOne(int id) {
        return binary.substr(id,1) == "1";
    }

    void toDecimal() {
        decimal  = 0;
        for (int i = 0; i<binary.size(); i++) {
            if (binary.substr(i,1)=="1") {
                decimal = decimal + pow(2,binary.size()-i-1);
            }
        }
    }
};

int getNactive( vector<Data> v) {
    int nActive = 0;

    for (Data d : v) {
        if (d.active) {nActive++;}
    }

    return nActive;
}


int main()
{

    vector<Data> input;

    int n = 1000;
    int l = 0;


    for (int i = 0; i<n; i++) {
        Data d;
        cin >> d.binary; cin.ignore();
        d.active = true;
        input.push_back(d);
        l = d.binary.size();
     //   cerr << d.binary << " l " << l << endl;
    }

    Data gammarate;
    Data epsilonrate;
    gammarate.binary = "";
    epsilonrate.binary = "";

    for (int j = 0; j<l; j++) {
        int nOnes = 0;
        int nZeros = 0;
        for (int i = 0; i<n; i++) {
            if (input[i].isOne(j) ) {nOnes++;} else {nZeros++;}
        }
        if (nOnes > nZeros) {
            gammarate.binary = gammarate.binary + "1";
            epsilonrate.binary = epsilonrate.binary + "0";
        } else {
            gammarate.binary = gammarate.binary + "0";
            epsilonrate.binary = epsilonrate.binary + "1";
        }

    }

    cerr << gammarate.binary << endl;
    gammarate.toDecimal();
    cerr << gammarate.decimal << endl;

    cerr << epsilonrate.binary << endl;
    epsilonrate.toDecimal();
    cerr << epsilonrate.decimal << endl;

    cout <<  gammarate.decimal * epsilonrate.decimal << endl;


    // part II

    int j = 0;
    int nActive = getNactive(input);
    cerr << j << " " << nActive << endl;
    
    while (nActive > 1 & j<l) {

        int nOnes = 0;
        int nZeros = 0;
        for (int i = 0; i<n; i++) {
            if (input[i].active) {
                if (input[i].isOne(j) ) {nOnes++;} else {nZeros++;}
            }            
        }

        if (nOnes >= nZeros) {
            for (Data &d : input) {
                if (!d.isOne(j)) { d.active = false; }
            }
        } else {
            for (Data &d : input) {
                if (d.isOne(j)) { d.active = false; }
            }            
        }

        nActive = getNactive(input);
        j++;
        cerr << j << " " << nActive << endl;
    }

    Data oxygenGeneratorRating;
    for (Data &d : input) {
        if (d.active) { oxygenGeneratorRating = d; } 
    }
    cerr << oxygenGeneratorRating.binary << endl;
    oxygenGeneratorRating.toDecimal();
    cerr << oxygenGeneratorRating.decimal << endl;


    for (Data &d : input) {
        d.active = true;
    }

    j = 0;
    nActive = getNactive(input);
    cerr << j << " " << nActive << endl;
    
    while (nActive > 1 & j<l) {

        int nOnes = 0;
        int nZeros = 0;
        for (int i = 0; i<n; i++) {
            if (input[i].active) {
                if (input[i].isOne(j) ) {nOnes++;} else {nZeros++;}
            }   
        }

        if (nOnes >= nZeros) {
            for (Data &d : input) {
                if (d.isOne(j)) { d.active = false; }
            }
        } else {
            for (Data &d : input) {
                if (!d.isOne(j)) { d.active = false; }
            }            
        }

        nActive = getNactive(input);
        j++;
        cerr << j << " " << nActive << endl;
    }

    Data CO2scrubberRating;
    for (Data &d : input) {
        if (d.active) { CO2scrubberRating = d; } 
    }
    cerr << CO2scrubberRating.binary << endl;
    CO2scrubberRating.toDecimal();
    cerr << CO2scrubberRating.decimal << endl;    


    cout <<  oxygenGeneratorRating.decimal * CO2scrubberRating.decimal << endl;


}
