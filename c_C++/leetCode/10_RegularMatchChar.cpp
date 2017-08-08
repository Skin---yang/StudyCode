#include "../comm_C++.h"

/*
problem describe:
    '.' Matches any single character.
    '*' Matches zero or more of the preceding element.

    The matching should cover the entire input string (not partial).
    The function prototype should be:
    bool isMatch(const char *s, const char *p)

    Some examples:
    isMatch("aa","a") ?         false
    isMatch("aa","aa") ?        true
    isMatch("aaa","aa") ?       false
    isMatch("aa", "a*") ?       true
    isMatch("aa", ".*") ?       true
    isMatch("ab", ".*") ?       true
    isMatch("aab", "c*a*b") ?   true
 */

bool IsMatch(string s, string p)
{
    if(!s.empty() && p.empty()||(s.length() != p.length() && string::npos==p.find("*")))  return false;
    if(s.find("*")!=string::npos || s.find(".") != string::npos)    return false;   //not can have * and  .
    if(string::npos != p.find(".*") || string::npos != p.find(s))    return true;

    auto slen = s.length();
    auto plen = p.length();
    int sScript = 0;

    auto aBeginScript = str_find(p,s[0],0);
    if(-1 == aBeginScript)
        return false;

    bool bLastCharIsAsterisk = false;

    for(int i = aBeginScript; i < plen; ++i)
    {
        if(sScript < slen)
        {
            if(s[sScript] != p[i])
            {
                if(p[i] == '.')
                {
                    if(bLastCharIsAsterisk) bLastCharIsAsterisk = false;
                    ++sScript;
                    continue;
                }
                else if(p[i] == '*')
                {
                    if(!bLastCharIsAsterisk) bLastCharIsAsterisk = true;
                    //if there are mang duplicate charecters, then move the subscript to the last iteration.
                    if(p[i-1] == s[sScript])
                    {
                        while(1)
                        {
                            if(sScript+1 < slen)
                            {
                                if(s[sScript] == s[sScript+1])
                                {
                                    ++sScript;
                                }
                                else
                                    break;
                            }
                            else
                                return true;
                        }
                    }

                }
                else
                {
                    if(bLastCharIsAsterisk) bLastCharIsAsterisk = false;
                    // continue to find the next character
                    aBeginScript = str_find(p, s[0], aBeginScript);
                    if(-1 == aBeginScript)
                        return false;
                    i = aBeginScript - 1;
                }
            }
            ++sScript;
        }
    }
    
    return true;
}

size_t str_find(const string str, char c, size_t nFlagScript)
{
    auto nlen = str.length();
    for(size_t i = nFlagScript; i < nlen; ++i)
    {
        if(str[i] == c)
        {
            if(i > nFlagScript || nFlagScript == 0)
            {
                return i;
            }
        }
    }
    return -1;
}


int main()
{
    return 0;
}
