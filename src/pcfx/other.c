#include "utils.h"

int random_game(int min, int max)
{
  return rand()%(max-min) +min;
}

void startrandom_game()
{
}
