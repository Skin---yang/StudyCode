#include "../../comm/unp.h"

/* base client program */

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
    
    severaddr.sin_family = AF_INET;
    severaddr.sin_port = SERV_PORT;

    if(inet_pton(AF_INET, /*(const char*)*/s_addr, &serveraddr.sin_addr) <= 0)
    {
        err_quit("inet_pton the function exec fail.addrss = %s", s_addr);
    }

    //connect to server
    if(connect(cliSocket, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) <= 0)
    {
        err_quit("connect the function exec fail.");
    }

    bzero(recvbuf, sizeof(recvbuf));
    
    while(1)
    {
        if(read(cliSocket, recvbuf, MAXLINE) < 0)
        {
            err_quit("read buf is empty.\n");
        }

        fputs(recvbuf, stdout);

        if(strcmp(recvbuf, "quit") == 0)
            break;
    }
}


int main(int argc, char **argv)
{
    if(argc < 2)
        err_quit("not have enough argument.");

    ClientBase(argv[1]);

    return 0;
}
