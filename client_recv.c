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
	int s = socket(PF_INET, SOCK_STREAM, 0);
	char* ip_add = argv[1];
	char* port = argv[2];
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip_add);
	addr.sin_port = htons(atoi(port));
	int ret = connect(s,  (struct sockaddr *) &addr, sizeof(addr));

	// 読み取ったデータの途中にファイルの終了がある場合も
	// 出力する時に、読み取ったデータを全部出力するため、途中にファイルの終了があってもそれ以後も出力する
	// 考えられる実装は、読み取るデータの数に満たない場合（最後の読み取り時）だけ、一つずつ読み取りファイルの終了がきたら終了するようにする。
	char data[1];
	int N = 1;
	while (1){
		int n2 = recv(s, data, N, 0);
		if (n2 == 0){
			break;
		}

	printf("%s", data);
	}
	// int n2 = recv(s, data, N, 0);
	// int n = send(s, data, N, 0); // これも付け加えることで、相手サーバーにもデータを送りつけることができる。

	close(s);
	shutdown(s, SHUT_WR);
}
