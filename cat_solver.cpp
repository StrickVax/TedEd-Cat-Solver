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
bool alreadyUsedNumber(double, vector<int>);

// responsible for undoing results and operations
void retreader(double &, vector<int> &, vector<int> &);

// function that actually records results and operations
void pusher(double &, vector<int> &, int &, vector<int> &);

// function that sees if it should increase the operation, or add a new operation
// ie: | 0 -> 1 -> [0] | OR | 0 -> 2 |
bool repeat(vector<int> &, vector<int> &);

int main()
{
    vector<int> numbersNeeded{2, 10, 14};
    vector<int> solutionPath{0};

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

    int cycles = 0;

    // The flag becomes false when the program has gone through every possible intro
    // without a valid path
    bool flag = true;
    while (flag == true)
    {
        // this block checks to see if the result is valid
        if (validResult(currentNumber, numbersAlreadyUsed))
        {
            pusher(currentNumber, numbersAlreadyUsed, solutionRecorder, solutionPath);
        }
        // if sqrt is not valid, it will retread back two spaces, reset the operation to +5
        // and resume checking again
        else
        {
            retreader(currentNumber, numbersAlreadyUsed, solutionPath);
            cycles += 1;
        }

        if ((solutionPath.size() == 1) && (cycles != 0))
        {
            // The flag becomes false when the program has gone through every possible intro
            // without a valid path
            flag = false;
        }
    }
}

bool validResult(double result, vector<int> &numbersAlreadyUsed)
{
    if (alreadyUsedNumber(result, numbersAlreadyUsed))
    {
        return false;
    }

    // Checks to see if other two conditions are still being satisfied
    // If result is BIGGER than 60, OR if result ISN'T integer
    if ((result >= 20) || !((int)result == result))
    {
        return false;
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

bool alreadyUsedNumber(double result, vector<int> numbersAlreadyUsed)
{

    // TODO: need to make sure number hasn't been repeated
    for (int i = 0; i < numbersAlreadyUsed.size(); i++)
    {
        // Maybe sort numbers at one point? Especially if the number of tries gets [ big ]
        if (result == numbersAlreadyUsed[i])
        {
            // there's an issue where it will mark the number it [ just ] got as already-used
            // So to compromise, I have it delete that instance, and have it return with a
            // repeat if it finds it [twice]
            numbersAlreadyUsed.erase(numbersAlreadyUsed.begin() + i);
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

void pusher(double &result, vector<int> &numbersAlreadyUsed, int &operation, vector<int> &solutionPath)
{

    // operation = solutionPath.back();
    // solutionPath.push_back(operation);

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

        // this chunk of code should only execute to clear away a ton of square roots
        // ...0, 2, 2, 2 -> ...1
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

        result = numbersAlreadyUsed[numbersAlreadyUsed.size() - 1];

        break;
    }
}

bool repeat(vector<int> &numbersAlreadyUsed, vector<int> &solutionPath)
{
    if (numbersAlreadyUsed.size() == solutionPath.size())
    {
        return false;
    }
    return true;
}