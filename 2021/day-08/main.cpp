
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int nnp1(int n) {
    return n*(n+1)/2;
}

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

bool isIn(string s, string l) {
    bool r = false;
    for (int i = 0; i<s.length(); i++) {
        if (s.substr(i,1)==l) { r = true;}
    }

    return r;

}

class Values {
public:
    string uniqueSignalPatterns[10];
    string fourDigitOutputValue[4];
    int digitsSignal[10];
    int digitsOutput[4];

    void add(vector<string> segments) {
        for (int i = 0; i<10; i++) {
            uniqueSignalPatterns[i] = segments[i];
        }
        for (int i = 0; i<4; i++) {
            fourDigitOutputValue[i] = segments[ 11 + i];
        }
    }

    void read() {
        for (int i = 0; i<10; i++) {
           cin >> uniqueSignalPatterns[i]; cin.ignore();
            digitsSignal[i]=-1;
        }
        string s;
        cin >> s; cin.ignore();   
        for (int i = 0; i<4; i++) {
            cin >> fourDigitOutputValue[i]; cin.ignore();
            digitsOutput[i]=-1;
        }        
    }

    void print() {

        for (int i = 0; i<10; i++) {
           cerr << uniqueSignalPatterns[i] << " ";
        }
        cerr << endl;
        for (int i = 0; i<4; i++) {
            cerr << fourDigitOutputValue[i] << " ";
        }
        cerr << endl;
    }
};

int main()
{
    //int nLines = 10;
    int nLines = 200;
 
    vector<Values> vals;
    for (int i = 0; i<nLines; i++) {
        Values v;
        v.read();
        v.print();
        vals.push_back(v);
    }

    int n = 0;
    int totVal = 0;
    for (Values v : vals) {
        for (int i = 0; i<4; i++) {
            if (v.fourDigitOutputValue[i].length()==2) {v.digitsOutput[i]=1;}
            if (v.fourDigitOutputValue[i].length()==4) {v.digitsOutput[i]=4;}
            if (v.fourDigitOutputValue[i].length()==3) {v.digitsOutput[i]=7;}
            if (v.fourDigitOutputValue[i].length()==7) {v.digitsOutput[i]=8;}
        }
        vector<string> threeSix;
        vector<string> threeFive;
        string enka;
        string stirka;
        for (int i = 0; i<10; i++) {
            if (v.uniqueSignalPatterns[i].length()==2) {v.digitsSignal[i]=1; enka = v.uniqueSignalPatterns[i]; }
            if (v.uniqueSignalPatterns[i].length()==4) {v.digitsSignal[i]=4; stirka = v.uniqueSignalPatterns[i];}
            if (v.uniqueSignalPatterns[i].length()==3) {v.digitsSignal[i]=7;}
            if (v.uniqueSignalPatterns[i].length()==7) {v.digitsSignal[i]=8;}
            if (v.uniqueSignalPatterns[i].length()==6) {threeSix.push_back(v.uniqueSignalPatterns[i]);}
            if (v.uniqueSignalPatterns[i].length()==5) {threeFive.push_back(v.uniqueSignalPatterns[i]);}
        }

      // 1,4,7,8 vem
        cerr << threeSix.size() << endl;
        cerr << threeFive.size() << endl;


        // 6ka
        int c6 = -1;
        for (int j = 0; j<3; j++) {
            if ( ( isIn(threeSix[j],enka.substr(0,1)) & !isIn(threeSix[j],enka.substr(1,1)) ) || (!isIn(threeSix[j],enka.substr(0,1)) & isIn(threeSix[j],enka.substr(1,1)) )) { 
                for (int i = 0; i<10; i++) {
                    if (v.uniqueSignalPatterns[i]==threeSix[j]) {v.digitsSignal[i]=6; c6=j; cerr << "6=" << i << endl; }
                }
            }
        }

        // 9ka ima v sebi celo 4, 0ki pa manjka
        string devetka;
        int c9 = -1;
        for (int j = 0; j<3; j++) {
            if ( c6 != j  ) { 
                if ( isIn(threeSix[j],stirka.substr(0,1)) & isIn(threeSix[j],stirka.substr(1,1)) & isIn(threeSix[j],stirka.substr(2,1)) & isIn(threeSix[j],stirka.substr(3,1)) ) {
                    for (int i = 0; i<10; i++) {
                        if (v.uniqueSignalPatterns[i]==threeSix[j]) {v.digitsSignal[i]=9; c9=j;  devetka=v.uniqueSignalPatterns[i]; cerr << "9=" << i << endl; }
                    }
                }
            }
        }

        // 0ki pa manjka
        for (int j = 0; j<3; j++) {
            if ( c6 != j  & c9 != j ) { 
                for (int i = 0; i<10; i++) {
                    if (v.uniqueSignalPatterns[i]==threeSix[j]) {v.digitsSignal[i]=0; cerr << "0=" << i << endl; }
                }
            }
        }


        int c3 = -1;
        for (int j = 0; j<3; j++) {
            if (  isIn(threeFive[j],enka.substr(0,1)) & isIn(threeFive[j],enka.substr(1,1))  )  { 
                for (int i = 0; i<10; i++) {
                    if (v.uniqueSignalPatterns[i]==threeFive[j]) {v.digitsSignal[i]=3; c3=j; cerr << "3=" << i << endl; }
                }
            }
        } 

        // 5ka je v celi 9ki       
        int c5 = -1;
        for (int j = 0; j<3; j++) {
            if ( c3 != j  ) { 
                if ( isIn(devetka,threeFive[j].substr(0,1)) & isIn(devetka,threeFive[j].substr(1,1)) &  isIn(devetka,threeFive[j].substr(2,1)) &  isIn(devetka,threeFive[j].substr(3,1)) & isIn(devetka,threeFive[j].substr(4,1))  )  { 
                    for (int i = 0; i<10; i++) {
                        if (v.uniqueSignalPatterns[i]==threeFive[j]) {v.digitsSignal[i]=5; c5=j; cerr << "5=" << i << endl; }
                    }
                }
            }
        } 

        // 2ki pa manjka
        string dvojka;
        for (int j = 0; j<3; j++) {
            if ( c3 != j  & c5 != j ) { 
                for (int i = 0; i<10; i++) {
                    if (v.uniqueSignalPatterns[i]==threeFive[j]) {v.digitsSignal[i]=2; dvojka = v.uniqueSignalPatterns[i]; cerr << "2=" << i << endl; }
                }
            }
        }

        // tu nadaljuj
        int val = 0;
        for (int i = 0; i<4; i++) {
            for (int j = 0; j<10; j++) {
                if ( v.fourDigitOutputValue[i].length() == v.uniqueSignalPatterns[j].length() ) {
                    bool found = true;
                    for (int k=0; k<v.fourDigitOutputValue[i].length(); k++ ) {
                        string s = v.fourDigitOutputValue[i].substr(k,1);
                        if (!isIn(v.uniqueSignalPatterns[j],s)) { found = false; }
                    }
                    if (found) { v.digitsOutput[i]=v.digitsSignal[j];  }
                }
            }
            //cerr << v.digitsOutput[i];
            val = val + v.digitsOutput[i] * pow(10,3-i);
        }
        //cerr << endl;
        cerr << val << endl;
        totVal = totVal + val;




       

    }

   
    cout << totVal << endl;


}
