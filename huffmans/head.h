//
//  server.h
//  
//
//  Created by Jordan Coffland on 5/16/19.
//

#ifndef server_h
#define server_h

#include <netdb.h>
#include <stdio.h> /* for printf() and fprintf() */
#include <sys/types.h> /* for Socket data types */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <netinet/in.h> /* for IP Socket data types */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <netinet/in.h>
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <strings.h> /* for memset() */
#include <unistd.h> /* for close() */

typedef struct{
    int min;
    int max;
} mesg;

struct sockaddr_in servaddr, cli;
#define MAX 256
//#define PORT 9405
#define MAX_NODES 5
#define SA struct sockaddr
#define rangeMin 1
#define rangeMax 1000000

//Prototypes
void func(int* sockfd);
int setupServerSocket(int portno);
int* serverSocketAccept(int portno, int sockfd);

#endif /* server_h */
