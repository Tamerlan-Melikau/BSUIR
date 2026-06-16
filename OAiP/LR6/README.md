# Hash Table Implementation in C++

A C++ program for managing person records using a hash table

## Features

* Insert records into a hash table
* Search records by key (height)
* Handle hash collisions using random probing
* Display the resulting hash table
* Compare original data with hashed storage

## Hashing

The program uses a hash function to transform a key into an index of the hash table:

```cpp
index = height % tableSize;
```

This allows direct access to data without sequentially scanning all records.

### Collision Resolution

When two keys produce the same index, a collision occurs. To resolve it, the program uses random probing:

```cpp
newIndex = (index + randomOffset) % tableSize;
```

The algorithm continues searching for an empty cell until a free position is found.

## Why Hash Tables Are Useful

* Fast insertion of data
* Fast search by key
* Average search complexity close to **O(1)**
* Widely used in databases, dictionaries, caches, compilers, and indexing systems