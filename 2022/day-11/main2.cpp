
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;



size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}


class Monkey {
public:
    vector<int> itemWorryLevel;
    string operation;
    long operationValue;
    long nInspections;
    long trueMonkey;
    long falseMonkey;
    long divisibleBy;

    Monkey() { itemWorryLevel.clear(); operationValue=0; operation=""; nInspections=0; trueMonkey=-1; falseMonkey=-1;}




    void print() {
        cerr << operation << operationValue << " " << divisibleBy << " " << trueMonkey << " " << falseMonkey << " " << nInspections << endl;
        for (long x : itemWorryLevel)  { cerr << x << " "; }
        cerr << endl;
    }

};

int main()
{

    string line;
    ifstream myfile; 

    myfile.open("input.txt");

    long nRounds = 10000;
    long round = 0;
    vector<Monkey> opice;

    getline (myfile,line);
    long nOpic = stoi(line);

    vector<string> s;

    for (long i=0; i<nOpic; i++) {

        Monkey m;

        getline (myfile,line);
        split(line,s,' ');
        
        // item list
        getline (myfile,line);
        split(line,s,' ');
        for (long j=4;j<s.size();j++) { m.itemWorryLevel.push_back(stoi(s[j])); }
        
        // operation
        getline (myfile,line);
        split(line,s,' ');
        m.operation = s[6];
        if (s[7] == "old") {
            m.operation="**";
        } else {
            m.operationValue = stoi(s[7]);
        }
        
        // divisible by
        getline (myfile,line);
        split(line,s,' ');
        m.divisibleBy = stoi(s[5]);

        // true
        getline (myfile,line);
        split(line,s,' ');
        m.trueMonkey = stoi(s[9]);

        // false
        getline (myfile,line);
        split(line,s,' ');
        m.falseMonkey = stoi(s[9]);

        opice.push_back(m);

    } 

    myfile.close();

    long modulo = 1;
    for (Monkey m : opice) {
        modulo *= m.divisibleBy;
    }

    for (long r = 0; r<nRounds; r ++) {

        for ( long m = 0; m<opice.size(); m++) {

            opice[m].nInspections += opice[m].itemWorryLevel.size();

            for (long item : opice[m].itemWorryLevel ) {
 
                if (opice[m].operation == "+") { item = item + opice[m].operationValue; }
                if (opice[m].operation == "*") { item = item * opice[m].operationValue; }
                if (opice[m].operation == "**") { item = item * item;   }

               item = item % modulo;

                long targetMonkey = -1;
                if (item % opice[m].divisibleBy) {
                    targetMonkey = opice[m].falseMonkey;
                } else {
                    targetMonkey = opice[m].trueMonkey;
                }
        
                opice[targetMonkey].itemWorryLevel.push_back(item);
            }
            opice[m].itemWorryLevel.clear();
        }
    }

    long max1 = 0;
    long max2 = 0;
    for (Monkey m : opice) {
        if (m.nInspections > max1) {max1 = m.nInspections;} 
    }
    for (Monkey m : opice) {
        if (m.nInspections > max2 && m.nInspections != max1) {max2 = m.nInspections;} 
    }

    long monkeyBusiness = max1 * max2;
    cout << monkeyBusiness << endl;
}






