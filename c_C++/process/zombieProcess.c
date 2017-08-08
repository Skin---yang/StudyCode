#include "../comm.h"


int main()
{
    pid_t pid;

    pid = fork();
    if(pid < 0)
    {
        printf("this fork process fail.\n");
    }
    else if(pid == 0)
    {
        exit(0);
    }
    else
    {
        sleep(60);
        wait(NULL);
    }


    return 0;
}
