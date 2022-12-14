# Day 10: Cathode-Ray Tube

I'm four days behind while solving this one, so I'm hoping it goes quickly.
My goal is to finish this year, but I don't know if I can do that if I keep procrastinating over the weekend.

Another misunderstanding for part 1 today. I interpreted the cycles as overlapping CPU cycles, rather than just taking two steps.
So I was carrying over a `next` variable that would be the value added at the next iteration.
That could mean during an `addx` or `noop`, the result of the previous instruction would be executed.
In reality, I was just able to do a simple `next()` twice, and add the register in between.
A lot simpler, but a lot less engaging.
Here's hoping part 2 is a bit more challenging.

Part 2 was alright. I had a slight mistake with a modulo calculation, but otherwise everything went smoothly.
