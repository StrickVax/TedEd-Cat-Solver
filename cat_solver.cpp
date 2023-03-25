#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void Solver(vector<int>, vector<int> &);

void solutionPrinter(vector<int> &);

bool validResult(double, vector<int> &);

int main()
{
    vector<int> numbersNeeded{2, 10, 14};
    vector<int> solutionPath{0, 0, 1, 0};

    // Solver(numbersNeeded, solutionPath);

    solutionPrinter(solutionPath);

    return 0;
}

void Solver(vector<int> numbersNeeded, vector<int> &solutionPath)
{
    double currentNumber = 0;
    vector<int> numbersAlreadyUsed;
    // the flag is to become false if the number fails any of these conditions:
    // --A number appears more than once
    // --A number is larger than 60
    // --A square root returns a non-integer number
    bool flag = true;
    while (flag == true)
    {
        solutionPath.push_back(0);
        currentNumber += 5;
        validResult(currentNumber, numbersAlreadyUsed);
    }
}

bool validResult(double result, vector<int> &numbersAlreadyUsed)
{
    // TODO: need to make sure number hasn't been repeated
    for (int i = 0; i < numbersAlreadyUsed.size(); i++)
    {
        if (result == numbersAlreadyUsed[i])
        {
            return false;
        }
    }

    // Checks to see if other two conditions are still being satisfied
    if ((result <= 60) || ((int)result == result))
    {
        return false;
    }
    else
    {
        numbersAlreadyUsed.push_back(result);
        return true;
    }
}

void solutionPrinter(vector<int> &orderOfOperations)
{
    // program prints out operations
    for (int i = 0; i < orderOfOperations.size(); i++)
    {
        cout << orderOfOperations[i];
        // adds an arrow pointing to the next number, if it's not the last one in the list
        if (i != orderOfOperations.size() - 1)
        {
            cout << " -> ";
        }
    }
}