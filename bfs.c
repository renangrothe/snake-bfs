#include "bfs.h"

void init_queue(Queue *q) {

  if (!q)
    return;
  q->first = NULL;
  q->num_elements = 0;
}
void destroy_queue(Queue *q) {
  if (!q)
    return;

  while (q->first) { // remove element
    pop_queue(q);
  }
}

void insert_queue(Queue *q, size_t x, size_t y) {
  if (!q)
    return;

  Node *new = malloc(sizeof(Node));

  if (!new)
    return;

  new->x = x;
  new->y = y;
  new->next = NULL;

  if (!q->first) {
    q->first = new;
  } else {

    Node *p = q->first;

    while (p->next)
      p = p->next;

    p->next = new;
  }
  q->num_elements++;
}

Node pop_queue(Queue *q) {
  if (!q || !q->first) {
    Node e = {0, 0, NULL};
    return e;
  }
  Node *temp = q->first;
  Node value = *temp;
  q->first = temp->next;
  free(temp);
  q->num_elements--;

  return value;
}

bool run_bfs(Board *b, size_t start_x, size_t start_y,
             Node origin[BOARD_SIZE - 2][BOARD_SIZE - 2]) {

  /* bool found = false; */

  bool visited[BOARD_SIZE - 2][BOARD_SIZE - 2] = {false};
  Queue q;
  init_queue(&q);
  /**/
  for (int i = 0; i < BOARD_SIZE - 2; i++) {
    for (int j = 0; j < BOARD_SIZE - 2; j++) {
      origin[i][j].x = i + 1; // storing in board_size + 2 format
      origin[i][j].y = j + 1;
      origin[i][j].next = NULL;
    }
  }

  insert_queue(&q, start_x, start_y);
  visited[start_x - 1][start_y - 1] = true;

  bool found = false;
  size_t target_x = 0, target_y = 0;

  // always get enqueued with 'priority'
  int dx[] = {-1, 1, 0, 0};
  int dy[] = {0, 0, -1, 1};

  while (q.num_elements > 0) {
    Node current = pop_queue(&q);

    if (b->board[current.x][current.y] == 'x') {
      found = true;
      target_x = current.x;
      target_y = current.y;
      break;
    }

    for (int i = 0; i < 4; i++) {
      size_t nx = current.x + dx[i];
      size_t ny = current.y + dy[i];
      if (nx > 0 && nx < BOARD_SIZE - 1 && ny > 0 && ny < BOARD_SIZE - 1) {

        if (!visited[nx - 1][ny - 1] &&
            (b->board[nx][ny] == 0 || b->board[nx][ny] == 'x')) {
          visited[nx - 1][ny - 1] = true;

          origin[nx - 1][ny - 1].next = &origin[current.x - 1][current.y - 1];

          insert_queue(&q, nx, ny);

          if (b->board[nx][ny] == 0) {
            b->board[nx][ny] = '.'; // identifier for printing
            print_board(*b);
            usleep(1500); // 1.5ms
          }
        }
      }
    }
  }

  destroy_queue(&q);

  if (found) {
    Node *prev = NULL;
    Node *curr = &origin[target_x - 1][target_y - 1];
    Node *next_node = NULL;

    while (curr != NULL) {
      next_node = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next_node;
    }
  }

  /**/
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (b->board[i][j] == '.') {
        b->board[i][j] = 0;
      }
    }
  }
  return found;
}
