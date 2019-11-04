#include "head.h"

// Driver function
int main()
{
    int portno = 9405; 
    int sockfd = setupServerSocket(portno);
    
    int* connfd = serverSocketAccept(portno, sockfd);
    
    // Function for chatting between client and server
    func(connfd);
    
    // After chatting close the socket
    close(sockfd);
}

// Function designed for chat between client and server.
void func(int* sockfd)
{
    int i = 0;
    mesg ranges;
    ranges.min = rangeMin;
    ranges.max = 0;
    int rangeBetween = rangeMax - rangeMin;
    while(sockfd[i] != '\0')
    {
        ranges.max = (rangeBetween + rangeMin) / MAX_NODES * (i+1);
        printf("Node %d range to check: [%d - %d]\n", i+1, ranges.min, ranges.max);
        
        write(sockfd[i], &ranges, MAX);
        ranges.min = ranges.max + 1;
        
        i++;
    }
    printf("\n");
    
    //Simply shows what nodes got how many prime numbers and puts them together
    int sum = 0;
    int sumTemp = 0;
    for(int i = 0; i < MAX_NODES; i++)
    {
        read(sockfd[i], &sumTemp, sizeof(int));
        sum += sumTemp;
	printf("Node %d wrote back %d primes\n", i+1, sumTemp);
    }
    printf("TOTAL PRIMES: %d\n", sum);
}


//Creates the socket to which the nodes will connect to
int setupServerSocket(int portno)
{
    // socket create and verification
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    
    return sockfd;
}

//Listens and accepts any socket connections
int* serverSocketAccept(int portno, int sockfd)
{
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //servaddr.sin_addr.s_addr = htonl("10.35.195.47");
    servaddr.sin_port = htons(portno);
    
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
    printf("Socket successfully binded..\n");
    
    // Now server is ready to listen and verification
    if ((listen(sockfd, MAX_NODES)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    printf("Server listening..\n");
    
    int len = sizeof(cli);
    int* connfd = malloc(sizeof(int*)*MAX_NODES);
    
    // Accept the data packet from client and verification
    for(int i = 0; i < MAX_NODES; i++)
    {
        connfd[i] = accept(sockfd, (SA*)&cli, &len);
        //printf("We have accepted %d client(s).\n", (i+1));
        
        
        if (connfd < 0) {
            printf("server acccept failed...\n");
            exit(0);
        }
        else
        printf("server acccepted the client #%d...\n", (i+1));
    }
    
    return connfd;
    
}


