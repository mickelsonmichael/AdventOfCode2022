#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

#include "Utilities.h"

#define PART_1_MARKER_SIZE 4
#define PART_2_MARKER_SIZE 14

using namespace std;

tuple<size_t, vector<char>> find_start(const vector<char> &signal, const size_t &marker_size)
{
    int index = -1;
    vector<char> chars(marker_size);

    for (size_t i = 0; i + marker_size - 1 < signal.size(); ++i)
    {
        bool match = false;

        for (size_t j = 0; j < marker_size; ++j)
        {
            const char c = signal[j + i];

            for (size_t x = 0; x < marker_size; ++x)
            {
                if (x == j)
                    continue;

                if (c == signal[x + i])
                {
                    match = true;
                    break;
                }
            }

            if (match)
            {
                break;
            }
        }

        if (!match)
        {
            index = i;
            for (size_t y = i; y < marker_size; ++y)
            {
                chars[y] = signal[y];
            }

            break;
        }
    }

    auto result = make_tuple(index, chars);

    return result;
}

vector<char> get_signal(const vector<string> &lines)
{
    if (lines.size() != 1)
    {
        cout << "Invalid input file, should be a single line." << endl;
        exit(1);
    }

    const string line_1 = lines[0];

    vector<char> result(line_1.begin(), line_1.end());

    return result;
}

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    const vector<char> signal = get_signal(lines);

    tuple<size_t, vector<char>> start_sequence = find_start(signal, PART_1_MARKER_SIZE);

    const vector<char> chars = get<1>(start_sequence);
    const size_t found_at = get<0>(start_sequence);

    cout << "Start signal found at: " << found_at + PART_1_MARKER_SIZE << endl;
}

void solvePart2(const vector<string> &lines)
{
    cout << "Solving part 2\n";

    const vector<char> signal = get_signal(lines);

    tuple<size_t, vector<char>> start_sequence = find_start(signal, PART_2_MARKER_SIZE);

    const vector<char> chars = get<1>(start_sequence);
    const size_t found_at = get<0>(start_sequence);

    cout << "Start signal found at: " << found_at + PART_2_MARKER_SIZE << endl;
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);

    isPart2(argc, argv)
        ? solvePart2(lines)
        : solvePart1(lines);
}
