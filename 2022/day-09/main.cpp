
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


class Position {
public:
    Position(int row_, int col_) { row=row_; col=col_;}
    Position() { row=0; col=0;}
    int row;
    int col;

    void plus(Position p) {
        row += p.row;
        col += p.col;
    }

    void print() {
        cerr << "(" << row << "," << col << ")" << endl;
    }

    void move(Position head) {

            if (head.row - row ==  2 && head.col == col ) { plus(Position( 1, 0)); }
            if (head.row - row ==  2 && head.col  > col ) { plus(Position( 1, 1)); }
            if (head.row - row ==  2 && head.col  < col ) { plus(Position( 1,-1)); }

            if (head.row - row == -2 && head.col == col ) { plus(Position(-1, 0)); }
            if (head.row - row == -2 && head.col  > col ) { plus(Position(-1, 1)); }
            if (head.row - row == -2 && head.col  < col ) { plus(Position(-1,-1)); }


            if (head.col - col ==  2 && head.row == row ) { plus(Position( 0, 1)); }
            if (head.col - col ==  2 && head.row  > row ) { plus(Position( 1, 1)); }
            if (head.col - col ==  2 && head.row  < row ) { plus(Position(-1, 1)); }

            if (head.col - col == -2 && head.row == row ) { plus(Position( 0,-1)); }
            if (head.col - col == -2 && head.row  > row ) { plus(Position( 1,-1)); }
            if (head.col - col == -2 && head.row  < row ) { plus(Position(-1,-1)); }

    }

};




int main()
{

    string line;
    ifstream myfile; 

    myfile.open("input.txt");

    int snakeLength = 10;
    Position head(0,0);
    Position tail(0,0);
    vector<Position> tailPath;
    vector<Position> snakeTailPath;
    tailPath.push_back(tail);
    snakeTailPath.push_back(tail);

    vector<Position> snake;

    for (int i = 0; i<snakeLength; i++) { snake.push_back(head); }

    while ( getline (myfile,line) ) {

        vector<string> s;
        split(line,s,' ');

        Position direction;
        if (s[0]=="U")  { direction.row = -1; }
        if (s[0]=="D")  { direction.row =  1; }
        if (s[0]=="L")  { direction.col = -1; }
        if (s[0]=="R")  { direction.col =  1; }

        int distance = stoi(s[1]);

        for (int i = 0; i<distance; i++) {

            head.plus(direction);
            tail.move(head);

            snake[0].plus(direction);
            for (int i = 1; i<snakeLength; i++) {
                snake[i].move(snake[i-1]);
            }

            bool found = false;
            for (Position p : tailPath) {
                if (p.row == tail.row && p.col == tail.col) { found = true;}
            }
            if (!found) {tailPath.push_back(tail);}

            found = false;
            for (Position p : snakeTailPath) {
                if (p.row == snake[snakeLength-1].row && p.col == snake[snakeLength-1].col) { found = true;}
            }
            if (!found) {snakeTailPath.push_back(snake[snakeLength-1]);}


        }

    }

    myfile.close();

    cout << tailPath.size() << endl;
    cout << snakeTailPath.size() << endl;

}






