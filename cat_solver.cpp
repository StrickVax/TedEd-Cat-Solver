#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Main function that tests to see if a number can be reached with operations
void Solver(vector<int>, vector<int> &);

// Prints out the numbers used to get to the results
void solutionPrinter(vector<int> &);

// Tests to see if the current number is valid
bool validResult(double, vector<int> &);

// Checks to see if the number has already been used before
bool alreadyUsedNumber(double, vector<int> &);

int main()
{
    vector<int> numbersNeeded{2, 10, 14};
    vector<int> solutionPath{0,0,0,0,0,2};

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
        if (validResult(currentNumber, numbersAlreadyUsed))
        {
        }
    }
}

bool validResult(double result, vector<int> &numbersAlreadyUsed)
{
    // Checks to see if other two conditions are still being satisfied
    if ((result <= 60) || ((int)result == result))
    {
        return false;
    }
    else
    {
        // records the fresh number
        numbersAlreadyUsed.push_back(result);
        return true;
    }
}

bool alreadyUsedNumber(double result, vector<int> &numbersAlreadyUsed)
{
    // TODO: need to make sure number hasn't been repeated
    for (int i = 0; i < numbersAlreadyUsed.size(); i++)
    {
        // Maybe sort numbers at one point? Especially if the number of tries gets [ big ]
        if (result == numbersAlreadyUsed[i])
        {
            return false;
        }
    }

    return true;
}

void solutionPrinter(vector<int> &orderOfOperations)
{
    // if the program was unable to find a solution with the given parameters
    if (orderOfOperations.size() == 0)
    {
        cout << "No solution exists";
    }

    int currentNumber = 0;

    // program prints out operations
    for (int i = 0; i < orderOfOperations.size(); i++)
    {
        switch (orderOfOperations[i])
        {
        case 0:
            currentNumber += 5;
            break;
        
         case 1:
            currentNumber += 7;
            break;

        case 2:
            currentNumber = sqrt(currentNumber);
            break;
        }

        cout << currentNumber;
        // adds an arrow pointing to the next number, if it's not the last one in the list
        if (i != orderOfOperations.size() - 1)
        {
            cout << " -> ";
        }
    }
}