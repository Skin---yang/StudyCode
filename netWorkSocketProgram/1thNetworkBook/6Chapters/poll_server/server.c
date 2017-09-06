#include "../../comm/unp.h"

// this is a base sever
// this server use select deal with the client connect.

void ServerBase()
{
    int sevSocket, i;
    struct sockaddr_in serveraddr;
    int  transSocket, connSocket;
    int nready, 
    struct pollfd client[OPEN_MAX];
    int maxi;
    char buf[MAXLINE];
    bzero(buf, MAXLINE);

    //create
    sevSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(sevSocket < 0)
        err_quit("sevSocket fail\n");

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    // if not use the htons function, the server will bind * port.
    serveraddr.sin_port = htons(SERV_PORT);     

    // INADDR_ANY mean is 0.0.0.0 because a server can have multiple networks cards.
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sevSocket, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
        err_quit("bind fail\n");

    listen(sevSocket, LISTENQ);

    maxi = 0; // the variable is mean client arrary maximum index.

    client[0].fd = sevSocket;
    client[0].events = POLLRDNORM;
    // init
    for(i = 1; i < OPEN_MAX; ++i)
    {
        client[i].fd = -1;
    }

    while(1)
    {
        nready = poll(client, maxi+1, INFTIM); 
        if(nready == -1)
            err_quit("function poll fail.\n");
        
        if(client[0].revents & POLLRDNORM)
        {
            transSocket = accept(sevSocket, NULL, NULL);
            if(transSocket == -1)
                err_quit("function poll fail.\n");

            for(i = 1; i < OPEN_MAX; ++i)
            {
                if(client[i].fd < 0)
                {
                    client[i].fd = transSocket; //save the descript
                    break;
                }
            }

            if(i == OPEN_MAX)
                err_quit("too many client");

            client[i].events = POLLRDNORM;  // set follow events 

            if(maxi < i)
                maxi = i;

            if(--nready <= 0)
                continue;
        }

        // check all client for data
        for(i = 0; i <= maxi; ++i)
        {
            if((connSocket = client[i].fd) < 0)
                continue;
            // clear the buf
            bzero(buf, MAXLINE);
            if(client[i].revents & (POLLRDNORM | POLLERR))
            { 
                if(read(connSocket, buf, MAXLINE) == 0) /* connection close by client*/
                {
                    close(connSocket);
                    client[i].fd = -1;
                }
                else if(read(connSocket, buf, MAXLINE) < 0)
                {
                    /* connection reset by client */
                    close(connSocket);
                    client[i].fd = -1;
                }
                else
                {
                    char sendbuf[MAXLINE+10];
                    sprintf(sendbuf, "server: %s", buf);
                    write(connSocket, sendbuf, sizeof(sendbuf));

                    // print the data
                    puts(buf);
                }

                // not have more socket
                if(--nready <= 0)
                    break;
            }
        }
    }
}

int main(int argc, char **argv)
{
    ServerBase();

    return 0;
}
