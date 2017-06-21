/* A strange terminal-pong clone using the ncurses library. Compile using the -lncurses flag. */

#include <time.h>

#include <ncurses.h>

#include "vector2.h"
#include "rect.h"
#include "entity.h"
#include "render.h"

#define FPS (60)
#define SECS_PER_TICK (1/FPS)

#define BALL_CHAR ('O')
#define DIVIDER_CHAR ('|')

//TODO?: Move some logic and setup into individual functions.
int main(int argc, char *argv[]){
    // Seed rand, rand is currently not implimented
    init_entity();

    // Define Variables
    bool running;
    clock_t last_render_time, before_tick, tick_time;

    Vector2i SCREEN_SIZE;
    Ball ball;
    Player player[2];

    // Setup ncurses
    initscr();          // Use ncurses screen
    cbreak();           // Disable line buffering
    noecho();           // Switches off echoing
    curs_set(0);        // Make cursor invisible

    // Pre-Game Logic
    // TODO: Pre game menu
    // TODO: Set your own controls
    SCREEN_SIZE = screen_size(stdscr);

    ball = new_ball(SCREEN_SIZE, BALL_CHAR);
    player[0] = new_player(
        new_vector2i(0, SCREEN_SIZE.y/2),
        SCREEN_SIZE,
        ']',
        'z',
        'a',
        'q');
    player[1] = new_player(
        new_vector2i(SCREEN_SIZE.x-1, SCREEN_SIZE.y/2),
        SCREEN_SIZE,
        '[',
        '/',
        ';',
        'p');

    print_center(stdscr, "Press any key to start...");
    refresh();
    getch();

    last_render_time = clock();
    tick_time = 0;

    nodelay(stdscr, true); // Turns getch to a non-blocking call
    running = true;

    // Game Loop
    while(running){
        before_tick = clock();

        // User Input
        int ch = getch();
        switch(ch){
            case '\n':
                running = false;
                //TODO: create a function that prints and gets the character
                print_center(stdscr, "Press any key to exit...");
                refresh();
                nodelay(stdscr, false);
                getch();
                break;
            case ' ':
                print_center(stdscr, "Press any key to resume...");
                refresh();
                nodelay(stdscr, false);
                getch();
                nodelay(stdscr, true);
                break;
            case 'n':
                ball = new_ball(SCREEN_SIZE, BALL_CHAR);
                break;
            case 's':
                player[0].score = 0;
                player[1].score = 0;
                break;
            case 'm':
                player[0].paddle.boundingbox.h += 1;
                player[1].paddle.boundingbox.h += 1;
                break;
            case 'l':
                player[0].paddle.boundingbox.h -= 1;
                player[1].paddle.boundingbox.h -= 1;
                break;
            case 'b':
                print_center(stdscr, "Press the key you want to change the ball to...");
                refresh();
                nodelay(stdscr, false);
                ball.displaychar = getch();
                nodelay(stdscr, true);
                break;
            default:
                break;
        }

        // Logic
        // Display Size Changed
        Vector2i oldscreensize = new_vector2i(SCREEN_SIZE.x, SCREEN_SIZE.y);
        getmaxyx(stdscr, SCREEN_SIZE.y, SCREEN_SIZE.x);
        if(oldscreensize.x != SCREEN_SIZE.x || oldscreensize.y != SCREEN_SIZE.y){
            // Move right paddle to new position
            player[0].paddle = new_paddle(
                new_vector2i(0, SCREEN_SIZE.y/2),
                SCREEN_SIZE,
                player[0].paddle.displaychar);
            player[1].paddle = new_paddle(
                new_vector2i(SCREEN_SIZE.x-1, SCREEN_SIZE.y/2),
                SCREEN_SIZE,
                player[1].paddle.displaychar);
            ball = new_ball(SCREEN_SIZE, ball.displaychar);
        }

        // Update entities
        for(int i = 0; i < 2; i++){
            update_player(&player[i], tick_time, SCREEN_SIZE, ch, &ball);
        }
        update_ball(&ball, tick_time, SCREEN_SIZE);

        // Scoring and Win detection
        if(rect_center_i(ball.boundingbox).x < 0 - 1){
            player[1].score++;
            ball = new_ball(SCREEN_SIZE, ball.displaychar);
        }else if(rect_center_i(ball.boundingbox).x > SCREEN_SIZE.x + 1){
            player[0].score++;
            ball = new_ball(SCREEN_SIZE, ball.displaychar);
        }

        // Render
        if((float)(clock() - last_render_time)/(float)CLOCKS_PER_SEC > SECS_PER_TICK){
            erase();

            print_vertical_chars(stdscr, 0, SCREEN_SIZE.x/2, DIVIDER_CHAR);
            render_ball(stdscr, ball);
            for(int i = 0; i < 2; i++){
                render_paddle(stdscr, player[i].paddle);
            }

            char scorestring[SCREEN_SIZE.x];
            sprintf(scorestring, "%d | %d", player[0].score, player[1].score);
            mvprintw(0, (SCREEN_SIZE.x-strlen(scorestring)+1)/2, scorestring);

            refresh();
            last_render_time = clock();
        }

        tick_time = clock() - before_tick;
    }

    // Post-Game Logic
    // TODO?: print score?
    endwin();

    return 0;
}
