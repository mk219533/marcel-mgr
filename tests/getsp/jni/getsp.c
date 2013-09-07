#include <stdio.h>

unsigned long getsp() {
  __asm__("add r0, sp, #0");
}

void main() {
  printf("sp=%08lx\n", getsp());
}

