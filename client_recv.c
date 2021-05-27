#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	int s = socket(PF_INET, SOCK_STREAM, 0);
	char* ip_add = argv[1];
	char* port = argv[2];
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip_add);
	addr.sin_port = htons(atoi(port));
	int ret = connect(s,  (struct sockaddr *) &addr, sizeof(addr));

	char data[100];
	int N = 100;
	while (1){
		int n2 = recv(s, data, N, 0);
		if (n2 == 0){
			break;
		}
		else{
			int n1 = send(s, data, N, 0);
		}
	}
	int n2 = recv(s, data, N, 0);
	printf("%s", data);
	// int n = send(s, data, N, 0);


	shutdown(s, SHUT_WR);
}
