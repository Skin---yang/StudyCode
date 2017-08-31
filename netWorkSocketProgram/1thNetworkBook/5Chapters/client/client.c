#include "../../comm/unp.h"

/*  this is a base client program 
 *
 *  the connection server will send data to the server after the success of the server.
 *  last, the server will answer the same data.
 *
 * */

void str_echo(int transSocket)
{
    char buf[MAXLINE] = {0};
    bzero(buf, MAXLINE);
    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        write(transSocket, buf, strlen(buf));
        bzero(buf, MAXLINE);
        if(read(transSocket, buf, MAXLINE) > 0)
        {
            printf("server: %s\n", buf);
        }
    }
}

void    ClientBase(char *s_addr)
{
    int cliSocket;
    struct sockaddr_in serveraddr;
    char recvbuf[MAXLINE+1];

    // creat socket
    cliSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == cliSocket)    
    {
        err_sys("create socket fail.\n"); 
    }

    //initialization the struct serveraddr
    bzero(&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERV_PORT);

    if(inet_pton(AF_INET, /*(const char*)*/s_addr, &serveraddr.sin_addr) <= 0)
    {
        err_quit("inet_pton the function exec fail.addrss = %s", s_addr);
    }

    //connect to server
    if(connect(cliSocket, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        err_quit("connect the function exec fail.");
    }

    bzero(recvbuf, sizeof(recvbuf));

    str_echo(cliSocket);
}


int main(int argc, char **argv)
{
    if(argc < 2)
        err_quit("not have enough argument.");

    ClientBase(argv[1]);

    return 0;
}
