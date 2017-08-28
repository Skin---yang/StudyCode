#include "../comm/unp.h"

/* this program is get the byte order of the host*/

union {
   short    s;
   char c[sizeof(short)];
}un;

int main(int argc, char ** argv)
{
    un.s = 0x0102;

    if(un.c[0] == 0x01 && un.c[1] == 0x02)
    {
        printf("this is big-endian\n");
    }
    else if(un.c[0] == 0x02 && un.c[1] == 0x01)
    {
        printf("this is small-endian\n"); 
    }
    else
    {
        printf("sorry, unknown the byte order.\n");
    }

    return 0;
}
