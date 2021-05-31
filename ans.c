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
#define N 10000

int check(unsigned char *data){
	int k = 0;
  for (int i = 0; i < 10000; i++){
    if (data[i] == '1'){
      k++;
    }
  }
  if (k == 10000){
    return 1;
  }else{
    return 0;
  }
}

int main(int argc, char* argv[]){
  unsigned char data[N];
  char* ip_add = argv[1];
	char* port = argv[2];
  int s = socket(PF_INET, SOCK_DGRAM, 0);
  if (s == -1){
    printf("socket is failed\n");
  }
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
  int c = inet_aton(argv[1], &addr.sin_addr);
  if (c == 0){
    perror("inet_aton is failed\n");
  }
	// addr.sin_addr.s_addr = inet_addr(ip_add);
	addr.sin_port = htons(atoi(port));
  unsigned char k = '1';
  int m = sendto(s, &k, 1, 0, (struct sockaddr*)&addr, sizeof(addr));
  if (m == -1){
    perror("send error");
    exit(1);
  }

	while (1){
    int n = recvfrom(s, data, N, 0, NULL, 0);
    if (n == -1){
      perror("recv");
      exit(1);
    }
    if (n == 0){
      break;
    }
    int ans = check(data);
    if (ans == 1){
      break;
    }
    printf("%s", data);
	}

	close(s);
	// shutdown(s, SHUT_WR);
}