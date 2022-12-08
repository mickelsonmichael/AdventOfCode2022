#ifndef TREE_H
#define TREE_H

#include <optional>
#include <regex>
#include <vector>

#include "Dir.cpp"

class Tree
{
private:
    Dir _root;
    Dir *_current;

public:
    Tree();
    void ls(const std::vector<std::string> &lines);
    void cd(const std::string &dest);
};

#endif
