#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <optional>
#include <deque>

#include "Dir.cpp"
#include "Tree.h"
#include "Utilities.h"

#define PART_1_THRESHOLD 100000
#define PART_2_UNUSED 30000000
#define PART_2_TOTAL 70000000

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

Tree process_tree(const vector<string> &lines)
{
    Tree files;

    for (auto it = lines.begin() + 1; it != lines.end(); ++it) // skip the first cd
    {
        string dest;
        if (try_get_cd(*it, &dest))
        {
            files.cd(dest);

            continue;
        }

        vector<string> output;
        while ((it + 1) != lines.end() && !is_cmd(*(it + 1))) // until the last line of output
        {
            ++it;

            string to_add(*it);

            output.push_back(to_add);
        }

        files.ls(output);
    }

    return files;
}

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    Tree files = process_tree(lines);

    Dir root = files.root();

    deque<Dir> to_scan = {root};
    double size = 0;
    do
    {
        Dir current = to_scan.front();
        to_scan.pop_front();

        if (current.size() <= PART_1_THRESHOLD)
        {
            size += current.size();
        }

        for (auto child : current.children())
        {
            to_scan.push_back(child);
        }
    } while (to_scan.size() > 0);

    cout << "Total size of files below " << PART_1_THRESHOLD << ": "
         << fixed << size << '\n';
}

void solvePart2(const vector<string> &lines)
{
    cout << "Solving part 2\n";

    Tree files = process_tree(lines);

    Dir root = files.root();
    double space_left = PART_2_TOTAL - root.size();
    vector<Dir> meets_requirement;

    deque<Dir> to_scan = {root};
    do
    {
        Dir current = to_scan.front();
        to_scan.pop_front();

        if (space_left + current.size() >= PART_2_UNUSED)
        {
            meets_requirement.push_back(current);
        }

        for (auto child : current.children())
        {
            to_scan.push_back(child);
        }
    } while (to_scan.size() > 0);

if (meets_requirement.size() < 1)
{
    cout << "WARN: No directories apparently meet the requirement\n";
    exit(1);
}

    Dir to_delete = meets_requirement[0];
    for (auto d : meets_requirement)
    {
        cout << "You could delete " << d.name() << " (" << d.size() << ")\n";

        if (d.size() < to_delete.size())
        {
            to_delete = d;
        }
    }

    cout << "You should delete " << to_delete.name() << " to save "
        << to_delete.size() << " bytes.\n";
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);

    isPart2(argc, argv)
        ? solvePart2(lines)
        : solvePart1(lines);
}
