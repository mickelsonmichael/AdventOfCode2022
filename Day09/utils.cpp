#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define PART2 2

std::vector<std::string> getAllLines(char *fileName)
{
    std::fstream fs(fileName);

    if (!fs.is_open())
    {
        exit(1);
    }

    std::vector<std::string> result;

    std::string line;
    while (getline(fs, line))
    {
        // Remove the endline
        if (line.find('\r') == line.size() - 1)
        {
            line = line.substr(0, line.size() - 1);
        }

        result.push_back(line);
    }

    return result;
}

std::vector<std::string> readFile(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "You must provide a filename as the first argument" << std::endl;

        exit(1);
    }

    char *fileName = argv[1];

    std::cout << "Input file: " << fileName << std::endl;

    return getAllLines(fileName);
}

bool isPart2(int argc, char **argv)
{
    if (argc < 3)
    {
        return false;
    }

    return (argv[2][0] - '0') == PART2;
}
