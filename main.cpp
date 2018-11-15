#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
/**
 * The program reads numbers from line file and prints the sum of them
 * Example: main.exe ./tests/input.in
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */

// Checks if text contains '-' or '.' and is a valid number
bool ValidNumber(std::string inputToCheck);

float RoundThreeDecimals(float nrToRound);

int main(int argc, const char *argv[])
{
    std::ifstream myReadFile;
    myReadFile.open(argv[1]);
    if (myReadFile)
    {
        std::string a = "";

        int arraySize = 0;
        float sum = 0;
        float *numbersArr = new float[arraySize];
        bool textGood = true;

        while ((myReadFile >> a) && textGood)
        {
            if (ValidNumber(a))
            {
                float tempNumber = stof(a);
                arraySize++;
                float *tempArray = new float[arraySize];
                tempNumber = RoundThreeDecimals(tempNumber);

                for (int i = 0; i < (arraySize - 1); i++)
                {
                    tempArray[i] = numbersArr[i];
                }

                tempArray[arraySize - 1] = tempNumber;

                delete[] numbersArr;
                numbersArr = nullptr;

                numbersArr = tempArray;
                sum += tempNumber;
            }
            else
            {
                textGood = false;
            }
        }

        myReadFile.close();
        if (textGood)
        {
            if (arraySize > 0)
            {
                float average = sum / arraySize;
                for (int i = 0; i < arraySize; i++)
                {
                    if (numbersArr[i] > average)
                    {
                        std::cout << numbersArr[i] << " ";
                    }
                }
            }
            getchar();
        }

        if (numbersArr != nullptr)
        {
            delete[] numbersArr;
            numbersArr = nullptr;
        }
    }
    return 0;
}

float RoundThreeDecimals(float nrToRound)
{
    float roundedNr = roundf(nrToRound * 1000) / 1000;
    return roundedNr;
}

bool ValidNumber(std::string inputToCheck)
{
    bool isValid = true;

    int maxDotCharacters = 1;
    int maxMinusCharacters = 1;

    int currentDotAmount = 0;
    int currentMinusAmount = 0;

    for (int i = 0; i < inputToCheck.length() && isValid == true; i++)
    {
        if (!(isdigit(inputToCheck[i])))
        {
            if (i == 0)
            {
                if (inputToCheck[i] == '-')
                {
                    currentMinusAmount++;
                }
                else
                {
                    isValid = false;
                }
            }
            else
            {
                if (inputToCheck[i] == '.')
                {
                    currentDotAmount++;
                }
                else
                {
                    isValid = false;
                }

                if (isValid && ((currentDotAmount > maxDotCharacters) || (currentMinusAmount > maxMinusCharacters)))
                {
                    isValid = false;
                }
            }
        }
    }
    return isValid;
}