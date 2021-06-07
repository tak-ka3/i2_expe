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
    FILE* fpin;
    fpin = popen("ls", "r");
    char data[100];
    while (1){
        int n1 = fread(data, sizeof(char), 100, fpin);
        if (n1 == 0){
            break;
        }
        printf("%s\n", data);
    }
}