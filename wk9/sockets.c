#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
 
void fatal(const char *msg)
{
    perror(msg);
    exit(0);
}
 
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
 
    if (argc < 2) {
        fprintf(stderr, "Usage: %s URL\n", argv[0]);
        exit(1);
    }
    char buffer[BUFSIZ];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) fatal("ERROR socket");
    server = gethostbyname("localhost");
    if (server == NULL) fatal("ERROR gethost");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(8080);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        fatal("ERROR connecting");
 
    char *reqFmt = "GET %s HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n";
    sprintf(buffer, reqFmt, argv[1]);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) fatal("ERROR writing to socket");
    printf("Response:\n");
    while ((n = read(sockfd,buffer,BUFSIZ)) > 0)
        write(1, buffer, n);
    if (n < 0) fatal("ERROR reading from socket");
    close(sockfd);
    return 0;
}