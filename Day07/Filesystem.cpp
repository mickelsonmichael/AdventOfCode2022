#include <iostream>

#include "Command.h"
#include "Filesystem.h"

void Filesystem::run(Command cmd)
{
    if (cmd.type == ls)
    {
        auto file = find(cmd[0]);

        Dir* dir = static_cast<Dir*>(file);

        for (auto output : cmd)
        {
            
        }
    }
}

void Filesystem::print() const
{
    std::cout << _root.str();
}
