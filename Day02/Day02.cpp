#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#include "Utilities.h"

using namespace std;

#define OPP_ROCK 'A'
#define OPP_PAPER 'B'
#define OPP_SCISSORS 'C'
#define SELF_ROCK 'X'
#define SELF_PAPER 'Y'
#define SELF_SCISSORS 'Z'
#define SCORE_ROCK 1
#define SCORE_PAPER 2
#define SCORE_SCISSORS 3
#define SCORE_LOSE 0
#define SCORE_TIE 3
#define SCORE_WIN 6

int getStrategyGuideOutcome(char opponent, char self)
{
    if ((self - 23) == opponent)
    {
        return SCORE_TIE;
    }

    switch (opponent)
    {
    case OPP_ROCK:
        return self == SELF_PAPER ? SCORE_WIN : SCORE_LOSE;
    case OPP_PAPER:
        return self == SELF_SCISSORS ? SCORE_WIN : SCORE_LOSE;
    case OPP_SCISSORS:
        return self == SELF_ROCK ? SCORE_WIN : SCORE_LOSE;
    default:
        return SCORE_TIE;
    }
}

int getChoicePoints(char choice)
{
    switch (choice)
    {
        case SELF_ROCK:
            return SCORE_ROCK;
        case SELF_PAPER:
            return SCORE_PAPER;
        case SELF_SCISSORS:
            return SCORE_SCISSORS;
        default:
            cout << "Unable to get points for choice" << endl;
            return 0;
    }
}

int calculateRoundWithStrategyGuide(string line)
{
    char opponent_move = line.substr(0, line.find(" ")).c_str()[0];
    char my_move = line.substr(line.find(" ") + 1, 1).c_str()[0];

    int outcome = getStrategyGuideOutcome(opponent_move, my_move);
    int choice = getChoicePoints(my_move);

    return outcome + choice;
}

void solve(vector<string> input)
{
    vector<int> scores(input.size());

    for (string s : input)
    {
        int outcome = calculateRoundWithStrategyGuide(s);

        scores.push_back(outcome);
    }
    
    int sum = accumulate(scores.begin(), scores.end(), 0);

    cout << "Total score: " << sum << endl;
}

int main(int argc, char **argv)
{
    vector<string> lines = readFile(argc, argv);

    solve(lines);
}
