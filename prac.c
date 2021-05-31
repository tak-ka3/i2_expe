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

int main(int argc, char** argv){
    int N = 100;
    char data[N];
    int cnt = 0;
    while (cnt < 20){
        fgets(data, N, stdin);
        printf("%s", data);
    }
}