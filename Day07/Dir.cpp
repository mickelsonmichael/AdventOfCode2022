#ifndef DIR_H
#define DIR_H

#include <string>
#include <vector>
#include <iostream>

class Dir
{
private:
    std::vector<Dir> _children;
    std::vector<std::string> _filenames;
    double _size;
    const Dir *_parent;
    const std::string _name;

public:
    Dir(const std::string &name, const Dir *parent) : _children(), _filenames(), _size(0), _parent(parent), _name(name){};
    std::vector<Dir> children() const
    {
        return _children;
    }
    void add(Dir child)
    {
        _children.push_back(child);
    }
    void add(const std::string &name, const int &sz)
    {
        _filenames.push_back(name);
        _size += sz;
    }
    int size() const
    {
        return _size;
    }
    std::string name() const
    {
        return _name;
    }
    bool is_root() const
    {
        return _parent == nullptr;
    }
};

#endif