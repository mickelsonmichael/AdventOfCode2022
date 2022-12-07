#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{

private:
    const std::string name;

public:
    Item(std::string name);
    std::string get_name() const;
    virtual int size() const;
    virtual std::string str() const;
};

#endif