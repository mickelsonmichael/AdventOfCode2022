#include <vector>
#include <utility>
#include <list>
#include <algorithm>
#include <queue>
#include <optional>

#include "node.cpp"

#define CURRENT_POSITION 'S'
#define BEST_SIGNAL 'E'

using namespace std;

class Topography
{
private:
    vector<vector<char>> _grid;
    size_t _row_size = 0;
    size_t _col_size = 0;
    pair<size_t, size_t> _current;
    pair<size_t, size_t> _target;

    bool can_move(const pair<size_t, size_t> &from, const pair<size_t, size_t> &to) const
    {
        return can_move(from.first, from.second, to.first, to.second);
    }

    bool can_move(const Node &from, const Node &to) const
    {
        return can_move(from.row, from.col, to.row, to.col);
    }

    bool can_move(
        const size_t &r1,
        const size_t &c1,
        const size_t &r2,
        const size_t &c2) const
    {
        return abs(_grid[r1][c1] - _grid[r2][c2]) < 1;
    }

    bool is_end(const Node &n) const
    {
        return n.row == _target.first && n.col == _target.second;
    }

    bool is_start(const size_t &r, const size_t &c) const
    {
        return r == _current.first && c == _current.second;
    }

public:
    Topography(const vector<string> &lines) : _grid()
    {
        _row_size = lines.size();

        string ln;
        for (size_t r = 0; r < _row_size; ++r)
        {
            ln = lines[r];

            if (_col_size == 0)
            {
                _col_size = ln.size();
            }

            vector<char> row;
            for (size_t c = 0; c < ln.size(); ++c)
            {
                row.push_back(ln[c]);

                if (ln[c] == CURRENT_POSITION)
                {
                    _current = pair<size_t, size_t>(r, c);
                }

                if (ln[c] == BEST_SIGNAL)
                {
                    _target = pair<size_t, size_t>(r, c);
                }
            }

            _grid.push_back(row);
        }
    }

    size_t get_index(const size_t &r, const size_t &c)
    {
        return (r * _row_size) + c;
    }

    size_t steps_to_optimal_signal() const
    {
        vector<size_t> distances(_row_size * _col_size, SIZE_MAX);
        distances[(_row_size * _current.first) + _current.second] = 0;

        vector<pair<size_t, size_t>> to_visit;
        for (size_t r = 0; r < _grid.size(); ++r)
            for (size_t c = 0; c < _grid[r].size(); ++c)
                to_visit.push_back(pair<size_t, size_t>(r, c));

        const size_t num_rows = _row_size;
        while (!to_visit.empty())
        {
            auto current = min_element(
                to_visit.begin(),
                to_visit.end(),
                [distances, num_rows](const pair<size_t, size_t> &lhs, const pair<size_t, size_t> &rhs)
                {
                    return distances[(num_rows * lhs.first) + lhs.second] < distances[(num_rows * rhs.first) + rhs.second]; 
                }
            );

            to_visit.erase(current, current + 1); // remove from the queue

            const size_t row = current->first;
            const size_t col = current->second;
            const size_t idx = (row * _row_size) + col;
            const size_t d = distances[idx] + 1;

            cout << "Visiting [" << row << ", " << col << "] (d=" << distances[idx] << ")\n";

            // UP
            if (row < _row_size - 1)
            {
                const size_t up_dx = ((row + 1) * _row_size) + col;

                if (d < distances[up_dx])
                {
                    distances[up_dx] = d;
                }
            }

            // DOWN
            if (row > 0)
            {
                const size_t down_idx = ((row - 1) * _row_size) + col;

                if (d < distances[down_idx])
                {
                    distances[down_idx] = d;
                }
            }

            // RIGHT
            if (col < _col_size - 1)
            {
                const size_t right_idx = (row  * _row_size) + col + 1;

                if (d < distances[right_idx])
                {
                    distances[right_idx] = d;
                }
            }

            // LEFT
            if (col > 0)
            {
                const size_t left_idx = (row  * _row_size) + col - 1;

                if (d < distances[left_idx])
                {
                    distances[left_idx] = d;
                }
            }
        }

        const size_t end_idx = (_row_size * _target.first) + _target.second;

        return distances[end_idx];
    }
};
