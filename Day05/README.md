# Day 05: Supply Stacks

Part 1 had a lot of trials an tribulations. I started out with high spirits thinking the STL would make this a breeze, and quickly found a lot of blockers.

For example, the `deque` container throws an exception when you attempt to `pop_front` and there is nothing at the front of the `deque`. However, that exception is not helpful unless you know that the `deque` works by using a series of pointers.

```plain
free(): invalid pointer
```

The `deque`, apparently, attempts to `free` the pointer at the "front" of the `deque`, and if it doesn't exist this exception is thrown. In my opinion, this should definitely be something caught by the container and a more helpful error thrown, like `cannot pop: no items on deque`. Rather than requiring a knowledge of the `deque`'s internal implementation to know that it may utilize pointers.

It seems that a lot of the "checking" is pushed onto the user, and it is assumed that if you use it incorrectly that's your problem. I don't enjoy this mindset, and I don't think it's very productive.
