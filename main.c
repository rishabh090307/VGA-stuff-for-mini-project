#include "game.h"
#include "input.h"
#include "dtekv-lib.h"
#include "random_number.h"
#include "landmarks.h"

int player_x;
int player_y;
#define MAP_ROWS 48
#define MAP_COLS 21
#define CELL_SIZE 5
#define MAP_X 100
#define MAP_Y 0
#define RED     4
#define GREEN   2
#define YELLOW  14

int sweden_array[MAP_ROWS][MAP_COLS] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
void draw_cell(volatile char *VGA, int x, int y)
{
    int screen_x = MAP_X + x * CELL_SIZE;
    int screen_y = MAP_Y + y * CELL_SIZE;

   int color;

    if (sweden_array[y][x]) {
        color = 1;
    } else {
        color = 0;
    }

    for (int py = 0; py < CELL_SIZE; py++) {
        for (int px = 0; px < CELL_SIZE; px++) {
            VGA[(screen_y + py) * 320 + (screen_x + px)] = color;
        }
    }
}
void draw_guess(volatile char *VGA, int x, int y, int result)
{
    int screen_x = MAP_X + x * CELL_SIZE;
    int screen_y = MAP_Y + y * CELL_SIZE;

    int color;

    if (result == correct) {
        color = GREEN;
    }
    else if (result == close) {
        color = YELLOW;
    }
    else {
        color = RED;
    }

    for (int py = 0; py < CELL_SIZE; py++) {
        for (int px = 0; px < CELL_SIZE; px++) {
            VGA[(screen_y + py) * 320 + (screen_x + px)] = color;
        }
    }
}
void draw_sweden(volatile char *VGA){
    for (int y=0;y<MAP_ROWS; y++) {

        for (int x = 0; x < MAP_COLS; x++) {

            if (sweden_array[y][x] == 1) {
                int screen_x = MAP_X + x * CELL_SIZE;
                int screen_y = MAP_Y + (y) * CELL_SIZE;
                for (int py = 0; py < CELL_SIZE; py++) {
                    for (int px = 0; px < CELL_SIZE; px++) {

                        VGA[(screen_y + py) * 320 + (screen_x + px)] = 1;

                    }
                }           
                

            }
        }
    }
}

void random_start_position(void) {
    do {
        player_x = random_number() % MAP_COLS;
        player_y = random_number() % MAP_ROWS;
    } while (sweden_array[player_y][player_x] != 1);
}

void draw_cursor(volatile char *VGA, int x, int y)
{
    int screen_x = MAP_X + x * CELL_SIZE;
    int screen_y = MAP_Y + (y) * CELL_SIZE;

    for (int py = 0; py < CELL_SIZE; py++) {
        for (int px = 0; px < CELL_SIZE; px++) {
            VGA[(screen_y + py) * 320 + (screen_x + px)] = 2;
        }
    }
}



int main()
{
    volatile char *VGA = (volatile char*) 0x08000000;
    volatile int *VGA_CTRL = (volatile int*) 0x04000100;
    random_seed(12345);
    random_start_position();

    draw_sweden(VGA);                      
    draw_cursor(VGA, player_x, player_y); 

    *(VGA_CTRL + 1) = (unsigned int)VGA;
    *(VGA_CTRL + 0) = 0;
    
    while (1) {
       
        
        int dx = move_x();
        int dy = move_y();
        int pressed_button = btn_pressed();
        if (dx == 1){
            if (pressed_button) {
                if (player_x < MAP_COLS - 1 && sweden_array[player_y][player_x + 1] == 1) {
                    draw_cell(VGA, player_x, player_y);
                    player_x++;
                    draw_cursor(VGA, player_x, player_y);
                }
            }
        }

        else if (dx == -1){
            if (pressed_button) {
                if (player_x > 0 && sweden_array[player_y][player_x - 1] == 1) {
                    draw_cell(VGA, player_x, player_y);
                    player_x--;
                    draw_cursor(VGA, player_x, player_y);
                }
            }
        }
        else if (dy == -1){
            if (pressed_button) {
                if (player_y > 0 && sweden_array[player_y - 1][player_x] == 1) {
                        draw_cell(VGA, player_x, player_y);
                        player_y--;
                        draw_cursor(VGA, player_x, player_y);
                }
            }
        }       
        else if (dy == 1){
            if (pressed_button) {
                if (player_y < MAP_ROWS - 1 && sweden_array[player_y + 1][player_x] == 1) {
                    draw_cell(VGA, player_x, player_y);
                    player_y++;
                    draw_cursor(VGA, player_x, player_y);
                }
            }
        }
        if (reset ()){
    
            player_x = start_x;
            player_y = start_y;

            draw_sweden(VGA);
            draw_cursor(VGA, player_x, player_y);
        }
    }
        
} 

void handle_interrupt(unsigned cause){
  (void)cause;
}
