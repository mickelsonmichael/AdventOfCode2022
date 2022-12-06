#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    for (string line : lines)
    {
        cout << line << '\n';
    }
}

void solvePart2(const vector<string> &lines)
{
    cout << "Solving part 2\n";

    for (string line : lines)
    {
        cout << line << '\n';
    }
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);

    isPart2(argc, argv)
        ? solvePart2(lines)
        : solvePart1(lines);
}
