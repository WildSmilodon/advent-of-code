
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std; 


class Rule {
    public:

    string pattern;
    string insert;

    Rule() {}
    Rule(string p, string i) {
        pattern = p;
        insert = i;
    }
};

string getInsert(string mask, vector<Rule> rules) {
    string res = "";
    for (Rule r : rules) {
        if (mask == r.pattern) { res =  r.insert; }
    }
    return res;
}

string insertLetter(string insert, long long position, string poly) {
    string res = poly.substr(0,position);
    res = res + insert;
    res = res + poly.substr(position,poly.size()-position);
    return res;
}

void addElement(string element, vector<string> &elements) {
    bool found = false;
    for (string s : elements) {
        if (s==element) { found = true; }
    }
    if (!found) { elements.push_back(element); }
}


int main()
{

    int nRules = 16; //16; // 100;
    int nSteps = 10;
    vector<Rule> rules;
    vector<string> elements;

    string poly;
     cin >> poly;  cin.ignore();


    for (int i = 0; i<nRules; i++) {
        string p;
        string ins;
        cin >> p >> ins;  cin.ignore();
        rules.push_back(Rule(p,ins));
    }

    cerr << poly << endl;
    for (Rule r : rules) {
        cerr << r.pattern << " -> " << r.insert << endl;
        addElement(r.insert,elements);
        addElement(r.pattern.substr(0,1),elements);
        addElement(r.pattern.substr(1,1),elements);
    }


    for (int step = 0; step < nSteps; step++) {
        for (long long i = 0; i<poly.length()-1; i++) {
            string mask = poly.substr(i,2);
            string insert = getInsert(mask,rules);
            if (insert != "") {
                poly = insertLetter(insert,i+1,poly);
                i++;
             //   cerr << mask << " found " << insert << " new " << poly << endl;
            }
        }
        //cerr << poly << " " << poly.length() << endl;
        cerr  << step << " " << poly.length() << endl;
    }


    vector<long long> occurrences;
    for (string s : elements) {
        long nS = 0;
        for (int i = 0; i<poly.length(); i++) {
            if (poly.substr(i,1)==s) { nS++;}
        }
        occurrences.push_back(nS);    
      //  cerr << s << " " << occurrences[occurrences.size()-1] << endl;    
    }

    for (int i = 0; i<elements.size(); i++) {
        cerr << elements[i] << " nS " << occurrences[i] << endl;
    }

    sort(occurrences.begin(), occurrences.end(), greater<long>());

    for (int i = 0; i<elements.size(); i++) {
        cerr  << occurrences[i] << endl;
    }

    cout << "Result = " << occurrences[0] - occurrences[occurrences.size()-1] << endl;

}

