# Day 7: No Space Left On Device

I hit a wall with Day 7. It's a difficult problem that requires a lot of code which, when compared to the other days in the Advent thus far, makes it very discouraging.

I took an initial run at it on the 7th, but found C++ classes infuriating to work with. Today, the 8th, I took another attempt and made an effort to simplify things, removing a lot of the header files in favor of simple inline code, which made making changes much easier. The code works for the most part, but eventually hits a `Segmentation fault` at some point. I know roughly where the fault is being thrown, but I'm unsure why it's happening and I can't access `valgrind` while at work without more effort than it's worth. So I'm going to take another attempt at it either today while at home (with `valgrind`) or tomorrow with fresh eyes to see if I'm doing something incorrectly.

This does make me reflect on the difficulty introduced by header files and maintaining consistency. A single change to a class's signature would result in a change to _two_ files rather than one, which is irritating to be sure.

I came back with Bryan and found out a large portion of my issues were due to an apparent over-utilization of `const` and and under-utilization of `&`. When returning the list of children

```c++
vector<Dir> children()
{
    return _children;
}
```

This creates a _copy_ of the children, which caused issues with de-allocation down the line when trying to set the current child. The proper signature should be `vector<Dir>& children()` (note the `&`) so that it passes by reference and the nodes will remain in memory.

Once I had the directory structure built out, it was trivial to find the answers to part 1 and 2.
