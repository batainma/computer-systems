//
//  client.h
//  
//
//  Created by Jordan Coffland on 5/16/19.
//

#ifndef client_h
#define client_h
typedef struct{
    int min;
    int max;
}mesg;

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#define MAX 256
//#define IPADDR "10.35.195.49"
//#define PORT 9405
#define SA struct sockaddr

struct sockaddr_in servaddr, cli;

//PROTOTYPES
void writeInt(int, int);
void func(int sockfd);
int setupClientSocket(int portno);
void callServer(char* host, int portno, int socket);
#endif /* client_h */
