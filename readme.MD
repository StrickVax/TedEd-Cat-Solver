# Giant Cat Riddle Solver

This program is meant to solve math problems similar to TedEd's [Giant Cat Riddle](https://www.ted.com/talks/dan_finkel_can_you_solve_the_giant_cat_army_riddle/)

---
## Purpose

The program is tasked with outputting three numbers: 2, 10, 14, in that order.

However, the computer can only do three operations: 
 - Add 5
 - Add 7
 - Square root the current number

On top of that, it cannot output a number.
 - Bigger than 60
 - More than once
 - A non-integer number

---

## Implementation

The program is a Depth-first search. It will attempt to repeat the same operation until it un-satisfies a requirement or finds the solution. If it finds a wrong path, it will backtrack until it can attempt a different operation, and then do so.

The program keeps track of the moves done with a vector. Every time it makes a move, it adds a new entry, [0], which stands for [Add 5]. If it must go back, it replaces the previous entry with the proceeding number; [1] or [2].

```
[0] -- Add 5

[1] -- Add 7

[2] -- Square root
```

```
// ...5 -> 10 -> 17 -> \sqrt{17}

...[0, 0, 1, 2]
```

If it still breaks the rules, it will go back two elements, and replace the current element.

---

## Task List:

- [ ] Recreate original problem.
- [ ] Be able to tell whether a problem is solvable.
- [ ] Be able to attempt the problem using different operations.
- [ ] Be able to generate original problems.
  - [ ] (Optional) Have the program choose its own operations, to let it reach the solution faster.