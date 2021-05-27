#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	char* ip_add = argv[1];
	char* port = argv[2];

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip_add);
	addr.sin_port = htons(atoi(port));
	int ret = connect(s,  (struct sockaddr *) &addr, sizeof(addr));

  int N = 10000;
	char data[N];

  bind(s, (struct sockaddr *)&addr, sizeof(addr));
  memset(data, 0, sizeof(addr));
  recv(s, data, sizeof(data), 0);

	while (1){
    char* input = gets(data);
    sendto(s, data, 10000, 0, (struct sockaddr *)&addr, sizeof(addr));
	  printf("%s", data);
	}

	close(s);
	shutdown(s, SHUT_WR);
}
