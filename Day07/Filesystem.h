#ifndef FILE_H
#define FILE_H

#include <optional>
#include <regex>

#include "Item.h"
#include "Command.h"
#include "Dir.h"

class Filesystem
{
private:
    Dir _root;
    std::optional<Dir> _current = std::nullopt;
    Item *find(const std::string &name) const;
    const std::regex _details_pattern;

public:
    Filesystem() : _root("/"), _details_pattern("([A-Za-z0-9]+) ([A-Za-z0-9]+)"){};
    void run(Command cmd);
    void print() const;
};

#endif
