#include <string>
#include "Item.h"

Item::Item(std::string name) : name(name){}

std::string Item::get_name() const
{
    return name;
}

int Item::size() const
{
    return 0;
}
