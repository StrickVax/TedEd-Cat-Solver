#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void Solver(vector<int>, vector<int> &);

void solutionPrinter(vector<int> &);

int main()
{
    vector<int> numbersNeeded {2, 10, 14};
    vector<int> solutionPath;

    Solver(numbersNeeded ,solutionPath);
    return 0;
}

void Solver(vector<int> numbersNeeded, vector<int> &solutionPath)
{
    // the flag is to become false if the number fails any of these conditions:
    // --A number appears more than once
    // --A number is larger than 60
    // --A square root returns a non-integer number
    bool flag = true;
    while (flag == true)
    {

    }
}

void solutionPrinter(vector<int> orderOfOperations)
{
    for (int i = 0; i < orderOfOperations.size(); i++)
    {
        cout << orderOfOperations[i] << " -> ";
    }
}