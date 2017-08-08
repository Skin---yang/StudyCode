/*
 * this is a simple time to get client program.
 * source code in book 5 pages.
 * 
 * the procedure is related to the ipv4 protocol
 * 
 * if want related to the ipv6 protocol, i use comment mark the need modify.
 *
 * */


#include "../../comm/unp.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE+1];
    struct sockaddr_in servaddr;//sockaddr_in6

    if(argc != 2)
        err_quit("usage: no ipAddress");   

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) //AF_INET6
    {
        err_sys("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;//servaddr.sin6_family = AF_INET6
    servaddr.sin_port = htons(13);   //servaddr.sin6_port


    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)//AF_INET6   servaddr.sin6_addr
    {
        err_quit("inet_pton funtion error for : %s",argv[1]);
    }

    if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0)
    {
        err_sys("connect error.");
    }

    while((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if(fputs(recvline, stdout) == EOF)
        {
            err_sys("fputs error.");
        }
    }

    if(n < 0)
        err_sys("read error.");

    exit(0);
}

