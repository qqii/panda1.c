#include "render.h"

Vector2i screen_size(WINDOW *window){
	Vector2i screensize;

	getmaxyx(window, screensize.y, screensize.x);

	return screensize;
}

void print_center(WINDOW *window, char *string){
	Vector2i screensize = screen_size(window);

	mvwprintw(window, screensize.y/2, (screensize.x-strlen(string))/2, string);
}

// A not as powerful mvwprintw which prints vertically instead of horizontally.
void print_vertical_string(WINDOW *window, int y, int x, char *string){
	Vector2i screensize = screen_size(window);

	for(int j = y, i = 0; i < strlen(string) && j < screensize.y; j++, i++){
		mvwaddch(window, j, x, string[i]);
	}
}

// Prints a single character from a point vertically down until it hits bottom.
void print_vertical_chars(WINDOW *window, int y, int x, char character){
    Vector2i screensize = screen_size(window);

    for(int j = y; j < screensize.y; j++){
    	mvwaddch(window, j, x, character);
    }
}

void render_ball(WINDOW *window, Ball b){
    Vector2i center = rect_center_i(b.boundingbox);

    mvwaddch(window, center.y, center.x, b.displaychar);
}

void render_paddle(WINDOW *window, Paddle p){
	char display[(int)p.boundingbox.h+1];
	Vector2i center = rect_center_i(p.boundingbox);

	for(int i = 0; i < p.boundingbox.h; i++){
		display[i] = p.displaychar;
	}
	display[(int)p.boundingbox.h] = '\0';

	print_vertical_string(window, center.y-(int)p.boundingbox.h/2, center.x, display);
}