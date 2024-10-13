# Set-Operations-Software

This project implements a set management system in C, enabling users to perform various operations on sets of integers. The system supports operations such as adding, removing, checking membership, and performing set operations like union, intersection, and difference.

### Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Author](#author)

## Overview

The set management system is designed to handle multiple sets of integers and perform various operations on them. It uses a command-line interface for user interaction, where users can input commands to manipulate sets.

## Features

- **Set Operations**: Perform union, intersection, difference, and symmetric difference on sets.
- **Error Handling**: Comprehensive error messages for invalid commands or set operations.
- **Dynamic Input Handling**: Read and manipulate input strings dynamically.

## Installation

To compile the project, ensure you have a C compiler installed. Use the provided `Makefile` to compile the project:

```bash
make
```

This will create an executable named `myset`.

## Usage

Run the executable from the command line:

```bash
./myset
```

You will be prompted to enter commands. The available commands are:

- **read_set**: Read integers into a set.
  ```Format: read_set SET_NAME, num1, num2, ..., -1```
- **print_set**: Print the contents of a set.
  ```Format: print_set SET_NAME```
- **union_set**: Perform union operation on two sets.
  ```Format: union_set SET_NAME1, SET_NAME2, DESTINATION_SET_NAME```
- **intersect_set**: Perform intersection operation on two sets.
  ```Format: intersect_set SET_NAME1, SET_NAME2, DESTINATION_SET_NAME```
- **sub_set**: Perform subtraction operation between two sets.
  ```Format: sub_set SET_NAME1, SET_NAME2, DESTINATION_SET_NAME```
- **symdiff_set**: Perform symmetric difference operation on two sets.
  ```Format: symdiff_set SET_NAME1, SET_NAME2, DESTINATION_SET_NAME```
- **stop**: Terminate the program.
  ```Format: stop```

  *Note:   The integers should be in range 0 - 127, the set names should be SETA, SETB, SETC, SETD, SETE or SETF*

## Author

Leah Orenstein  
June 2024
