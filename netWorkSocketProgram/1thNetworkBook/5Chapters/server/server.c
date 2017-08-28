#include "../../comm/unp.h"

void ServerBase()
{
   int sevSocket; 
   struct sockaddr serveraddr;
   int  transSocket;

   //create
   sevScoket = socket(AF_INET, SOCK_STREAM, 0);
   if(sevSocket < 0)
       err_quit("sevSocket fail\n");

   bzero(&serveraddr, sizeof(serveraddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = SERV_PORT;
   servaddr.sin_addr.s_addr = INADDR_ANY;
  
   if(bind(sevSocket, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) <= 0)
       err_quit("bind fail\n");

   listen(sevSocket, LISTENQ);

   while(1)
   {
       transSocket = accept(sevSocket, NULL, NULL);

   }
}


int main(int argc, char **argv)
{


    return 0;
}
