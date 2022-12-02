
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric> // for accumulate
#include <fstream>


using namespace std;


class Elf {
    public:

    vector<int> foodItem;
    int totalCalories;
};

bool comapre(Elf e1, Elf e2)
{
    return (e1.totalCalories > e2.totalCalories);
}
  

int main()
{

    vector<Elf> elves;

    int calories;
    string line;
    ifstream myfile; 
    myfile.open("input.txt");

    Elf elf;

    while ( getline (myfile,line) ) {
       
        if (line != "") {
            elf.foodItem.push_back(stoi(line));
        } else {
            elf.totalCalories = accumulate(elf.foodItem.begin(), elf.foodItem.end(),0); // calculate sum
            elves.push_back(elf);
            elf.foodItem.clear();
        }
    }
    myfile.close();

    sort(elves.begin(), elves.end(), comapre);

    cout << elves[0].totalCalories << endl;
    cout << elves[0].totalCalories + elves[1].totalCalories + elves[2].totalCalories << endl;

}






