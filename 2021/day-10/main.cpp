
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

string flip(string s) {
    string r = "";

//    if ( s=="(" ) { r = ")"; }
//    if ( s=="{" ) { r = "}"; }
//    if ( s=="[" ) { r = "]"; }
//    if ( s=="<" ) { r = ">"; }

    if ( s==">" ) { r = "<"; }
    if ( s=="}" ) { r = "{"; }
    if ( s=="]" ) { r = "["; }
    if ( s==")" ) { r = "("; }

    return r;
}

string flipOpen(string s) {
    string r = "";

    if ( s=="(" ) { r = ")"; }
    if ( s=="{" ) { r = "}"; }
    if ( s=="[" ) { r = "]"; }
    if ( s=="<" ) { r = ">"; }

    return r;
}


void remove(string &s ) {
    string r = "";

    for (int j = 0; j<s.length(); j++) {

        if (j < s.length() - 1) {
            if ( s.substr(j,1) != flip(s.substr(j+1,1)) ) { 
                r = r + s.substr(j,1); 
            } else {
                j++;
            }  
        }  else {
            r = r + s.substr(j,1);
        }


    }

    s = r;
}

string turnAround(string s) {
    string r = "";

    for (int i = s.length(); i>0; i--) {
        r = r + flipOpen(s.substr(i-1,1));
    }

    return r;
}

int main()
{

    int nLines = 94;
    int n[4];
    vector<string> data;

    for (int i = 0; i<4; i++) {
        n[i] = 0;
    }


    long score = 0;

    for (int i = 0; i<nLines; i++) {
        string line;
        cin >> line;  cin.ignore();
        cerr << "nnew " << line << endl;
        bool corr = false;


        bool notDone = true;
        while (notDone) {
            int l = line.length();
            remove(line);
            
            if (l == line.length() ) { notDone = false; }
        }
            
        for (int i = 0; i < line.length(); i++) {
            if ( line.substr(i,1) == "]" || line.substr(i,1) == ")" || line.substr(i,1) == "}" || line.substr(i,1) == ">"  ) {
                corr = true;
        
                if ( line.substr(i,1) == ")" ) { score = score + 3; }
                if ( line.substr(i,1) == "]" ) { score = score + 57; }
                if ( line.substr(i,1) == "}" ) { score = score + 1197; }
                if ( line.substr(i,1) == ">" ) { score = score + 25137; }

                break;
            }
        
        }

        if (!corr) { data.push_back(line); }

    }

    cerr  << score << endl;


    vector<long> scores;

    for (string s : data) {

        string r = turnAround(s);
        
        score = 0;
        

        for (int j=0; j<r.length(); j++) {
            score = score * 5;

            
            if ( r.substr(j,1)==")" ) { score = score + 1; }
            if ( r.substr(j,1)=="}" ) { score = score + 3; }
            if ( r.substr(j,1)=="]" ) { score = score + 2; }
            if ( r.substr(j,1)==">" ) { score = score + 4; }
        }

        cerr << s << " " << r << " " << score << endl;

        scores.push_back(score);

    }


     std::sort(scores.begin(), scores.end(), greater<long>() );
     std::sort(scores.begin(), scores.end());

    for (long i : scores) {
        cerr << i << endl;
    }



    cerr  << scores[(scores.size()+1)/2-1] << endl;


}
