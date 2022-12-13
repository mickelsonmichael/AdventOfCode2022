#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "utils.h"
#include "cpu.cpp"

using namespace std;

bool try_get_addx(const string &str, int *val)
{
    const regex pattern("addx (-?[0-9]+)");
    smatch matches;

    if (!regex_match(str, matches, pattern))
    {
        return false;
    }

    *val = stoi(matches[1]);

    return true;
}

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    CPU cpu;

    for (const string &line : lines)
    {
        int to_add;
        if (try_get_addx(line, &to_add))
        {
            // cout << "Adding " << to_add << '\n';
            
            cpu.addx(to_add);
        }
        else
        {
            // cout << "noop\n";

            cpu.noop();
        }
    }

    cout << "Sum signal strength:" << cpu.signal_strength() << endl;
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
