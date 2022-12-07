#ifndef CMD_H
#define CMD_H

#include <iterator>
#include <string>
#include <vector>

enum CommandType
{
    cd,
    ls
};

class Command
{
private:
    const std::vector<std::string> args;
    const std::vector<std::string> output;
public:
    const CommandType type;
    Command(const std::string &str);
    const std::size_t size() const
    {
        return args.size();
    }
    const std::string &operator[](std::size_t i) const
    {
        return args[i];
    }
    auto begin() const
    {
        return output.begin();
    }
    auto end() const
    {
        return output.end();
    }
};

#endif
