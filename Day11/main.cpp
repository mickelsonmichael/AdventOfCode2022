#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "utils.h"
#include "monkey.cpp"

using namespace std;

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";
    const function<long long(long long)> relief = [](long long old) { return old / 3; };

    vector<Monkey> monkeys;

    for (size_t i = 0; i < lines.size(); i += 7)
    {
        const vector<string> subset(lines.begin() + i, lines.begin() + i + 6);

        monkeys.push_back(parse_monkey(subset));
    }

    for (size_t round = 1; round <= 20; ++round)
    {
        for (auto &monkey : monkeys)
        {
            for (auto act : monkey.throw_items(relief))
            {
                monkeys[act.second].catch_item(act);
            }
        }
    }

    size_t top = 0;
    size_t second = 0;
    
    for (auto &monkey : monkeys)
    {
        cout << "Monkey " << monkey.id() << " inspected " << monkey.num_inspections() << " times\n";

        size_t n = monkey.num_inspections();
        if (n > top)
        {
            second = top;
            top = n;
            continue;
        }

        if (n > second)
        {
            second = n;
            continue;
        }
    }

    cout << "The top monkeys inspected " << top << " and " << second
        << " times. Resulting in a level of " << top * second << " monkey business\n";
}

void solvePart2(const vector<string> &lines)
{
    cout << "Solving part 2\n";


    vector<Monkey> monkeys;

    for (size_t i = 0; i < lines.size(); i += 7)
    {
        const vector<string> subset(lines.begin() + i, lines.begin() + i + 6);

        monkeys.push_back(parse_monkey(subset));
    }

    int common_multiple = 1;
    for (auto &monkey : monkeys)
    {
        common_multiple *= monkey.get_test();
    }

    cout << "Using common multiple " << common_multiple << '\n';

    const function<long long(long long)> relief = [common_multiple](long long old) { return old % common_multiple; };

    for (size_t round = 1; round <= 10000; ++round)
    {
        for (auto &monkey : monkeys)
        {
            for (auto act : monkey.throw_items(relief))
            {
                monkeys[act.second].catch_item(act);
            }
        }

        // cout << "== After round " << round << " ==\n";

        // for (auto &monkey : monkeys)
        // {
        //     cout << "Monkey " << monkey.id() << " inspected items " << monkey.num_inspections() << " times.\n";
        // }

        // cout << '\n';
    }

    size_t top = 0;
    size_t second = 0;
    
    for (auto &monkey : monkeys)
    {
        cout << "Monkey " << monkey.id() << " inspected " << monkey.num_inspections() << " times\n";

        size_t n = monkey.num_inspections();
        if (n > top)
        {
            second = top;
            top = n;
            continue;
        }

        if (n > second)
        {
            second = n;
            continue;
        }
    }

    cout << "The top monkeys inspected " << top << " and " << second
        << " times. Resulting in a level of " << top * second << " monkey business\n";
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);

    isPart2(argc, argv)
        ? solvePart2(lines)
        : solvePart1(lines);
}
