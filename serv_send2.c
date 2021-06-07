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
#define MAXLINE 1024

int main(int argc, char** argv){
    FILE *fpin;
    char* port = argv[1];
    int N = 100;
    unsigned char data[N];
    int ss = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(ss, (struct sockaddr *) & addr, sizeof(addr));

    listen(ss, 10);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int s = accept(ss, (struct sockaddr *) & client_addr, &len);
    if (s > 0){
        printf("%s\n", "complete connecting");
    }
    char D[MAXLINE];
    fpin = popen("rec -t raw -b 16 -c 1 -e s -r 44100 -", "r");
    while (1){
        if (s > 0){
            int n1 = fread(D, sizeof(char), MAXLINE, fpin);
            if (n1 == 0){
                break;
            }
            write(s, D, n1);
        }
    }

    close(ss);

    close(s);
}