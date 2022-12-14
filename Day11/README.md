# Day 11: Monkey in the Middle

Another day, another pass by reference mistake. My monkey tossing was slowing way down in the later rounds because each time I iterated throught he monkeys, I was making a copy of the monkey, rather than passing by reference. This is a pitfall that caught me on day 7 and again caught me on day 11. Here's an example of where the copying happened:

```c++
for (auto monkey : monkeys)
{
    // throw to another monkey
}
```

Notice the `auto monkey` is missing the `&` to make it a pass by reference.
It should really be `auto &monkey`. To avoid this in the future, I can elect to explicitly exclude the copy constructor, which would result in compile-time exceptions, rather than runtime headaches.

Part 2 was quite the undertaking, for multiple reasons.
For starters, the question was worded _very_ poorly, in my opinion.
It wasn't clear what they actually wanted or what the problem is.
They really _implied_ that it would be an integer overload, but they didn't outright say it and instead danced around it with vague statements.
So I started the problem wondering what I was even trying to accomplish.

Once I figured out that they were asking for a method to reduce the size of the worry level without changing the calculations, I was able to make forward progress.
I looked at a lot of hints and explanations online, doing my best to avoid actual code, but I wasn't making much progress.
Eventually, a user on reddit, [u/paul_sb76](https://www.reddit.com/user/paul_sb76/), wrote a statement that made it click a little more.

> The key insight is this:
>
> ```
> For any set of integers n, p and d: if p mod d = 0, then
> 
>   (n mod p) mod d = n mod d
> ```
> 
> In this case: d is the divisor (different for each monkey), n is the input number (worry level), and n mod p is the reduced number. What the above observation shows is that if you take p to be a common multiple for every possible d, then you may safely replace n by n mod p without messing up any future divisibility test.
> 
> In this case, since all the monkey divisors are different primes, the minimum number p that satisfies these conditions is simply the product of all those primes. If the monkey divisors weren't primes or if they had some divisors in common, then the "least common multiple" would be a lot smaller.

Here is a rough explanation as I understand it:

When working with modulus arithmetic, there is a property that holds true:

```math
(x % (m * n) ) % n == x % n
```

Which more or less states a relationship between a number, `x` and a multiple of the modulus `m * x`.
In terms of the problem itself, this can be translated as:

> When taking `worry_level % monkey_test`, it is the same as taking `(worry_level % (m * monkey_test)) % monkey_test`, where `m` is any number.

So to start a solution, you must first find a common multiple of all the `monkey_test` values.
In the input, it appears to be a set of prime numbers, `2, 3, 5, 7, 11, 13, 17, 19`.
The fastest way to find the multiple of any set of numbers is to multiply them together, which in the input should result in `9,999,690`.

With that in mind, you can now take that common multiple and remove it from consideration by performing a `worry_level = worry_level % 9_999_690`.
This removes all the multiples of the primes and leaves only the "significant" portions and a much smaller value.
We are essentially "shifting" the values down to a more manageable number and ignoring the "shared" multiples.

As an example, we can look at the AoC example input from part 1.

```plain
Monkey 0:
  Starting items: 79, 98
  Operation: new = old * 19
  Test: divisible by 23
    If true: throw to monkey 2
    If false: throw to monkey 3

Monkey 1:
  Starting items: 54, 65, 75, 74
  Operation: new = old + 6
  Test: divisible by 19
    If true: throw to monkey 2
    If false: throw to monkey 0

Monkey 2:
  Starting items: 79, 60, 97
  Operation: new = old * old
  Test: divisible by 13
    If true: throw to monkey 1
    If false: throw to monkey 3

Monkey 3:
  Starting items: 74
  Operation: new = old + 3
  Test: divisible by 17
    If true: throw to monkey 0
    If false: throw to monkey 1
```

The "test" values for the example are `23`, `19`, `13`, and `17`.
Multiplying these together gives a common multiple of `96,577`.

Then we can use the first item as an example.

```plain
Monkey 0 inspects item 79
- Multiplies 79 by 19 to get 1,501
```

After the `monkey 0`'s inspection, the new worry level is `1,501`, which is not divisible by `23` (remainder `6`), meaning the monkey tosses it to `monkey 3`.

We can continue following the item around until the value is greater than our common value `96,577`:

```plain
Monkey 3 inspects item @ 1,501
- Adds 3 to 1,501 to get 1,504
- 1,504 is not divisible by 17, so it is thrown to monkey 1

Monkey 1 inspects item @ 1,504
- Adds 6 to 1,504 to get 1,510
- 1,510 is not divisible by 19, so it is thrown to monkey 0

Monkey 0 inspects item @ 1510
- Multiples 1510 by 19 to get 28,690
- 28,690 is not divisible by 23, so it is thrown to monkey 3

Monkey 3 inspects item @ 28,690
- Adds 3 to 28,690 to get 28,693
- 28,693 is not divisible by 17, so it is thrown to monkey 1

Monkey 1 inspects item @ 28,693
- Adds 6 to 28,693 to get 28,695
- 28,696 is not divisible by 19, so it is thrown to monkey 0

Monkey 0 inspects item @ 28,696
- Multiplies 28,696 by 19 to get 545,224
```

Now that we have a value, `545,224`, which is larger than our common multiple, `96,577`, we can take the modulus by the common multiple (`545,224 % 96,577`) to get `62,339`.

Now we can do the `mod 23` on both values to check that they are equivalent:

- [`545,224 % 23 = 9`](https://www.google.com/search?q=545224+mod+23)
- [`62,339 % 23 = 9`](https://www.google.com/search?q=62339+mod+23)

Therefore, we can replace the larger `545,224` with the smaller `62,339`, and continue this replacement each time the value grows beyond our `96,577` multiple, meaning we will never get an integer overflow.
