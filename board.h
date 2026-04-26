#ifndef BOARD_H
#define BOARD_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BOARD_SIZE (30 + 2) // + 2 is NOT playable area

typedef struct snake {
  size_t size;
  size_t x_position;
  size_t y_position;
} Snake;

typedef struct Board {
  char board[BOARD_SIZE][BOARD_SIZE];
  size_t obj_position_x;
  size_t obj_position_y;
} Board;

void init_board(Board *b);
void print_board(Board b);
void init_snake(Snake *s);
void add_objective(Board *b);
void play_game(Board *b, Snake *s);

#endif
