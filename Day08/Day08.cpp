#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

vector<vector<size_t>> get_tree_grid(const vector<string> &lines)
{
    vector<vector<size_t>> rows;

    for (const auto &line : lines)
    {
        vector<size_t> cols;

        for (const char &c : line)
        {
            const size_t height = c - '0';

            cols.push_back(height);
        }

        rows.push_back(cols);
    }

    return rows;
}

void solvePart1(const vector<string> &lines)
{
    cout << "Solving part 1\n";

    const vector<vector<size_t>> trees = get_tree_grid(lines);

    size_t visible_trees = 0;
    for (size_t row_num = 0; row_num < trees.size(); ++row_num)
    {
        vector<size_t> row = trees[row_num];

        if (row_num == 0 || row_num == row.size() - 1)
        {
            visible_trees += row.size();

            continue;
        }

        for (size_t col_num = 0; col_num < row.size(); ++col_num)
        {
            if (col_num == 0 || col_num == row.size() - 1)
            {
                visible_trees += 1;

                continue;
            }

            const size_t this_tree = row[col_num];

            bool is_visible = true;
            for (size_t i = 0; i < row_num && is_visible; ++i)
            {
                is_visible = trees[i][col_num] < this_tree;
            }

            if (is_visible)
            {
                visible_trees += 1;
                continue;
            }

            is_visible = true;
            for (size_t i = row_num + 1; i < trees.size() && is_visible; ++i)
            {
                is_visible = trees[i][col_num] < this_tree;
            }

            if (is_visible)
            {
                visible_trees += 1;
                continue;
            }

            is_visible = true;
            for (size_t j = 0; j < col_num && is_visible; ++j)
            {
                is_visible = row[j] < this_tree;
            }

            if (is_visible)
            {
                visible_trees += 1;
                continue;
            }

            is_visible = true;
            for (size_t j = col_num + 1; j < row.size() && is_visible; ++j)
            {
                is_visible = row[j] < this_tree;
            }

            if (is_visible)
            {
                visible_trees += 1;
                continue;
            }
        }
    }

    cout << "There are " << visible_trees << " visible trees" << endl;
}

size_t get_scenic_score(const size_t &up, const size_t &down, const size_t &left, const size_t &right)
{
    return up * down * left * right;
}

void solvePart2(const vector<string> &lines)
{
    cout << "Solving part 2\n";

    const vector<vector<size_t>> trees = get_tree_grid(lines);

    size_t max = 0;
    for (size_t row_num = 0; row_num < trees.size(); ++row_num)
    {
        for (size_t col_num = 0; col_num < trees[row_num].size(); ++col_num)
        {
            const size_t this_tree = trees[row_num][col_num];

            // UP
            size_t up = 0;
            for (int i = row_num - 1; i >= 0; --i)
            {
                up += 1;

                if (trees[i][col_num] >= this_tree)
                {
                    break;
                }
            }

            // DOWN
            size_t down = 0;
            for (int i = row_num + 1; i < trees.size(); ++i)
            {
                down += 1;
                if (trees[i][col_num] >= this_tree)
                {
                    break;
                }
            }

            // LEFT
            size_t left = 0;
            for (int i = col_num - 1; i >= 0; --i)
            {
                left += 1;

                if (trees[row_num][i] >= this_tree)
                {
                    break;
                }
            }

            // RIGHT
            size_t right = 0;
            for (int i = col_num + 1; i < trees[row_num].size(); ++i)
            {
                right += 1;

                if (trees[row_num][i] >= this_tree)
                {
                    break;
                }
            }

            const size_t score = get_scenic_score(up, down, left, right);

            // cout << "INFO: (" << row_num << ", " << col_num << ")"
            //      << " got a score of " << score
            //      << "\n\tup: " << up
            //      << "\n\tright: " << right
            //      << "\n\tdown: " << down
            //      << "\n\tleft: " << left
            //      << '\n';

            if (score > max)
            {
                max = score;
            }
        }
    }

    cout << "The highest possible scenic score is " << max << endl;
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);

    isPart2(argc, argv)
        ? solvePart2(lines)
        : solvePart1(lines);
}
