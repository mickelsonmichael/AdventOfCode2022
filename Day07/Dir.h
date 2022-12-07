#ifndef DIR_H
#define DIR_H

#include <vector>

#include "Item.h"

class Dir : public Item
{

private:
    std::vector<Item> items;

public:
    Dir(const std::string &name);
    std::vector<Item> get_items() const;
    void add(Item item);
    int size() const override;
    std::string str() const override;
};

#endif