#include "game.h"
#include "input.h"
#include "dtekv-lib.h"
#include "landmarks.h"
#include "random_number.h"

void game_init(Game *game){
    game->cursor_x = 0;
    game->cursor_y = 0;
    game->guesses_used = 0;
    game->state = GAME_PLAYING;
    unsigned int random_value = random_number();
    int random_landmark = random_value % LANDMARK_COUNT;
    game->target = &landmarks[random_landmark];
}

void game_reset(Game *game){
    game->cursor_x = 0;
    game->cursor_y = 0;
    game->guesses_used = 0;
    game->state = GAME_START;
    game->target = 0;
}

void game_update_cursor(Game *game){
    int x = move_x();
    int y = move_y();
    game->cursor_x += x;
    game->cursor_y += y;
    if (game->cursor_x < 0)
        game->cursor_x = 0;
    if (game->cursor_x > 20)
        game->cursor_x = 20;
    if (game->cursor_y < 0)
        game->cursor_y = 0;
    if (game->cursor_y > 47)
        game->cursor_y = 47;
}

int game_submit_guess(Game *game){
    if (game->guesses_used >= MAX_GUESSES || game->state == GAME_WON){
        return 0;
    }
    game->guesses[game->guesses_used].x = game->cursor_x;
    game->guesses[game->guesses_used].y = game->cursor_y;
    int dx = game->target->x - game->cursor_x;
    int ddx = dx;
    if(dx < 0)
        ddx = -dx;
    int dy = game->target->y - game->cursor_y;
    int ddy = dy;
    if(dy < 0)
        ddy = -dy;
    int distance = ddx + ddy;
    if(distance == 0){
        game->guesses[game->guesses_used].distance = correct;
        game->guesses_used++;
        game->state = GAME_WON;
        return 1;
    }
    else if(distance <= 2)
        game->guesses[game->guesses_used].distance = close;
    else
        game->guesses[game->guesses_used].distance = far;
    if (dx == 0 && dy < 0)
        game->guesses[game->guesses_used].direction = DIR_N;
    else if (dx > 0 && dy < 0)
        game->guesses[game->guesses_used].direction = DIR_NE;
    else if (dx > 0 && dy == 0)
        game->guesses[game->guesses_used].direction = DIR_E;
    else if (dx > 0 && dy > 0)
        game->guesses[game->guesses_used].direction = DIR_SE;
    else if (dx == 0 && dy > 0)
        game->guesses[game->guesses_used].direction = DIR_S;
    else if (dx < 0 && dy > 0)
        game->guesses[game->guesses_used].direction = DIR_SW;
    else if (dx < 0 && dy == 0)
        game->guesses[game->guesses_used].direction = DIR_W;
    else
        game->guesses[game->guesses_used].direction = DIR_NW;
    game->guesses_used++;
    if (game->guesses_used >= MAX_GUESSES)
        game->state = GAME_LOST;
    return 1;
}