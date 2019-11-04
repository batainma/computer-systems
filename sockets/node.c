
#include "node.h"
//Finds the primes to send back to the server
int main()
{
    //int connfd;
    int portno = 9405;
    int sockfd = setupClientSocket(portno);
    char* hostname = "10.35.195.49";
    //struct sockaddr_in servaddr, cli;
    
    callServer(hostname, portno, sockfd);
    
    // function for chat
    func(sockfd);
    
    // close the socket
    // close(sockfd);
    return 0;
}

//Func accepts a range from the server socket and calculates all primes within this range
void func(int sockfd)
{
    mesg ranges;
    ranges.min = 0;
    ranges.max = 0;
    
    read(sockfd, &ranges, MAX);
    
    printf("CLIENT SIDE\n MIN %d | MAX: %d\n", ranges.min, ranges.max);
    
    int primeCount = 0;
    if(ranges.min == 2)
    primeCount++;
    
    if(ranges.min % 2 == 0)
    ranges.min++;
    
    //This will find all the primes
    int num;
    bool isPrime = true;
    for(int i = ranges.min; i <= ranges.max; i += 2)
    {
        num = 3;
        isPrime = true;
        
        while(isPrime && num < i)
        {
            if(i % num == 0)
            isPrime = false;
            num++;
        }
	//Prints all the primes it finds, too. Kind of fun to watch...
        if(isPrime)
        {
            primeCount++;
            printf("%d\n", i);
        }
    }
    writeInt(primeCount, sockfd);
    close(sockfd);
    exit(0);
}

//writeInt will send individual ints to server
void writeInt(int prime, int socket)
{
    write(socket, &prime, sizeof(int));
}

//This creates this client's socket
int setupClientSocket(int portno)
{
    // socket create and varification
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    
    return sockfd;
    
}

//Accepts host as the IP address, port number and socket
//to connect to the server socket
void callServer(char* host, int portno, int socket)
{
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(host);
    servaddr.sin_port = htons(portno);
    
    // connect the client socket to server socket
    if (connect(socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
    printf("connected to the server..\n");
    
    
}



