#include "../../comm/unp.h"

/* 
 * this is a base sever by udp
 *
 */

// 
void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
    socklen_t len;
    char buf[MAXLINE];

    while(1)
    {
        len = clilen;
        ssize_t ret = recvfrom(sockfd, buf, MAXLINE, 0, pcliaddr, &len);
        if(ret == -1)
        {
            err_sys("recvfrom: appear a error. errno = %d\n", errno);
            continue;
        }

        printf("recv data: %s", buf);

        char sendbuf[MAXLINE+10];
        bzero(sendbuf, sizeof(sendbuf));
        sprintf(sendbuf, "server: %s", buf);
        ssize_t res = sendto(sockfd, sendbuf, MAXLINE+10, 0, pcliaddr, len);
        if(res == -1)
        {
            err_sys("sendto: appear a error. errno = %d\n", errno);
            continue;
        }
    }
}

void ServerBase()
{
   int sevSocket; 
   struct sockaddr_in serveraddr, cliaddr;

   //create udp socket
   sevSocket = socket(AF_INET, SOCK_DGRAM, 0);
   if(sevSocket < 0)
       err_quit("sevSocket fail\n");

   bzero(&serveraddr, sizeof(serveraddr));
   serveraddr.sin_family = AF_INET;
   serveraddr.sin_port = htons(SERV_PORT);  // if not use the htons function, the server will bind * port.
   // INADDR_ANY mean is 0.0.0.0 because a server can have multiple networks cards.
   serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
   if(bind(sevSocket, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
       err_quit("bind fail\n");
    
   dg_echo(sevSocket, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
}


int main(int argc, char **argv)
{
    ServerBase();

    return 0;
}
