//this programing is a test.
//vfork a process and return in the child process.
//

//you can get the difference between vfork and fork by manual. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char**argv)
{
    // now create a process by vfork
    pid_t vPid;
    vPid = vfork();
    if(vPid == 0)
    {
        printf("this child pid = %d\n", getpid());
        //return 0; can not use return,beaceuse return will callback the memory space. note: parent and child process shared memory space.
        exit(1);
    }

    printf("this parent pid = %d\n", getpid());

    


    return 0;	
}
