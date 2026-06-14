# kanren

**kanren** is a library for relational (logic) programming in Python. It allows you to describe relationships between data and find all solutions that satisfy given conditions.

## Features

- Define relations using `Relation()`
- Add facts using `facts()`
- Search for solutions using `run()` and logic variables (`var()`)
- Logical operators: `conde` (OR), `conjo` (AND), `fresh`
- Recursive relations

## Advantages

- Declarative style — you describe *what* to find, not *how*
- Automatically finds all possible solutions
- Pure Python implementation
- Suitable for problems where imperative algorithms are hard to write

## Use Cases

Logical inference, symbolic computing, constraint satisfaction, expert systems, Q&A systems, test data generation, business rule verification.