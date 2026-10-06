#ifndef GAME_H
#define GAME_H

#include "landmarks.h"

#define MAX_GUESSES 5

typedef enum {
    GAME_START,
    GAME_PLAYING,
    GAME_WON,
    GAME_LOST
} Game_State;

typedef enum {
    DIR_N,
    DIR_NE,
    DIR_E,
    DIR_SE,
    DIR_S,
    DIR_SW,
    DIR_W,
    DIR_NW
} Direction;

typedef enum {
    correct,
    close,
    far
} Distance_Category;

typedef struct {
    int x;
    int y;
    Distance_Category distance;
    Direction direction;
} Guess;

typedef struct {
    int cursor_x;
    int cursor_y;
    int guesses_used;
    Game_State state;
    Guess guesses[MAX_GUESSES];
    const Landmark *target;
} Game;

void game_update_cursor(Game *game);
int game_submit_guess(Game *game);
void game_init(Game *game);
void game_reset(Game *game);

#endif