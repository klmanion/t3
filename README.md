# t3
A game of advanced Tic-Tac-Toe.

# Summary
Inspired by Atari's 3D tic-tac-toe which I played as a kid,
I started this project 6 years ago, and left it unfinished until now.

It is now playable and winable.

The board is programmatic, and you can set the dimensions with the `-d` switch.
Don't forget to check out this math in the code.

## Historical note
I made as few changes as possible to the existing codebase, so there's some oddities in there which I was experimenting with at the time.
This mainly refers to: (1) the use of the compiler attributes `__attribute__((pure))` and `__attribute__((const))` (in their macro forms `__pure` and `__pure2` respectively;
(2) the `__P()` macro, which really is only supposed to be used to make K&R prototypes portable, but for whatever reason I was using them when I started the codebase and didn't have the heart (or compunction) to remove them.

# Building
This project is built using autotools, so to build just type:
```bash
./autogen.sh
./configure && make
```
