#include <iostream>
using namespace std;
#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc1(LPVOID lpParameter);
DWORD WINAPI ThreadProc2(LPVOID lpParameter);
HANDLE hMutex;
int counter=0,accnt1=0,accnt2=0,tmp1,tmp2,r;
void main()
{
    printf("开始服务:\n");
    HANDLE handle1=CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);
    HANDLE handle2=CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);
    CloseHandle(handle1);
    CloseHandle(handle2);
    hMutex=CreateMutex(NULL,FALSE,NULL);
/*控制主进程运行时间*/
    Sleep(5000);
    printf("服务结束\n");
    //getchar();//VS2008
}


DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
    while (accnt1+accnt2==0)
    {
        WaitForSingleObject(hMutex,INFINITE);
        tmp1=accnt1;
        tmp2=accnt2;
        r=rand();
        accnt1=tmp1+r;
        accnt2=tmp2-r;
        counter++;
        printf("账户A完成转账--%d\n",counter);
        Sleep(100);
        ReleaseMutex(hMutex);
    }
    //printf("第%d次转账发生错误",counter);
    return 0;
    }

    DWORD WINAPI ThreadProc2(LPVOID lpParameter)
    {

    while (accnt1+accnt2==0)
    {
        WaitForSingleObject(hMutex,INFINITE);
        tmp1=accnt1;
        tmp2=accnt2;
        r=rand();
        accnt1=tmp1+r;
        accnt2=tmp2-r;
        counter++;
        printf("账户B完成转账--%d\n",counter);
        Sleep(100);
        ReleaseMutex(hMutex);
    }
    //printf("第%d次转账发生错误",counter);
    return 0;
}
