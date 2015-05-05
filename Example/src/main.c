#include "Ccode.h"
#include <stdio.h>

int main()
{
  printf("You're in main.c!\n");

  if (Ccode_func(7) == 7)
  {
    printf("Func returns equality\n");
  }
  else
  {
    printf("Func is being funky...\n");
  }

  return 0;
}
