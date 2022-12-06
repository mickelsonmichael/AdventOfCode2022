#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

#define MIN 0
#define MAX 1
#define RANGE 2

#define LEFT 0
#define RIGHT 1
#define LARGER 2
#define EQUAL 3

using namespace std;

vector<int> getRange(const string &range)
{
    const auto dash_indx = range.find('-');

    vector<int> result(3);

    result[MIN] = stoi(range.substr(0, dash_indx));
    result[MAX] = stoi(range.substr(dash_indx + 1));
    result[RANGE] = result[MAX] - result[MIN];

    return result;
}

vector<vector<int>> getRanges(const string &line)
{
    const auto comma_indx = line.find(',');

    string left = line.substr(0, comma_indx);
    string right = line.substr(comma_indx + 1);

    vector<vector<int>> result(3);

    result[LEFT] = getRange(left);
    result[RIGHT] = getRange(right);

    return result;
}

void solvePart1(vector<string> input)
{
    cout << "Solving part 1\n";

    size_t total_contained = 0;

    for (auto s : input)
    {
        vector<vector<int>> ranges = getRanges(s);

        // cout << ranges[LEFT][MIN] << "-" << ranges[LEFT][MAX]
        //      << " and "
        //      << ranges[RIGHT][MIN] << "-" << ranges[RIGHT][MAX];

        const int size_difference = (ranges[LEFT][RANGE]) - (ranges[RIGHT][RANGE]);

        if (!size_difference)
        {
            total_contained += (ranges[LEFT][MAX] == ranges[RIGHT][MAX]) ? 1 : 0;

            // cout << '\n';

            continue;
        }

        const bool leftIsBigger = size_difference > 0;

        // cout << (leftIsBigger ? "Left" : "Right") << " is bigger\n";

        const bool overlap = leftIsBigger
                                 ? (ranges[LEFT][MAX] >= ranges[RIGHT][MAX] && ranges[LEFT][MIN] <= ranges[RIGHT][MIN])
                                 : (ranges[RIGHT][MAX] >= ranges[LEFT][MAX] && ranges[RIGHT][MIN] <= ranges[LEFT][MIN]);

        // cout << (overlap ? "*" : "") << '\n';

        total_contained += overlap ? 1 : 0;
    }

    cout << "Total overlapped: " << total_contained << endl;
}

void solvePart2(vector<string> input)
{
    cout << "Solving part 2\n";

    vector<bool> covered;
    size_t overlap = 0;

    for (string s : input)
    {
        vector<vector<int>> ranges = getRanges(s);

        // cout << ranges[LEFT][MIN] << "-" << ranges[LEFT][MAX]
        //      << " and "
        //      << ranges[RIGHT][MIN] << "-" << ranges[RIGHT][MAX];

        // Left wraps around right max
        if (ranges[LEFT][MAX] >= ranges[RIGHT][MAX] && ranges[LEFT][MIN] <= ranges[RIGHT][MAX])
        {
            overlap += 1;

            continue;
        }

        // Left wraps around right min
        if (ranges[LEFT][MAX] >= ranges[RIGHT][MIN] && ranges[LEFT][MIN] <= ranges[RIGHT][MIN])
        {
            overlap += 1;

            continue;
        }

        // Right wraps around left max
        if (ranges[RIGHT][MAX] >= ranges[LEFT][MAX] && ranges[RIGHT][MIN] <= ranges[LEFT][MAX])
        {
            overlap += 1;

            continue;
        }

        // Right wraps around left min
        if (ranges[RIGHT][MAX] >= ranges[LEFT][MIN] && ranges[RIGHT][MIN] <= ranges[LEFT][MIN])
        {
            overlap += 1;

            continue;
        }
    }

    cout << "Number of overlaps: " << overlap << '\n';
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);
    bool part2 = isPart2(argc, argv);

    part2 ? solvePart2(lines) : solvePart1(lines);
}
