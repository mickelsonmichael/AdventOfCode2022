# Day 6: Tuning Trouble

First notable thing for this day, before I even start, is that there are multiple examples. This doesn't mesh perfectly with my makefile but it's still more than manageable. I'll just have to run the commands manually.

This one was reasonably trivial to solve, but I definitely didn't do it the most efficiently. I had several nested loops, which made it easier to write but much less efficient than doing it with direct index access and just comparing 14 items. I find that on these solutions I like to strike a balance between quick solutions and _reusable_ solutions. I want my solutions to be solvable with anyone's input and be extensible if the input parameters were to ever change. I realize this is a fruitless exercise, but it's good practice, in my opinion, on how to think about things in a re-usable manner.

As always, I try to follow the SOLID principles, but could probably afford to do it a little more intensely.
