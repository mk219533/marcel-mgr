#include <stdio.h>
#include <stdlib.h>

void exploit() {
  printf("Exploited!\n");
  exit(0);
}

void vulnerable(char *arg) {
  char buffer[100];
  strcpy(buffer, arg);
}

int main(int argc, char *argv[]) {
  vulnerable(argv[1]);
  if (argc < 0) exploit();
}

