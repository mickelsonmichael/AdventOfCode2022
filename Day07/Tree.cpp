#include <iostream>
#include <vector>
#include <regex>

#include "Dir.cpp"
#include "Tree.h"

Tree::Tree() : _root("/", nullptr), _current(&_root)
{
}

Dir* Tree::current() const
{
    return _current;
}

Dir Tree::root() const
{
    return _root;
}

void Tree::cd(const std::string &dest)
{
    // std::cout << "Changing directory to " << dest << '\n';

    if (dest == "..")
    {
        // std::cout << "\tMoving to parent dir\n";

        _current = _current->parent();

        // std::cout << "\t\tNew dir: " << _current->name() << '\n';

        return;
    }

    for (auto &child : _current->children())
    {
        if (child.name() == dest)
        {
            _current = &child;

            return;
        }
    }
}

void Tree::ls(const std::vector<std::string> &lines)
{
    const std::regex pattern("(dir|[0-9]+) (.*)");

    std::smatch matches;
    // std::cout << "Adding files to " << (_current->name()) << '\n';

    for (auto line : lines)
    {
        if (!std::regex_match(line, matches, pattern) || matches.size() != 3)
        {
            std::cout << "INVALID OUTPUT: " << line << " (" << matches.size() << ")" << '\n';
            exit(1);
        }

        if (matches[1] == "dir")
        {
            // std::cout << "\tAdding directory " << matches[2] << '\n';

            Dir newDir(matches[2], _current);

            _current->add(newDir);
        }
        else
        {
            // std::cout << "\tAdding " << stoi(matches[1]) << " byte file " << matches[2] << " to " << _current->name() << '\n';

            _current->add(matches[2], stoi(matches[1]));
        }
    }

    // std::cout << _current->name() << " now has " << _current->children().size() << " children and "
    //           << _current->size() << " bytes worth of files\n";
}
