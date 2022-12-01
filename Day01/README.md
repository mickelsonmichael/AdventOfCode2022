# Day 1: Calorie Counting

## Journal

I hastilyt crafted a dev container using Visual Studio Code in order to do some C++ compilation. I'm not sold on using C++ yet the entire time, but it is still good practice. Right out of the gate I realized I'm quite rusty, and had to look up how to import libraries and read a file, so that was a good refersher. But I also remembered some of the reasons I despise C++ while solving part 1.

For starters, Makefiles are a trap. They are simultaenously complicated and simple. In C#, you can build nearly _any_ C# application using `dotnet build`, and the compiler is smart enough to figure out _every thing else_ on it's own. In C++ you have to specify flags, what the outfile will be named, what the infile is named, etc. Things that are specified inside a csproj just by running `dotnet new`. And so you may think I'd like a `g++ new` command, right? Wrong. I know whatever that new command produces will be a nightmare and will do some convoluted and strange things to accomplish it's goals, much like `create-react-app`. It will abstract out the knowledge I should have in favor of making it simple.

Part 2 helped me realize how much I rely on LINQ and JavaScript's array methods. The STL functions are archaic and ugly and I don't enjoy using them. Meanwhile LINQ I cannot help but use, because it's so effortless and beautiful. In LINQ part 2 would have taken me one minute to complete:

```c#
Enumerable<int> totals; // some list of totals

int totalOfTopThree = totals.OrderByDescending(x => x).Take(3).Sum();
```

And it reads like a dream. In C++, I had to create multiple variables, call the grotesque `vector.beign()` and `vector.end()` functions, and just generally make code that isn't easily processessible using the language center of the brain, and instead rely on the number part.

Of course, all this complaining I'm doing is just shouting at clouds. Really the fault is my own for not knowing C++ better. So hopefully this is a good opportunity to get to where I want to be.

## Part 1
 
> The jungle must be too overgrown and difficult to navigate in vehicles or access from the air; the Elves' expedition traditionally goes on foot. As your boats approach land, the Elves begin taking inventory of their supplies. One important consideration is food - in particular, the number of Calories each Elf is carrying (your puzzle input).
> 
> The Elves take turns writing down the number of Calories contained by the various meals, snacks, rations, etc. that they've brought with them, one item per line. Each Elf separates their own inventory from the previous Elf's inventory (if any) by a blank line.
> 
> For example, suppose the Elves finish writing their items' Calories and end up with the following list:

```
1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
```

> This list represents the Calories of the food carried by five Elves:
> 
> - The first Elf is carrying food with 1000, 2000, and 3000 Calories, a total of 6000 Calories.
> - The second Elf is carrying one food item with 4000 Calories.
> - The third Elf is carrying food with 5000 and 6000 Calories, a total of 11000 Calories.
> - The fourth Elf is carrying food with 7000, 8000, and 9000 Calories, a total of 24000 Calories.
> - The fifth Elf is carrying one food item with 10000 Calories.
> 
> In case the Elves get hungry and need extra snacks, they need to know which Elf to ask: they'd like to know how many Calories are being carried by the Elf carrying the most Calories. In the example above, this is 24000 (carried by the fourth Elf).
> 
> Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?

## Part 2

> By the time you calculate the answer to the Elves' question, they've already realized that the Elf carrying the most Calories of food might eventually run out of snacks.
> 
> To avoid this unacceptable situation, the Elves would instead like to know the total Calories carried by the top three Elves carrying the most Calories. That way, even if one of those Elves runs out of snacks, they still have two backups.
> 
> In the example above, the top three Elves are the fourth Elf (with 24000 Calories), then the third Elf (with 11000 Calories), then the fifth Elf (with 10000 Calories). The sum of the Calories carried by these three elves is 45000.
> 
> Find the top three Elves carrying the most Calories. How many Calories are those Elves carrying in total?
