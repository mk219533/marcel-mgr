#include <unistd.h>

void main() {
  char *sh[2] = { "/system/bin/ls", NULL };
  execve(sh[0], sh, NULL);
}
