#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <optional>

#include "Item.h"
#include "Dir.h"
#include "File.h"
#include "Utilities.h"

using namespace std;

Dir process_dir(const string &str)
{
    const regex dir_pattern("^dir (.*)");

    smatch matches;

    if (!regex_match(str, matches, dir_pattern) || matches.size() != 1)
    {
        cout << "UNABLE TO PARSE DIR: " << str;
        exit(1);
    }

    return Dir(matches[0]);
}

File process_file(const string &str)
{
    const regex file_pattern("^(.*) (.*)");

    smatch matches;

    if (!regex_match(str, matches, file_pattern) || matches.size() != 2)
    {
        cout << "UNABLE TO PARSE FILE: " << str;
        exit(1);
    }

    string name = matches[0];
    int size = stoi(matches[1]);

    return File(name, size);
}

Item process_item(const string &str)
{
    const regex dir_pattern("^dir (.*)");
    const regex file_pattern("^(.*) (.*)");

    if (regex_search(str, dir_pattern))
    {
        return process_dir(str);
    }

    if (regex_search(str, file_pattern))
    {
        return process_file(str);
    }

    cout << "UNSUPPORTED LINE: " << str;
    exit(1);
}

Item get_tree(const vector<string> &lines)
{
    const regex cmd_regex("\\$ (.*)");
    const regex is_ls("ls");
    const regex is_cd("cd");

    optional<Dir> dir = nullopt;
    for (const auto &line : lines)
    {
        smatch matches;
        bool is_command = regex_match(line, matches, cmd_regex);

        if (!dir.has_value())
        {
            if (!is_command || matches.size() < 1)
            {
                cout << "Expected a command next\n";
                exit(1);
            }

            if (regex_search(line, is_cd))
            {
                dir.emplace(process_dir(matches[0]));
            }
        }
    }

    return Dir("name");
}

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    Item root = get_tree(lines);
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
