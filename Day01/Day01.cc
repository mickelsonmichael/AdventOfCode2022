#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

void solve(char *fileName)
{
    fstream filestream(fileName);

    if (!filestream.is_open())
    {
        exit(1);
    }

    string line;
    vector<int> elfTotal;
    vector<int> currentElfTotal;
    while (getline(filestream, line))
    {
        if (line.length() == 0)
        {
            int thisTotal = 0;
            for (int amt : currentElfTotal)
            {
                thisTotal += amt;
            }
            elfTotal.push_back(thisTotal);

            cout << "Elf totaled " << thisTotal << " Calories\n";

            currentElfTotal.clear();

            continue;
        }

        int amt = stoi(line);

        currentElfTotal.push_back(amt);
    }

    int thisTotal = 0;
    for (int amt : currentElfTotal)
    {
        thisTotal += amt;
    }
    elfTotal.push_back(thisTotal);
    cout << "Final elf totaled " << thisTotal << " Calories\n";

    vector<int> maxes(3);
    fill(maxes.begin(), maxes.end(), 0);

    for (int calories : elfTotal) {
        if (maxes[0] == 0) {
            maxes[0] = calories;
            continue;;
        }

        if (calories > maxes[0]) {
            maxes[0] = calories;
        }

        sort(maxes.begin(), maxes.end());
    }

    int total = 0;
    for (int max : maxes) {
        total += max;
    }

    cout << "The three elves with the most calories have " << total << endl; 
}

int main(int argv, char **argc)
{
    if (argv != 2)
    {
        cout << "You gotta give me a file" << endl;

        return 1;
    }

    char *fileName = argc[1];

    cout << "Parsing file " << fileName << endl;

    solve(fileName);

    return 0;
}
