#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <optional>

#include "Dir.cpp"
#include "Tree.h"
#include "Utilities.h"

using namespace std;

bool is_cmd(const string &str)
{
    return regex_search(str, regex("^\\$"));
}

bool try_get_cd(const string &str, string *dest)
{
    const regex cd_pattern("^\\$ cd (.*)");

    smatch matches;

    if (!regex_match(str, matches, cd_pattern) || matches.size() != 2)
    {
        return false;
    }
    else
    {
        *dest = matches[1];

        return true;
    }
}

bool is_ls(const string &str)
{
    const regex ls_pattern("^\\$ ls");

    return regex_match(str, ls_pattern);
}

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    Tree files;
    vector<string> output;

    for (auto it = lines.begin() + 1; it != lines.end(); ++it) // skip the first cd
    {
        string dest;
        if (try_get_cd(*it, &dest))
        {
            files.cd(dest);

            continue;
        }

        vector<string> output;

        while (!is_cmd(*(it + 1))) // until the last line of output
        {
            ++it;

            output.push_back(*it);
        }

        output.push_back(*it); // add the last line

        files.ls(output);
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
