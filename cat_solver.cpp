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

// responsible for undoing results and operations
void retreader(vector<int> &);

int main()
{
    vector<int> numbersNeeded{2, 10, 14};
    vector<int> solutionPath{};

    Solver(numbersNeeded, solutionPath);

    solutionPrinter(solutionPath);

    return 0;
}

void Solver(vector<int> numbersNeeded, vector<int> &solutionPath)
{
    double currentNumber = 0;
    vector<int> numbersAlreadyUsed;

    // the operation is recorded by a 0/1/2, which this variable does
    int solutionRecorder = 0;

    // The flag becomes false when the program has gone through every possible intro
    // without a valid path
    bool flag = true;
    while (flag == true)
    {
        solutionPath.push_back(solutionRecorder);
        currentNumber += 5;
        if (validResult(currentNumber, numbersAlreadyUsed))
        {
        }
        else if (solutionRecorder <= 2)
        {
            retreader(numbersAlreadyUsed, solutionPath);
        }

        else
        {
            // The flag becomes false when the program has gone through every possible intro
            // without a valid path
            flag = false;
        }
    }
}

bool validResult(double result, vector<int> &numbersAlreadyUsed)
{
    // weird
    // It will kill validResult if it [alreadyUsed] is T R U E
    if (alreadyUsedNumber(result, numbersAlreadyUsed))
    {
        return false;
    }

    // Checks to see if other two conditions are still being satisfied
    // If result is BIGGER than 60, OR if result ISN'T integer
    if ((result >= 60) || !((int)result == result))
    {
        return false;
    }
    // records the fresh number
    numbersAlreadyUsed.push_back(result);
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

bool alreadyUsedNumber(double result, vector<int> &numbersAlreadyUsed)
{
    // TODO: need to make sure number hasn't been repeated
    for (int i = 0; i < numbersAlreadyUsed.size(); i++)
    {
        // Maybe sort numbers at one point? Especially if the number of tries gets [ big ]
        if (result == numbersAlreadyUsed[i])
        {
            return true;
        }
    }

    return false;
}

void retreader(vector<int> &numbersAlreadyUsed, vector<int> &solutionPath)
{
    numbersAlreadyUsed.pop_back();
    solutionPath.pop_back();
}
