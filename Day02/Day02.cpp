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

#define OPP_TO_SELF 23

#define SCORE_ROCK 1
#define SCORE_PAPER 2
#define SCORE_SCISSORS 3

#define SCORE_LOSE 0
#define SCORE_TIE 3
#define SCORE_WIN 6

#define SHOULD_LOSE 'X'
#define SHOULD_TIE 'Y'
#define SHOULD_WIN 'Z'

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
        cout << "Unable to get points for choice" << choice << endl;
        exit(1);
    }
}

int getPart1Outcome(char opponent, char self)
{
    int outcome = 0;

    if ((self - OPP_TO_SELF) == opponent)
    {
        outcome = SCORE_TIE;
    }
    else
    {
        switch (opponent)
        {
        case OPP_ROCK:
            outcome = self == SELF_PAPER ? SCORE_WIN : SCORE_LOSE;
            break;
        case OPP_PAPER:
            outcome = self == SELF_SCISSORS ? SCORE_WIN : SCORE_LOSE;
            break;
        case OPP_SCISSORS:
            outcome = self == SELF_ROCK ? SCORE_WIN : SCORE_LOSE;
            break;
        default:
            outcome = SCORE_TIE;
            break;
        }
    }

    return outcome + getChoicePoints(self);
}

int getPart2Outcome(char opponent, char desired_outcome)
{
    if (desired_outcome == SHOULD_TIE)
    {
        return SCORE_TIE + getChoicePoints(opponent + OPP_TO_SELF);
    }

    bool win = desired_outcome == SHOULD_WIN;
    char choice = 'X';

    switch (opponent)
    {
        case OPP_ROCK:
            choice = win ? SELF_PAPER : SELF_SCISSORS;
            break;
        case OPP_PAPER:
            choice = win ? SELF_SCISSORS : SELF_ROCK;
            break;
        case OPP_SCISSORS:
            choice = win ? SELF_ROCK : SELF_PAPER;
            break;
        default:
            cout << "unexpected outcome" << endl;
            exit(1);
    }

    return getChoicePoints(choice) + (win ? SCORE_WIN : SCORE_LOSE);
}

int calculateRoundWithStrategyGuide(string line)
{
    char opponent_move = line.substr(0, line.find(" ")).c_str()[0];
    char rhs = line.substr(line.find(" ") + 1, 1).c_str()[0];

    // int outcome = getPart1Outcome(opponent_move, rhs);
    int outcome = getPart2Outcome(opponent_move, rhs);

    return outcome;
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
