# Terminal Pong Clone with Strange Input using ncurses

## Pong
"Pong is a two-dimensional sports game that simulates table tennis. The player controls an in-game paddle by moving it vertically across the left side of the screen, and can compete against either a computer-controlled opponent or another player controlling a second paddle on the opposing side. Players use the paddles to hit a ball back and forth. The aim is for each player to reach eleven points before the opponent; points are earned when one fails to return the ball to the other."

(Taken from [wikipedia](https://en.wikipedia.org/wiki/Pong#Gameplay))

## Installation

Install ncurses.

1. `make build`
2. `./pong.o` 

## Usage

Controls | Key
-------- | ---
Pause | Space
Exit | Enter
Player 0 Up | q
Player 0 Stop | a
Player 0 Down | z
Player 1 Up | p
Player 1 Stop | ;
Player 1 Down | \
New Ball | n
Reset Score | s
Larger Paddles | m
Smaller Paddles | l
Change Ball Display | b

## Comments

The program will keep track of the score but there is currently no target score for winning. It will carry on until you press Enter to quit. It would not be difficult to implement a target score but I did not have enough time to create a pre game menu that I felt was intuitive.

The controls are a little different from conventional pong. The paddle will continue to move until it reaches the edge or the stop key is pressed. This is because detecting multiple keypresses at once is not very easy even with ncurses. Also the OS normally has a delay before sending multiple keys when you hold a key down. This can be easily changed by editing the source code, but it is not recommended.

The program currently has no AI, but it would not be very difficult to implement one after figuring out some nice values for the sizes and timing.

Currently the height of the paddle, velocity of the paddle and velocity of the ball all have some placeholder values that depend on the screen size. I have not spent enough time playing the game to figure out a nice formula for all of these values to make good gameplay. It will also depend on if the velocity of the ball should increase at each bounce and what other additions to the game will be added.

If the terminal window size is changed, the game will automatically create a new ball and paddles in the correct locations while keeping track of the score. Currently there is a bug where the program will crash if the terminal screen is too small. This will leave the terminal in ncurses mode (characters no longer echo, newlines don't print properly) and can only be fixed by restarting the terminal.

## Code

For this project, I have separated the code into different files for organization. I have attempted to keep the logic and display as separate as possible in I wanted to use another display system.

`vector2`
Defines a vector of size 2 for int and float (float has been used since this is a game and does not require very precise numbers).
`rect`
Defines a rectangle by 4 values - point x, point y, a width and a height. Another possible way to define rect would be to have 2 vector2fs. The rect struct was created before vector2 therefore this design choice was not made.
`entity`
Contains the definition for a Ball and Paddle. Both have a bounding box, velocity and display character. The update function for these structs all take a pointer to the struct, the time it took for the previous tick and the screen size. All calculations in the update functions are done via dt.
`render`
Contains a few helper functions and functions to render the ball and paddle.
`pong`
The program itself. The game loop removes the dependency of the rendering from the logic itself. The physics is stepped with variable deltas which is not advisable for physics simulation heavy games but since this is only pong, it does not matter that much.

## Improvements

As mentioned in the Usage section, there are a number of possible improvements that could be made.

Currently the physics for the ball bounce is very inaccurate and could be improved.

As positions have been stored in floats, the ball looks very jumpy when moving around. This could be fixed by rendering it less or rounding the position instead of simply casting to int.

A pre game menu with options for vs Human, vs AI and to set the controls would be much nicer than simply throwing the user into the game. Even printing the controls on the startup screen would be useful.
