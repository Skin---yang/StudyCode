#include "../comm_C++.h"

//this code can solution the problem,but it will take a lot of time. 205ms
bool isPalindromeNumber(int x)
{
    bool isYes = false;
    int i, j;
    if(x < 0)
        return isYes;
    string str  = to_string(x);
    auto nlen = str.length();
    if(nlen <= 1)
        isYes = true;

    for(i = 0; i < nlen; ++i)
    {
        j = nlen - i - 1;
        if(i <= j)
        {
            if(str[i] == str[j])
            { 
                continue;
            }
            else
                break;
        }
        else
        {
            isYes = true;
            break;
        }
    } 
    return isYes;
}


//this is best solution way on leetcode. spent 58ms times and shorter.
//i need more thought.
bool IsPalindormeNumber_SpentsTimesLess(int x)
{
    if ((x<0)||(x!=0&&x%10==0)) 
        return false;
    int res=0;
    while (x>res) 
    {
        res=res*10+x%10;
        x=x/10;
    }
    return res==x || res/10==x;//(res/10==x)this is a one-digit case.
}



int main(int argc, char **argv)
{

    return 0;
}
