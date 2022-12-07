#include <iostream>
#include <sstream>

#include "Item.h"
#include "File.h"

File::File(std::string name, int size) : Item{name}, _size(size) {}

int File::size() const
{
    return _size;
}

std::string File::str() const
{
    std::stringstream ss;

    ss << "- " << get_name() << " (file, size=" << size() << ")\n";

    return ss.str();
}
