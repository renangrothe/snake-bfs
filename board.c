#include "board.h"
#include "bfs.h"

void play_game(Board *b, Snake *s) {
  bool running = true;
  Node snake_last_position = {0, 0, NULL};

  Node origin[BOARD_SIZE - 2][BOARD_SIZE - 2];
  for (int i = 0; i < BOARD_SIZE - 2; i++)
    for (int j = 0; j < BOARD_SIZE - 2; j++) {
      origin[i][j].x = 0;
      origin[i][j].y = 0;
      origin[i][j].next = NULL;
    }

  size_t points = 0;
  Queue snake_body;
  init_queue(&snake_body);
  insert_queue(&snake_body, s->x_position, s->y_position);

  while (running) {

    print_board(*b);

    // find route to objective
    bool found = run_bfs(b, s->x_position, s->y_position, origin);

    Node tail_position = {s->x_position, s->y_position, NULL};

    if (found) {
      //  translate coordinates to smaller matrix
      Node *passo_atual = origin[s->x_position - 1][s->y_position - 1].next;

      while (passo_atual != NULL) {

        bool scored = b->board[passo_atual->x][passo_atual->y] == 'x';

        insert_queue(&snake_body, (size_t)passo_atual->x,
                     (size_t)passo_atual->y);

        if (scored) {
          s->size++;
          /* b->board[s->x_position][s->y_position] = ' '; */
        } else {
          /* if (s->x_position != tail_position.x && */
          /* s->y_position != tail_position.y) { */

          tail_position = pop_queue(&snake_body);
          b->board[tail_position.x][tail_position.y] = 0;
          /* } */
        }
        snake_last_position.x = s->x_position;
        snake_last_position.y = s->y_position;

        s->x_position = passo_atual->x; // current_step ->x
        s->y_position = passo_atual->y;

        b->board[s->x_position][s->y_position] =
            '@'; // draw snake's head current position

        print_board(*b);

        printf("\n");

        usleep(50000);

        passo_atual = passo_atual->next;
        scored = false;
      }

      points++;
      printf("Points = %lu\n", points);

      add_objective(b); // new objective generated
    } else {
      printf("\nGame Over.\n");
      break;
    }

    /* running = false; */
  }

  printf("Final points = %lu\n", points);
  return;
}

void init_snake(Snake *s) {
  s->size = 0;

  s->x_position = (rand() % (BOARD_SIZE - 2)) + 1;
  s->y_position = (rand() % (BOARD_SIZE - 2)) + 1;

  printf("snake - x:%u y:%u\n", s->x_position, s->y_position);
}

void add_objective(Board *b) {
  if (!b)
    return;
  do {
    b->obj_position_x = (rand() % (BOARD_SIZE - 2)) + 1;
    b->obj_position_y = (rand() % (BOARD_SIZE - 2)) + 1;
  } while (b->board[b->obj_position_x][b->obj_position_y] != 0);

  b->board[b->obj_position_x][b->obj_position_y] = 'x';
  printf("objective - x:%lu y:%lu\n", b->obj_position_x, b->obj_position_y);
}

void init_board(Board *b) {

  if (!b)
    return;

  b->obj_position_x = -1;
  b->obj_position_y = -1;

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      b->board[i][j] = 0;
    }
  }

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      switch (i) {
      case 0:
        switch (j) {
        case 0: // upper left corner
          b->board[i][j] = (char)201;
          break;
        case (BOARD_SIZE - 1): // upper right corner
          b->board[i][j] = (char)187;
          break;
        default: // upper line
          b->board[i][j] = (char)205;
        }
        break;
      case (BOARD_SIZE - 1):
        switch (j) {
        case 0: // lower left corner
          b->board[i][j] = (char)200;
          break;
        case (BOARD_SIZE - 1): // lower right corner
          b->board[i][j] = (char)188;
          break;
        default: // lower line
          b->board[i][j] = (char)205;
        }
        break;
      default:
        switch (j) {
        case 0: // vertical lines
        case (BOARD_SIZE - 1):
          b->board[i][j] = (char)186;
          break;
        }
      }
    }
  }
  Snake *s = malloc(sizeof(Snake));
  init_snake(s);

  b->board[s->x_position][s->y_position] = '@';

  add_objective(b); // add first objective

  play_game(b, s);
  free(s);
}

void print_board(Board b) {

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {

      switch ((unsigned char)b.board[i][j]) {
      case 201:
        printf("\u2554\u2550"); // left upper corner
        /* printf("\u2800"); */
        break;
      case 200:
        printf("\u255A\u2550"); // left inferior corner
        /* printf("\u2800"); */
        break;
      case 187:
        printf("\u2550\u2557"); // right upper corner
        /* printf("\u2800"); */
        break;
      case 188:
        printf("\u2550\u255D"); // right inferior corner
        /* printf("\u2800"); */
        break;
      case 205:
        printf("\u2550\u2550"); // horizontal lines
        /* printf("\u2800"); */
        break;
      case 186:
        switch (j) {
        case 0:
          printf("\u2551 "); // vertical lines
          break;
        case (BOARD_SIZE - 1):
        default:
          printf(" \u2551"); // vertical lines
        }
        /* printf("\u2800"); */
        break;
      case 0:
        /* printf("\u2800"); */
        printf("  ");
        break;
      case ' ':
        /* printf("\u2800"); */
        printf("''");
        break;
      case (unsigned char)'x':
        printf("x ");
        break;
      case '.':
        printf("..");
        break;
      default:
        printf("@ ");
      }
    }
    printf("\n");
  }
}
