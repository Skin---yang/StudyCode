#include "../../comm/unp.h"

/*  this is a base client program 
 *
 *  the connection server will send data to the server after the success of the server.
 *  last, the server will answer the same data.
 *
 * */

void str_echo(int transSocket)
{
    char buf[MAXLINE] = {0}; // this buf is small compare with the recieve buf
    bzero(buf, MAXLINE);

    int fd = fileno(stdin);
    fd_set reset;
    
    int stdflush = 0;
    FD_ZERO(&reset);
    while(1)
    {   
        if(!stdflush)
            FD_SET(fd, &reset);

        FD_SET(transSocket, &reset);
        int max = (fd > transSocket) ? fd+1:transSocket+1;
        int ret = select(max, &reset, NULL, NULL, NULL);
        if(ret == -1)
        {
            err_quit("select function fail. errno: %d\n", errno);
        }
        
        if(FD_ISSET(transSocket, &reset))
        {
            bzero(buf, MAXLINE);
            if(read(transSocket, buf, MAXLINE) == 0)
            {
                //  close the write. so not read the buf
                if(stdflush == 1)
                    return;
                else
                    err_quit("server terminaed prematurely.\n");
            }
            printf("%s", buf);
        }

        if(FD_ISSET(fd, &reset))
        {
            if(fgets(buf, MAXLINE, stdin) == 0)
            {
                stdflush = 1;

                // close the write socket
                int res = shutdown(transSocket, SHUT_WR);
                if(res != 0)
                    err_quit("server terminaed prematurely.\n");

                FD_CLR(fd, &reset);//clear
                continue;
            }
            write(transSocket, buf, strlen(buf));
        }
    }
}

void    ClientBase(char *s_addr)
{
    int cliSocket;
    struct sockaddr_in serveraddr;

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

    str_echo(cliSocket);
}


int main(int argc, char **argv)
{
    if(argc < 2)
        err_quit("not have enough argument.");

    ClientBase(argv[1]);

    return 0;
}
