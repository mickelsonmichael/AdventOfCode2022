#ifndef FILE_H
#define FILE_H

#include <string>

#include "Item.h"

class File : public Item
{
private:
    int _size;

public:
    File(std::string name, int size);
    int size() const override;
    std::string str() const override;
};

#endif