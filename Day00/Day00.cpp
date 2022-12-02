#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

void solvePart1(vector<string> input)
{
    cout << "Solving part 1\n";

    for (string s : input) {
        cout << s << '\n';
    }
}

void solvePart2(vector<string> input)
{
    cout << "Solving part 2\n";

    for (string s : input) {
        cout << s << '\n';
    }
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);
    bool part2 = isPart2(argc, argv);

    part2 ? solvePart2(lines) : solvePart1(lines);
}
