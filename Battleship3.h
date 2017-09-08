#ifndef BATTLESHIP3_H
#define BATTLESHIP3_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_ROWS 10
#define MAX_COLS 10

typedef struct ship
{
	int direction;
	int length;
	char letter_name;
	int hits;
}Ship;

//these functions set up the menu and let the user choose an option
void display_menu (void);
int is_valid_option (void);
void print_game_rules (void);
void quit_game (void);

//these functions set up the game boards and prepare gameplay
void init_board (char board[][MAX_COLS], int rows, int cols);
void print_board (char board[][MAX_COLS], int rows, int cols);
int generate_dir (void);
void generate_start_pt (int dir, int ship_length, int *row_start, int *col_start);
void place_ship (char board[][MAX_COLS], Ship ship_info, int *row_start, int *col_start);

//these functions run through gameplay
int is_ship_sunk (Ship ship_info);
int target_comp_board (char board_target[][MAX_COLS], char board_visible[][MAX_COLS], Ship carrier, Ship battleship, Ship cruiser, Ship sub, Ship destroyer);
int target_player_board (char board[][MAX_COLS], Ship carrier, Ship battleship, Ship cruiser, Ship sub, Ship destroyer);
void gameplay (void);
void eval_user_options (void);

#endif