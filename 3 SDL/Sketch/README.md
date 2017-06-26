# Coursework 3: SDL Sketch

Parse a `.sketch` file and render instructions in an SDL window.

## Usage

1. `make`
2. `./sketch.o <filename>`

## Sketch format

The sketch format is a binary file that uses an instruction set that controls something similar to a turtle.

Use `xxd -g 1 [filename]` to inspect sketch files in their binary format. A separate tool has been created in the Decode folder to print out the instructions.

See the [Sketch.xhtml](Sketch.xhtml) file or the code for more details.

## Comments

For my program I have attempted to separate the program into as many separate sections as possible but unfortunately it has become a horrible mess at the end of the day.

The initial stages I separated my program into are:

* vector2
* state
* interpret

`Vector2` contains a 2D Vector of ints which is used in the struct. I have also added some small functions in case I even need to use it again.

State contains a structure for the "pen", which contains the starting position, the position when the pen went down, if the pen has gone down and the color. 

Interpret was an attempt to write less (complex) code. Here a struct is defined for the operation/instruction (`Operation`), and another struct which links the opcode to a function pointer which will call different functions in display.h depending on the state (`InstructionTable`).
Unfortunately I had not perceived the idea of an extended operand so my operation struct can only store opcodes and operands that are 1 byte or less. This lead me to pass the file pointer to all of the functions.

The idea behind the instruction table was that I could write one function for the switching (`interpret`) and create small functions that were passed to interpret through an array of instruction tables. This system worked very well for the first 2 stages, and the third stage simply required me to create a function that defined its own switching table and add that to the original switching table.

When stage 4 arrived, I had to make all of the functions I created accept a file pointer. The original idea was for all function that drew or changed the state to say in sketch but I felt that with the addition of extend I should move them into interpret and keep the extended functions in sketch.
At this point I had also considered reading the entire file into a unsigned char array then passing this instead of the file pointer. 

Currently my sketch.o passes all tests.

At the end of all of this, I decided I needed to re factor my code. Looking at the task as a whole I identified 2 tasks the program needed to perform. 
The first is to take the binary file and turn it into the assembly like instructions. This part of the program should be SDL/display.h independent. 
The second is to take the assembly like instructions and interpret them and act on them (drawing, sleeping, etc).

Further it would be nice to have a program that could take the assembly like instructions and turn that back into a binary file. This program could even have features that exist in higher level languages like loops and if statements. 

I decided to attempt the first part, a program independent to SDL/display.h that could take the binary and turn it into assembly like instructions. This was relatively easy to create since it just required a small amount of tweaking of my current sketch.c.
I placed the functions with the instruction tables into decode.c and all of the printing functions into interpret.h. Currently my decode.o is able to decode binary .sketch files into assembly like text.

It was my original goal to create a decode function that given a unsigned character array returned a character array (the binary like format) but this requires another structure (since '\0' = 0x00 is a valid instruction) to keep track of the length and multiple reallocs to make sure the string is long enough to store the entire assembly code.

I would have liked to been able to create the second half (assembly->drawing) and then possibly add some new opcodes but I have ran out of time.
