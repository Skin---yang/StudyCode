#include <iostream>
#include <memory>
#include <string.h>

using namespace std;

struct Stru_Demo
{
	int a;
	int pLen;
	char pstr[255];
};
int main()
{
	Stru_Demo demo;
	demo.a = 100;
	memcpy(demo.pstr, "hello,world!", sizeof("hello,world!"));
	demo.pLen = sizeof("hello,world!");

	//序列化
	size_t nLen = sizeof(int);
	int nbufLen = nLen + demo.pLen;
char *pBuf = new char(nbufLen + 1);
char *pNext = pBuf;
memcpy(pNext, &demo.a, sizeof(int));
pNext = pNext + sizeof(int);
memcpy(pNext, &demo.pLen, sizeof(int));
pNext = pNext + sizeof(int);
memcpy(pNext, demo.pstr, demo.pLen);
//反序列化
char *pValue = pBuf;
cout << *(int*)pValue << endl;//输出的是100 对应的是demo.a
//	pNext = pValue;
//	cout << *(int*)(pNext + 4) << endl;//对应的是demo.pLen
//cout << (char *)p << endl;//对应最后一个了
delete pBuf;
return 0;
}
