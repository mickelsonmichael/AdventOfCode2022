#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <list>

#include "utils.h"
#include "topography.cpp"

using namespace std;



void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    Topography t(lines);

    const size_t steps = t.steps_to_optimal_signal();

    cout << "Steps required: " << steps << endl;
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
