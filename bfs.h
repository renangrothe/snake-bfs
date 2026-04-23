#ifndef BFS_H
#define BFS_H

#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  size_t x;
  size_t y;

  struct Node *next;
} Node;

typedef struct Queue {
  size_t num_elements;

  Node *first;
} Queue;

void init_queue(Queue *q);
void destroy_queue(Queue *q);

void insert_queue(Queue *q, size_t x, size_t y);
Node pop_queue(Queue *q);

bool run_bfs(Board *b, size_t start_x, size_t start_y,
             Node origin[BOARD_SIZE - 2][BOARD_SIZE - 2]);
#endif
