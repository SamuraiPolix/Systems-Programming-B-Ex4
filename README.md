# STL, Templates, and Iterators - C++ Assignment #4
#### (Systems Programming B @ Ariel University)
#### Author: Samuel Lazareanu (sam.lazareanu@gmail.com)


[Link to requirements](ASSIGNMENT.md)


## Overview
In this assignment, I implemented a generic tree container in C++.
The tree is k-ary (each node has at most k children. For example, a binary tree is a 2-ary tree), and can contain keys of any type (e.g. numbers, strings, and classes).
This assignment required usage of operators overloading, templates, and iterators.

## Classes
### `Tree`
The tree.hpp file contains the Tree class template with all the implemented methods.
The reason we implemented all the methods in the header file is because the methods are templated, and the compiler needs to know the implementation of the methods at compile time. This solves a lot of problems with templates, but it also makes the compilation time longer (which is no biggie because this is a very small project).

### `Node`
The Node class is a helper class for the Tree class. It represents a node in the tree, and it contains a key and a vector of children nodes.

### `Complex`
The Complex class is a class that represents complex numbers. It is used to demonstrate the usage of the Tree class and test its methods.

## Iterators
The Tree class contains the following iterators:
1. Pre-Order Iterator:
For a binary tree, K == 2: current node -> left subtree -> right subtree
For a general tree, K > 2: DFS starting from the root
2. Post-Order Iterator
For a binary tree, K == 2: left subtree -> right subtree -> current node
For a general tree, K > 2: DFS starting from the root
3. In-Order Iterator
For a binary tree, K == 2: left subtree -> current node -> right subtree
For a general tree, K > 2: DFS starting from the root
4. BFS Iterator
5. DFS Iterator
6. Heap Iterator

## GUI
I didn't implement the GUI part of the assignment, because lack of time and because I wanted to focus on the tree container and the iterators.

## Usage
A basic usage example can be found inside the Demo.cpp file.

1. Clone the repository.
2. Build the project using the provided 'makefile' and run:
   - `make demo` -     run using `./demo`  (simple test)
   - `make test` -     run using `./test`  (advanced doctest)
   - `make tidy` -     makes sure the code is clean
   - `make valgrind` - makes sure there are no memory leaks/problems.


### Tests
#### clang-tidy and valgrind
Before submitting we ran clang-tidy to make sure the code is written well, and valgrind to make sure there are no memory errors or leaks.

#### Test.cpp
This file includes tests on everything implemented in the Tree class. It tests the methods, the iterators, and the operators.