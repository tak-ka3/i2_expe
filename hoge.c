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
  sendto(s, "a", 1, 0, (struct sockaddr *)&addr, sizeof(addr));
  // 最初に１バイトデータを送る

  int cnt = 0;
	while (cnt < 50){
    memset(data, 0, sizeof(addr));
    recv(s, data, sizeof(data), 0);
    char* input = gets(data);
	  printf("%s", data);
    cnt++;
	}

	close(s);
	// shutdown(s, SHUT_WR);
}