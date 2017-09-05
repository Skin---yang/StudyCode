#include "../../comm/unp.h"

// this is a base sever
// this server use select deal with the client connect.

void ServerBase()
{
    int sevSocket, i;
    struct sockaddr_in serveraddr;
    int  transSocket, connSocket;
    int nready, client[FD_SETSIZE];
    fd_set   reset, allset;
    int maxfd, maxi;
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

    maxfd = sevSocket;
    maxi = -1; // the variable is mean client arrary maximum index.

    // init
    for(i = 0; i < FD_SETSIZE; ++i)
    {
        client[i] = -1;
    }

    FD_ZERO(&allset);
    FD_SET(sevSocket, &allset);
    while(1)
    {
        reset = allset;
        nready = select(sevSocket, &reset, NULL, NULL, NULL);

        if(nready == -1)
            err_quit("function select fail.\n");
        
        if(FD_ISSET(sevSocket, &reset))
        {
            transSocket = accept(sevSocket, NULL, NULL);

            if(nready == -1)
            {
                err_quit("function select fail.\n");    
            }

            for(i = 0; i < FD_SETSIZE; ++i)
            {
                if(client[i] < 0)
                {
                    client[i] = transSocket;
                    break;
                }
            } 

            if(i == FD_SETSIZE)
            {
                err_quit("not have enought descriptot");
            }

            FD_SET(transSocket, &allset);

            if(i > maxi)
                maxi = i;

            // update the maximum
            if(transSocket > maxfd)
                maxfd = transSocket;

            if(--nready <= 0)
                continue;
        }

        // check all client for data
        for(i = 0; i < maxi; ++i)
        {
            if((connSocket = client[i]) < 0)
                continue;

            if(FD_ISSET(connSocket, &reset))
            {
                if(read(connSocket, buf, MAXLINE) == 0)
                {
                    // close and clear the socket
                    close(connSocket);
                    FD_CLR(connSocket, &allset);
                    client[i] = -1;
                }
                else
                {
                    //print the server data
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
