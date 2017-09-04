#include "../../comm/unp.h"

// this is a base sever
// if hava a client conncet and sent a data to the server. the server will use the data answer client.

void sig_chld(int a)
{
    pid_t pid;
    int stat;

    //pid = wait(&stat);
    //if have some process exit on time. need the waitpid

    while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
        printf("this process end. pid : %d\n", pid);

    return;
}

void str_echo(int transSocket)
{
    if(transSocket == -1)
    {
        err_quit("the socket is invalid");
    }

    char buf[MAXLINE];
    int nData = 0;
again:
    bzero(buf, MAXLINE);
    while((nData = read(transSocket, buf, MAXLINE)) > 0)
    {
        write(transSocket, buf, nData);
        printf("client: %s\n", buf);
    }

    if(nData < 0 && errno == EINTR)
        goto again;
    else if(nData < 0)
    {
        err_sys("str_echo function read fuction err.");
    }
}

void ServerBase()
{
   int sevSocket; 
   struct sockaddr_in serveraddr;
   int  transSocket;
   pid_t childpid;

   //create
   sevSocket = socket(AF_INET, SOCK_STREAM, 0);
   if(sevSocket < 0)
       err_quit("sevSocket fail\n");

   bzero(&serveraddr, sizeof(serveraddr));
   serveraddr.sin_family = AF_INET;
   serveraddr.sin_port = htons(SERV_PORT);  // if not use the htons function, the server will bind * port.
   // INADDR_ANY mean is 0.0.0.0 because a server can have multiple networks cards.
   serveraddr.sin_addr.s_addr = INADDR_ANY;
  
   if(bind(sevSocket, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
       err_quit("bind fail\n");

   listen(sevSocket, LISTENQ);

   // capture the child process exit signal
   //signal(SIGCHLD, sig_chld);
   while(1)
   {
       transSocket = accept(sevSocket, NULL, NULL);
       if(transSocket < 0)
       {
           if(errno == EINTR)
           {
               continue;
           }
           else
           {
               err_sys("accept error.errno: %d\n", errno);
           }
       }
       
       // create a process deal with a client
       if((childpid = fork()) == 0)
       {
            str_echo(transSocket);
            exit(0);
       }
       close(transSocket);      // parent process close connected socket
   }
}


int main(int argc, char **argv)
{
    ServerBase();

    return 0;
}
