#include "../../comm/unp.h"

/*  this is a base client program 
 *
 *  the str_echo function use select deal with socket.
 *  print message terim
 *
 * */

void str_echo(int transSocket)
{
    char buf[MAXLINE] = {0};
    bzero(buf, MAXLINE);

    int inputfd = fileno(stdin);
    fd_set rset;
    FD_ZERO(&rset);

    FD_SET(inputfd, &rset);
    FD_SET(transSocket, &rset);

    int stdflush = 0;
    while(1)
    {
        if(stdflush == 0)
            FD_CLR(inputfd, &rset);
        int max = inputfd > transSocket ? inputfd+1:transSocket+1;
        int ret = select(max, &rset, NULL, NULL, NULL);
        if(ret == -1)
        {
            err_sys("select function fail. errno: %d\n", errno);
            return;
        }

        if(FD_ISSET(transSocket, &rset))
        {
            if(read(transSocket, buf, MAXLINE) > 0 )
            {
                if(stdflush == 1)
                    return;     // alse close.

                puts(buf);
            }

            int res = write(fileno(stdout), buf, MAXLINE);
            if(res != 0)
            {
                FD_CLR(inputfd, &rset);
            }
        }

        if(FD_ISSET(inputfd, &rset))
        {
            if(read(inputfd, buf, MAXLINE) == 0 )
            {
                stdflush = 1;
                shutdown(transSocket, SHUT_WR); //send FIN to server
                FD_CLR(inputfd, &rset);
                continue;
            }
            int res = write(transSocket, buf, MAXLINE);
            if(res != 0)
            {
                err_quit("write fail.");
            }
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
