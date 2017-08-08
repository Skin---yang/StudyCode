#include "comm.h"

#define MAX_LEN 256

int copy_something(char *buf, int len)
{
    char mybuf[MAX_LEN];
    if(len > MAX_LEN){ // <---- [1]
        printf("111111111111");
        return -1;
    }
 
    return memcpy(mybuf, buf, len);
}

int main()
{
    char buf[MAX_LEN]={0};
    copy_something(buf,-2147483649);

    return 0;
}
