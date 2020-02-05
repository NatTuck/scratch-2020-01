
# CS3650: Lecture 9

Today: Building an interpreter


## Challenge 1: Build a shell

Steps to build an interpreter:

    Concrete language: Arithmetic Expressions, like for a 4-function calculator

1. Tokenize

    String => List of Tokens
    
    "3 + 4*5" => [3, +, 4, *, 5]

2. Parse

    List of Tokens => Abstract Syntax Tree

```
    [3, +, 4, *, 5] => (+ 3 (* 4 5))
```

```
    new AddExpr(
       new IntValue(3),
       new MulExpr(
           new IntValue(4),
           new IntValue(5),
       )
    )

```



    
3. Eval

    Abstract Syntax Tree => Value

    Input: Abstract Syntax Tree
    Result: Do stuff

```
(+ 3 (* 4 5)) => 23
```


