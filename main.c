#include "bfs.h"
#include "board.h"
#include <stdlib.h>
#include <time.h>

int main() {
  unsigned int iseed = (unsigned int)time(NULL);
  srand(iseed);

  Board b;
  init_board(&b);

  /*
  BFS will play the snake game, a new objective will be generated only when the
  algorithm finds the current objective and takes it's position
   */
  return 0;
}
