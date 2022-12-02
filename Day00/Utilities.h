#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::string> getAllLines(char* fileName);

std::vector<std::string> readFile(int argc, char** argv);

bool isPart2(int argc, char** argv);

#endif