#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "Item.h"
#include "Dir.h"

Dir::Dir(const std::string &name) : Item{name}, items() {}

std::vector<Item> Dir::get_items() const
{
    return std::vector<Item>(items);
}

void Dir::add(Item item)
{
    items.push_back(item);
}

int Dir::size() const
{
    int sz = 0;

    for (Item item : items)
    {
        sz += item.size();
    }

    return sz;
}

std::string Dir::str() const
{
    std::stringstream ss;

    ss << "- " << get_name() << " (dir)\n";

    for (const auto it : get_items())
    {
        ss << "\t" << it.str();
    }

    return ss.str();
}
