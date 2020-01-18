
## Upgrades and Programming

 - Touch Typing
   - Speeds up time to input code.
   - Avoids distractions
 - Getting an editor with syntax highlighting and automatic indentation
 - Getting a keyboard focued editor and learning it reasonably well
 - Be familiar with the language and libraries you're using
   - Code autocompletion isn't a substitute for this.
 - Learn your environment's debugger. For us that's GDB.
 - More?

## More Assembly Examples


### Example #1: Collatz Conjecture

What if we?

 * Start with an integer > 1.
 * If even, divide by two.
 * If odd, take 3 * x + 1
 * Iterate repeatedly.

10 => 5 => 16 => 8 => 4 => 2 => 1 (=> 4 => 2 => 1 => ...)

7 => 22 => 11 => 34 => 17 => 52 => 26 => 13 => 40 => 20 => 10 => 5 ^

Collatz's Conjecture: All integers eventually get to 1.


### Example 2: Fives

 * Takes one command line argument.
 * If that string is entirely made up of the character '5', print
   "all five".
 * Else, print "not all five".





















