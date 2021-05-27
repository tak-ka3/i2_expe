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
	int N = 1000;
	char data[N];
  int cnt = 0;
	while (cnt < 1){
    char* input = gets(data);
		int n2 = send(s, data, N, 0);
    int t = 0;
		for (int i = 0; i < N; i++){
      if (data[i] == 1){
        t += 1;
      }
      else{
        break;
      }
    }
    if (t == N){
      break;
    }
	  printf("%s", data);
    cnt++;
	}
	// int n2 = recv(s, data, N, 0);
	// int n = send(s, data, N, 0); // これも付け加えることで、相手サーバーにもデータを送りつけることができる。

	close(s);
	shutdown(s, SHUT_WR);
}
