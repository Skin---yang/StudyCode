#include "../../comm/unp.h"

/*  this is a base client program by udp
 *
 * */

void dgc_echo(int clifd, struct sockaddr *pcliaddr, socklen_t clilen)
{
    char buf[MAXLINE+10];
    bzero(buf, MAXLINE);
    struct sockaddr servaddr;

    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        socklen_t len = clilen;
        ssize_t res = sendto(clifd, buf, sizeof(buf), 0, pcliaddr, len);
        if(res == -1)
        {
            err_sys("sendto: appear a error. errno = %d\n", errno);
            continue;
        }
        printf("send data : %s", buf);
        
        ssize_t ret = recvfrom(clifd, buf, MAXLINE+10, 0, &servaddr, &len);
        if(ret == -1)
        {
            err_sys("recvfrom: appear a error. errno = %d\n", errno);
            continue;
        }

        if(clilen != len || memcmp(pcliaddr, &servaddr, len) != 0)
        {
            err_sys("not the send data server.\n");
            continue;
        }

        fputs(buf, stdout);
    }
}

void    ClientBase(char *s_addr)
{
    int cliSocket;
    struct sockaddr_in cliaddr;
    char recvbuf[MAXLINE+1];

    // creat socket
    cliSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == cliSocket)    
    {
        err_sys("create socket fail.\n"); 
    }

    //initialization the struct cliaddr
    bzero(&cliaddr, sizeof(cliaddr));

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(SERV_PORT);

    if(inet_pton(AF_INET, s_addr, &cliaddr.sin_addr) <= 0)
    {
        err_quit("inet_pton the function exec fail.addrss = %s", s_addr);
    }

    dgc_echo(cliSocket, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}


int main(int argc, char **argv)
{
    if(argc < 2)
        err_quit("not have enough argument.");

    ClientBase(argv[1]);

    return 0;
}
