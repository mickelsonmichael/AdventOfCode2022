#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

#include "Utilities.h"

#define A 65
#define Z 90

using namespace std;

vector<list<char>> get_layout(const vector<string> &lines, size_t *num_lines)
{
    *num_lines = 0;

    vector<list<char>> result;

    for (size_t i = 0; i < lines.size(); ++i)
    {
        *num_lines += 1;

        const string line = lines[i];

        if (line.find("[") == string::npos)
        {
            break;
        }

        int column = -1;

        for (size_t j = 0; j < line.size(); j += 4)
        {
            const char c = line[j + 1];

            ++column;

            if (c < A || c > Z)
            {
                continue;
            }

            for (int d_i = result.size() - 1; d_i < column; ++d_i)
            {
                list<char> ls;
                result.push_back(ls);
            }

            result[column].push_back(c);
        }
    }

    return result;
}

#define COUNT 0
#define SOURCE 1
#define DEST 2

vector<int> parse_move(const string &line)
{
    if (line.find("move") == string::npos)
    {
        cout << "line too short" << endl;
        exit(1);
    }

    vector<int> result(3);

    result[COUNT] = stoi(line.substr(line.find("move") + 5, 2));
    result[SOURCE] = stoi(line.substr(line.find("from") + 5, 2));
    result[DEST] = stoi(line.substr(line.find("to") + 3, 2));

    return result;
}

void solvePart1(const vector<string> &input)
{
    cout << "Solving part 1\n";

    size_t i;
    auto stacks = get_layout(input, &i);

    for (; i < input.size(); ++i)
    {

        const string line = input[i];

        if (line.find("move") == string::npos)
            continue;

        vector<int> move = parse_move(line);

        for (int n = 0; n < move[COUNT]; ++n)
        {
            stacks[move[DEST] - 1].push_front(stacks[move[SOURCE] - 1].front());

            stacks[move[SOURCE] - 1].pop_front();
        }
    }

    cout << "Top level containers: ";

    for (auto stack : stacks)
    {
        cout << stack.front();
    }

    cout << endl;
}

void solvePart2(const vector<string> &input)
{
    cout << "Solving part 2\n";

     size_t i;
    auto stacks = get_layout(input, &i);

    for (; i < input.size(); ++i)
    {

        const string line = input[i];

        if (line.find("move") == string::npos)
            continue;

        vector<int> move = parse_move(line);

        vector<char> to_move(move[COUNT]);
        for (int n = 0; n < move[COUNT]; ++n)
        {
            to_move[n] = stacks[move[SOURCE] - 1].front();

            stacks[move[SOURCE] - 1].pop_front();
        }

        reverse(to_move.begin(), to_move.end());

        for (char c : to_move)
        {
            stacks[move[DEST] - 1].push_front(c);
        }
    }

    cout << "Top level containers: ";

    for (auto stack : stacks)
    {
        cout << stack.front();
    }

    cout << endl;
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);
    bool part2 = isPart2(argc, argv);

    part2 ? solvePart2(lines) : solvePart1(lines);
}
