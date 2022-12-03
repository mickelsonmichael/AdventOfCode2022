#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Utilities.h"

#define LETTERS_IN_THE_ALPHABET 26

using namespace std;

int getIndex(char c)
{
    return c >= 'a'
               ? c - 'a'
               : c - 'A' + LETTERS_IN_THE_ALPHABET;
}

void solvePart1(vector<string> input)
{
    cout << "Solving part 1\n";

    int sum = 0;

    for (string backpack : input)
    {
        bool isInCompartment1[52] = {0};

        for (char c : backpack.substr(0, backpack.size() / 2))
        {
            int i = getIndex(c);

            isInCompartment1[i] = true;
        }

        for (char c : backpack.substr(backpack.size() / 2))
        {
            int i = getIndex(c);

            if (isInCompartment1[i])
            {
                sum += i + 1;

                break;
            }
        }
    }

    cout << "Part 1: " << sum << endl;
}

int getGroupPriority(const string *elves, bool isInCompartment[52][3])
{
    const size_t len = max(elves[0].size(), max(elves[1].size(), elves[2].size()));

    for (size_t l = 0; l < len; l++)
    {
        for (size_t e = 0; e < 3; e++)
        {
            if (elves[e].size() < l + 1)
            {
                continue;
            }

            int i = getIndex(elves[e][l]);

            isInCompartment[i][e] = true;

            if (isInCompartment[i][0] && isInCompartment[i][1] && isInCompartment[i][2])
            {
                return i + 1;
            }
        }
    }

    cout << "Could not locate the priority!" << endl;
    exit(1);
}

void solvePart2(vector<string> input)
{
    cout << "Solving part 2\n";

    int sum = 0;

    for (size_t i = 0; i < input.size(); i += 3)
    {
        bool isInCompartment[52][3] = {{0, 0, 0}};

        string elves[3];

        elves[0] = input[i];
        elves[1] = input[i + 1];
        elves[2] = input[i + 2];

        sum += getGroupPriority(elves, isInCompartment);
    }

    cout << "Part 2: " << sum << endl;
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);
    bool part2 = isPart2(argc, argv);

    part2 ? solvePart2(lines) : solvePart1(lines);
}
