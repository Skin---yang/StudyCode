#include "../../comm/unp.h"

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t tm;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    //bind
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

    //listen
    listen(listenfd, LISTENQ);

    while(1)
    {
        connfd = Accept(listenfd, (SA*)NULL, NULL);
        tm = time(NULL); // get current time
        snprintf(buff, sizeof(buff), "hello,welcome to my server.\n%.24s\r\n", ctime(&tm));
        Write(connfd, buff, strlen(buff));
    
        Close(connfd);
    }

    exit(0);
}
