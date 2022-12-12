#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <set>

#include "utils.h"

using namespace std;

class Rope
{
private:
    vector<pair<int, int>> _knots;
    pair<int, int> head;
    set<pair<int, int>> visited;

    void move_head(const char &dir)
    {
        switch (dir)
        {
        case 'R':
            head.first += 1;
            break;
        case 'L':
            head.first -= 1;
            break;
        case 'U':
            head.second += 1;
            break;
        case 'D':
            head.second -= 1;
            break;
        default:
            cout << "ERROR: Invalid direction (" << dir << ")\n";
            exit(1);
            break;
        }
    }

    bool is_too_far_y(const pair<int, int> &a, const pair<int, int> &b) const
    {
        return abs(a.second - b.second) > 1;
    }

    bool is_too_far_x(const pair<int, int> &a, const pair<int, int> &b) const
    {
        return abs(a.first - b.first) > 1;
    }

    void move_knots()
    {
        for (size_t n = 0; n < _knots.size(); ++n)
        {
            auto &knot = _knots[n];
            const auto &ahead = n == 0 ? head : _knots[n - 1];

            while (is_too_far_x(knot, ahead))
            {
                knot.first += ahead.first > knot.first ? 1 : -1;

                if (abs(ahead.second - knot.second) > 0)
                {
                    knot.second += ahead.second > knot.second ? 1 : -1;
                }
            }

            while (is_too_far_y(knot, ahead))
            {
                knot.second += ahead.second > knot.second ? 1 : -1;

                if (abs(ahead.first - knot.first) > 0)
                {
                    knot.first += ahead.first > knot.first ? 1 : -1;
                }
            }

            if (n == _knots.size() - 1)
            {
                visited.insert(knot);
            }
        }
    }

public:
    Rope(const size_t num_knots) : _knots(num_knots),
                                   head(pair<int, int>(0, 0)),
                                   visited()
    {
        visited.insert(pair<int, int>(0, 0));

        // print();
    }

    void print() const
    {
        for (int y = 4; y >= 0; --y)
        {
            for (int x = 0; x < 6; ++x)
            {
                if (head.first == x && head.second == y)
                {
                    cout << 'H';
                    continue;
                }

                char c = '.';
                for (size_t k = 0; k < _knots.size(); ++k)
                {
                    if (_knots[k].first == x && _knots[k].second == y)
                    {
                        c = k + '1';
                        break;
                    }
                }

                if (c == '.')
                {
                    for (auto v : get_visited())
                    {
                        if (v.first == x && v.second == y)
                        {
                            c = '#';
                            break;
                        }
                    }
                }

                cout << c;
            }
            cout << '\n';
        }
        cout << '\n';
    }

    void move(const char &dir, const int &n)
    {
        for (int move_num = 1; move_num <= n; ++move_num)
        {
            move_head(dir);

            move_knots();

            // print();
        }
    }

    set<pair<int, int>> get_visited() const
    {
        return visited;
    }
};

vector<pair<char, int>> get_moves(const vector<string> &lines)
{
    const regex pattern("^([RULD]) ([0-9]+)");

    vector<pair<char, int>> result;

    smatch matches;
    for (const string &line : lines)
    {
        if (!regex_match(line, matches, pattern))
        {
            cout << "ERROR: Unable to match move: " << line << endl;
            exit(1);
        }

        const char c = matches[1].str()[0];
        const int n = stoi(matches[2]);

        result.push_back(pair<char, int>(c, n));
    }

    return result;
}

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    Rope rope(1);

    for (auto move : get_moves(lines))
    {
        rope.move(move.first, move.second);
    }

    cout << "The tail moved to " << rope.get_visited().size() << " spots\n";
}

void solvePart2(const vector<string> &lines)
{
    cout << "Solving part 2\n";

    Rope rope(9);

    for (auto move : get_moves(lines))
    {
        rope.move(move.first, move.second);
    }

    cout << "The tail moved to " << rope.get_visited().size() << " spots\n";
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);

    isPart2(argc, argv)
        ? solvePart2(lines)
        : solvePart1(lines);
}
