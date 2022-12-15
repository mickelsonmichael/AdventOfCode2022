#include <iostream> // SIZE_MAX
#include <utility>  // pair

class Node
{
private:
    bool _visited = false;
    size_t _distance;

public:
    const size_t row;
    const size_t col;
    // Node(const Node &n) = delete;
    Node(const size_t &r, const size_t &c)
        : _distance(SIZE_MAX), row(r), col(c)  {}
    Node(const size_t &r, const size_t &c, const size_t &d)
        : _distance(d), row(r), col(c) {}

    bool is_visited() const
    {
        return _visited;
    }
    void visit()
    {
        _visited = true;
    }
    size_t distance() const
    {
        return _distance;
    }
    void set_distance(const size_t &d)
    {
        _distance = d;
    }
};