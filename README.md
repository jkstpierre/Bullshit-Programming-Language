# *The Bull$hit! Programming Language*

## Introduction
Bull$hit! is an esoteric programming language designed for one purpose: to infuriate you.
Inspired in part by its spritual neighbor Brainfuck, Bull$shit! stretches the bounds of computational usability to utterly outrageous lengths. 
It is repetitive, it is tedious, and it is boring, but from these tribulations it is hoped that you, the clever programmer, shall learn to overcome them and
truly appreciate the great lengths to which modern languages assist you in your day-to-day life.

Best of wishes to you and your computational journey ahead.

Sincerely,   
*J.K.S.*

## Language Overview
### Computational Process
In Bull$hit!, programs consist of the manipulation of three distinct variables:
1. A square 2-D array of 32-bit signed integers of size N^2 to be specified at the start of the program. 
This array plays the role of main memory for the program, and every cell is initialized to zero.
2. A (y,x) tuple representing the index of the cell in memory currently being pointed to.
3. A 32-bit signed integer called *curr_value* to be used for manipulating data. It's starting value is NULL.

Through the modification of these variables, theoretically any program can be successfully created. To summarize facetiously: you and you alone are what stands between Half-Life 3 and its corresponding Bull$hit! program. ;)


### Syntax
Bull$hit! borrows heavily from Brainfuck in the usage of an unambiguous and simplistic syntax. That being said, despite these similarities, the commands of Bull$hit! are fundamentally different and more numerous than Brainfuck's.

**Commands**  
+ `#` - Specifies the size of the N^2 2-D array that is the program's main memory. The number of consecutive `#`'s grouped together denotes the *N* for said array's allocation. This command must be called at the start of the program and cannot again be used once other commands have been called.
+ `+` - Copies the value stored at cell (y,x) in main memory to *curr_value*.
+ `-` - Overwrites the value stored at cell (y,x) with *curr_value*. Sets *curr_value* to NULL.
+ `>` - Move the (y,x) tuple to (y, x+1). If *curr_value* has data in it, add the value of the memory cell at (y, x+1) to it.
+ `v` - Move the (y,x) tuple to (y+1, x). If *curr_value* has data in it, add the value of the memory cell at (y+1, x) to it.
+ `<` - Move the (y,x) tuple to (y, x-1). If *curr_value* has data in it, subtract the value of the memory cell at (y, x-1) from it.
+ `^` - Move the (y,x) tuple to (y-1, x). If *curr_value* has data in it, subtract the value of the memory cell at (y-1, x) from it.
+ `0` - If *curr_value* is not NULL, set *curr_value* to 0.
+ `1` - If *curr_value* is not NULL, set *curr_value* to 1.
+ `{` - Begin loop. If value at memory cell (y, x) is 0, skip to corresponding `}`; otherwise, execute contained instructions.
+ `}` - End loop. Must have corresponding `{` obviously.
+ `,` - Read one ASCII character from stdin into memory cell (y, x).
+ `.` - Print the value of memory cell (y, x) to stdout as an ASCII character.
+ `;` - Read one 32-bit signed decimal number from stdin into memory cell (y, x).
+ `:` - Print the value of memory cell (y, x) to stdout as a 32-bit signed decimal number.
+ `/` - Comment out a line.

## Examples
The examples folder contains several documented Bull$hit! programs for you to learn from. If you develop a program that you wish to showcase there feel free to let me know!

## Installation & Usage
Included in this repository is a working Bull$hit! compiler written in C. This program is a work in progress, but at the moment is capable of basic syntax checking as well as converting your Bull$hit! programs into equivalent C code and compiling down to machine code using gcc. 

On Unix systems to install the Bull$hit! compiler enter the following into a terminal:
```
	cmake .
	make install
```

This will produce an executable named `bsc` at /usr/bin.

To compile a Bull$hit! program, type the following into a terminal:
```
	bsc <input_file.bs>
```

Assuming no syntax errors were found, this will generate an executable with the name <input_file>.

## Contact
Email: jkstpierre@wpi.edu
