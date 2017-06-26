# Coursework 3: SDL Sketch Decoder

Parse a `.sketch` file and print the instructions in the terminal.

## Format

* Opcode 0 represents a DX operation, which changes the current x position by a given signed number of pixels, in the range -32..31. Nothing is displayed.
* Opcode 1 represents a DY operation which changes the y position by a signed number of pixels (also -32..31). If the pen is down (see opcode 3), a line is drawn from the previous (x,y) position to the current position. Whether a line is drawn or not, the current position is remembered as the previous position for next time.
* Opcode 2 represents a DT operation which represents a pause of a given unsigned number of milliseconds, in the range 0..63.
* Opcode 3 with Operand 3 represents a PEN operation which toggles the drawing state between "pen up" (drawing off, movement only) and "pen down" (drawing on).

## Usage

1. `make`
2. `./decode.o <filename> [filenames]`
