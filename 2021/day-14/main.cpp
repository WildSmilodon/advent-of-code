
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

class Pair {
    public:

    string two;
    vector<string> produces;
    long long n;

    Pair(string a, string b, vector<Rule> rules) {
        n = 0;
        two = a + b;
        produces.clear();
        for (Rule r : rules) {
            if (r.pattern == two) {
                produces.push_back(a+r.insert);
                produces.push_back(r.insert+b);
            }
        }
    }

    void print() {
        cerr << two << " " ;
        for (string s : produces) {
            cerr << s << " " ;
        }
        cerr << " " << n << endl;
    }
};


int main()
{

    int nRules = 100; //16; // 100;
    int nSteps = 40;
    vector<Rule> rules;
    vector<string> elements;
    vector<Pair> pairs;

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


    for (string ena : elements) {
        for (string dva : elements) {
            pairs.push_back(Pair(ena,dva,rules));
        }
    }


    for (int i = 0; i<poly.length()-1; i++) {
        string mask = poly.substr(i,2);

        for (Pair &p : pairs) {
            if (p.two == mask) { p.n++; }
        }
    }


    for (Pair p : pairs) {
        p.print();
    }

    for (int step = 0; step < nSteps; step++) {
        vector<Pair> copy = pairs;
        for (Pair c : copy) {
            // add two children
            for (Pair &p : pairs) {
                if (c.produces[0] == p.two) { p.n = p.n + c.n; }
                if (c.produces[1] == p.two) { p.n = p.n + c.n; }
            }
            // remove my pair
            for (Pair &p : pairs) {
                if (c.two == p.two) {p.n = p.n - c.n;}
            }
        }

        cerr << "step " << step+1 << endl;
        for (Pair p : pairs) {
            p.print();
        }
    }

    long long t = 0;
    for (Pair p : pairs) {
        t = t + p.n;
    }
    cerr << t+1 << endl;


    vector<long long> occurrences;
    for (string s : elements) {
        long nS = 0;
        if ( s == poly.substr(poly.length()-1,1)) { nS++; }
        for (Pair p : pairs) {
            if ( s == p.two.substr(0,1)){ nS = nS + p.n; }
        }
        occurrences.push_back(nS);     
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
