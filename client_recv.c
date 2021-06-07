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

void die(char *a){
	perror(a);
	exit(1);
}

int main(int argc, char* argv[]){
	int s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == -1) die("socket\n");
	

	char* ip_add = argv[1];
	char* port = argv[2];
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip_add);
	addr.sin_port = htons(atoi(port));
	int ret = connect(s,  (struct sockaddr *) &addr, sizeof(addr));
	if (ret == -1) die("connect\n");

	// 読み取ったデータの途中にファイルの終了がある場合も
	// 出力する時に、読み取ったデータを全部出力するため、途中にファイルの終了があってもそれ以後も出力する
	// 考えられる実装は、読み取るデータの数に満たない場合（最後の読み取り時）だけ、一つずつ読み取りファイルの終了がきたら終了するようにする。
	int N = 100;
	unsigned char data[N];

	// こっちは受け取ってから相手に送るパターン
	// while (1){
	// 	int n2 = recv(s, data, N, 0);
	// 	if (n2 == -1){
	// 		die("recv\n");
	// 	}else if (n2 == 0){
	// 		break;
	// 	}
	// 	int m = write(s, data, n2);
  //   if(m == -1){
  //     die("write");
  //   } 
	// 	// write(s, data, N);
	// }
	// int n2 = recv(s, data, N, 0);
	// int n = send(s, data, N, 0); // これも付け加えることで、相手サーバーにもデータを送りつけることができる。

	// こっちは受け取ったら標準出力するパターン
	while(1){
    int n = read(s, data, N);
    if(n == -1) die("read");
    else if(n == 0) break;
    
    for(int j = 0;j < n; j++){
      printf("%c", data[j]);
    }
  }


	close(s);
	shutdown(s, SHUT_WR);
}
