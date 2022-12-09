#ifndef DIR_H
#define DIR_H

#include <string>
#include <vector>
#include <iostream>

class Dir
{
private:
    std::vector<Dir> _children;
    double _size;
    Dir *_parent;
    std::string _name;

public:
    Dir(std::string n, Dir *parent)
        : _children(),
          _size(0),
          _parent(parent),
          _name(n){};
    std::vector<Dir>& children()
    {
        return _children;
    }
    void add(Dir child)
    {
        _children.push_back(child);
    }
    void add(std::string name, int sz)
    {
        _size += sz;
    }
    int size() const
    {
        int total_size = _size;

        for (auto child : _children)
        {
            total_size += child.size();
        }

        return total_size;
    }
    std::string name() const
    {
        return _name;
    }
    bool is_root() const
    {
        return _parent == nullptr;
    }
    Dir *parent()
    {
        return _parent;
    }
};

#endif