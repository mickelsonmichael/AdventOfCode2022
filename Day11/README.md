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
