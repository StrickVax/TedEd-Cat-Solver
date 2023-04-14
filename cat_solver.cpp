#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Tries to reach requested numbers
void Solver(vector<int>, vector<int> &);

// Tests to see if the current number is valid
bool validResult(double, vector<int> &, vector<int>);

// Checks to see if the number has been used before
bool alreadyUsedNumber(double, vector<int>);

// checks to see if an operation ( +5/ +7 / sqrt(x) ) was repeated in a row
bool repeatedInARow(vector<int>);

// function that records results and operations
void pusher(double &, vector<int> &, int &, vector<int> &);

// responsible for undoing results and operations
void retreader(double &, vector<int> &, vector<int> &);

// checks whether the solution has been found
bool validSolution(vector<int>, vector<int>);

// Prints out the numbers used to get to the results
void solutionPrinter(vector<int> &, vector<int>);

int main()
{
    vector<int> numbersNeeded{10, 5};
    vector<int> solutionPath{0};

    Solver(numbersNeeded, solutionPath);

    solutionPrinter(solutionPath, numbersNeeded);

    return 0;
}

void Solver(vector<int> numbersNeeded, vector<int> &solutionPath)
{
    double currentNumber = 0;
    vector<int> numbersAlreadyUsed;

    // the operation is recorded by a 0/1/2, which this variable does
    int solutionRecorder = 0;

    // Loop ends when it cannot find a valid solution
    bool flag = true;
    while (flag == true)
    {
        // checks to see if the result is valid
        if (validResult(currentNumber, numbersAlreadyUsed, solutionPath))
        {
            pusher(currentNumber, numbersAlreadyUsed, solutionRecorder, solutionPath);
        }
        // if not valid, program will undo previous push and attempt next operation
        else
        {
            retreader(currentNumber, numbersAlreadyUsed, solutionPath);
        }

        if (validSolution(numbersNeeded, numbersAlreadyUsed))
        {
            break;
        }

        // no solution found; ends the loop
        if ((solutionPath.size() == 1) && solutionPath[0] == 2)
        {
            flag = false;
        }
    }
}

bool validResult(double result, vector<int> &numbersAlreadyUsed, vector<int> solutionPath)
{
    if (alreadyUsedNumber(result, numbersAlreadyUsed))
    {
        return false;
    }

    if (repeatedInARow(solutionPath))
    {
        return false;
    }

    // Also checks to see if other two conditions are still being satisfied
    if ((result >= 60) || !((int)result == result))
    {
        return false;
    }

    return true;
}

bool alreadyUsedNumber(double result, vector<int> numbersAlreadyUsed)
{
    // It will mark the number it [ just ] got as already-used
    // So I have it delete that instance, and have it return with a
    // repeat if it finds it again

    for (int i = 0; i < numbersAlreadyUsed.size(); i++)
    {
        // Maybe sort numbers at one point? Especially if the number of tries gets [ big ]
        if (result == numbersAlreadyUsed[i])
        {
            numbersAlreadyUsed.erase(numbersAlreadyUsed.begin() + i);
            break;
        }
    }

    for (int i = 0; i < numbersAlreadyUsed.size(); i++)
    {
        if (result == numbersAlreadyUsed[i])
        {
            return true;
        }
    }

    return false;
}

bool repeatedInARow(vector<int> solutionPath)
{
    const int MAX_IN_ROW = 3;
    if (solutionPath.size() < MAX_IN_ROW)
    {
        return false;
    }

    // TODO: Fix magic number
    for (int i = 0; i < solutionPath.size() - 2; i++)
    {
        if (solutionPath[i] == solutionPath[i + 1])
            if (solutionPath[i + 1] == solutionPath[i + 2])
                return true;
    }

    return false;
}

void pusher(double &result, vector<int> &numbersAlreadyUsed, int &operation, vector<int> &solutionPath)
{
    // if the two vectors are the same size, solutionPath needs a new operation node
    if (numbersAlreadyUsed.size() == solutionPath.size())
    {
        solutionPath.push_back(0);
    }

    switch (solutionPath.back())
    {
    case 0:
        result += 5;
        break;

    case 1:
        result += 7;
        break;

    case 2:
        result = sqrt(result);
        break;
    }

    numbersAlreadyUsed.push_back(result);
}

void retreader(double &result, vector<int> &numbersAlreadyUsed, vector<int> &solutionPath)
{
    switch (solutionPath.back())
    {
    case 0:
        result = numbersAlreadyUsed[numbersAlreadyUsed.size() - 2];
        numbersAlreadyUsed.pop_back();
        solutionPath.back() = 1;
        break;

    case 1:
        result = numbersAlreadyUsed[numbersAlreadyUsed.size() - 2];
        numbersAlreadyUsed.pop_back();
        solutionPath.back() = 2;
        break;

    case 2:

        // while-loop is to clear away a ton of [2]s
        // | ...0, 2, 2, 2 | -> | ...1 |
        while (solutionPath.back() == 2 && solutionPath.size() > 0)
        {
            solutionPath.pop_back();
            numbersAlreadyUsed.pop_back();
        }

        numbersAlreadyUsed.pop_back();

        if (solutionPath.back() < 2)
        {
            solutionPath.back() += 1;
        }

        if (numbersAlreadyUsed.size() > 1)
        {
            result = numbersAlreadyUsed[numbersAlreadyUsed.size() - 1];
        }
        else
        {
            result = 0;
        }

        break;
    }
}

bool validSolution(vector<int> numbersNeeded, vector<int> numbersAlreadyUsed)
{
    // loop through every number used, looking to see if all required numbers appear
    for (int i = 0, j = 0; (i < numbersAlreadyUsed.size() && j < numbersNeeded.size()); i++)
    {
        if (numbersNeeded[j] == numbersAlreadyUsed[i])
        {
            j += 1;
        }

        // all needed numbers were found
        if (j == numbersNeeded.size())
        {
            return true;
        }
    }

    return false;
}

void solutionPrinter(vector<int> &orderOfOperations, vector<int> numbersNeeded)
{
    // if the program was unable to find a solution with the given parameters
    if (orderOfOperations.size() == 1 && orderOfOperations[0] == 2)
    {
        cout << "No solution exists";
        return;
    }

    // TODO: Record results found, instead of recreating the results with the solutionPath
    int currentNumber = 0;

    int j = 0;

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

        // highlights requested number
        if (currentNumber == numbersNeeded[j])
        {
            cout << "[" << currentNumber << "]";
            j += 1;
        }

        else
        {
            cout << currentNumber;
        }

        // adds an arrow pointing to the next number, if it's not the last one in the list
        if (i != orderOfOperations.size() - 1)
        {
            cout << " -> ";
        }
    }
}
