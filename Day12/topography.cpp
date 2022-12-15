#include <vector>
#include <utility>
#include <list>
#include <algorithm>

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

    size_t steps_to_optimal_signal() const
    {
        vector<size_t> distances(_row_size * _col_size);
        vector<size_t> previous_distances(_row_size * _col_size);

        vector<Node> nodes;
        Node *current_node;

        for (size_t r = 0; r < _grid.size(); ++r)
        {
            for (size_t c = 0; c < _grid[r].size(); ++c)
            {
                bool start = is_start(r, c);
                size_t idx = (r * _row_size) + _col_size;

                Node n(r, c, start ? 0 : SIZE_MAX);

                nodes.push_back(n);
            }
        }

        for (auto &this_node : nodes)
        {
            cout << "[" << this_node.row << ", " << this_node.col
                << "] ";

            if (this_node.col == _col_size - 1)
            {
                cout << '\n';
            }

            if (is_start(this_node.row, this_node.col))
            {
                current_node = &this_node;
            }
        }

        auto find_node = [nodes](const size_t &r, const size_t &c)
        {
            auto ptr = find_if(
                nodes.begin(),
                nodes.end(),
                [r, c](Node n)
                { return n.row == r && n.col == c; });

            // get rid of the constness provided by find
            const Node *node = &(*ptr);

            return const_cast<Node *>(node);
        };

        cout << "Grid is a " << _row_size << " by " << _col_size << '\n';

        while (current_node != nullptr)
        {
            cout << "Visiting node: [" << current_node->row
                 << ", " << current_node->col
                 << "] -> (d=" << current_node->distance() << ")\n";

            current_node->visit();

            // if we've reached the destination at the shortest path already
            // we can stop early
            if (is_end(*current_node))
            {
                bool is_smallest = true;
                for (const auto &other_node : nodes)
                {
                    if (other_node.distance() < current_node->distance())
                    {
                        is_smallest = false;
                        break;
                    }
                }

                if (is_smallest)
                {
                    return current_node->distance();
                }
            }

            auto update_distance = [nodes, current_node](Node *&other)
            {
                size_t d = current_node->distance() + 1;

                if (d < other->distance())
                {
                    other->set_distance(d);
                }
            };

            cout << "\t- Visiting nodes...\n";

            // UP
            if (current_node->row < _row_size - 1)
            {
                auto up = find_node(current_node->row + 1, current_node->col);

                cout << "\t- Up: " << up->row
                     << ", " << up->col
                     << "(d=" << up->distance() << ")\n";

                update_distance(up);
            }

            // DOWN
            if (current_node->row > 0)
            {
                cout << "Getting the down with the sickness\n";

                auto down = find_node(current_node->row - 1, current_node->col);

                cout << "\t- Down: " << down->row
                     << ", " << down->col
                     << "(d=" << down->distance() << ")\n";

                update_distance(down);
            }

            // LEFT
            if (current_node->col > 0)
            {
                auto left = find_node(current_node->row, current_node->col - 1);

                cout << "\t- Left: " << left->row
                     << ", " << left->col
                     << "(d=" << left->distance() << ")\n";

                update_distance(left);
            }

            // RIGHT
            if (current_node->col < _col_size - 1)
            {
                auto right = find_node(current_node->row, current_node->col + 1);

                cout << "\t- Right: " << right->row
                     << ", " << right->col
                     << "(d=" << right->distance() << ")\n";

                update_distance(right);
            }

            current_node = nullptr;
            for (auto &n : nodes)
            {
                if (n.is_visited())
                {
                    continue;
                }

                if (current_node == nullptr || n.distance() < current_node->distance())
                {
                    current_node = &n;

                    continue;
                }
            }
        }

        for (const auto &n : nodes)
            if (is_end(n))
                return n.distance();

        cout << "Unable to find shortest route!\n";
        exit(1);
    }
};
