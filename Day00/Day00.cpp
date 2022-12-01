#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

void solve(vector<string> input)
{
    for (string s : input) {
        cout << s << '\n';
    }
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);

    solve(lines);
}
