// n1_s.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<winsock2.h>
#include<WS2tcpip.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include<time.h>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")       //显示连接套接字库 
#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"AdvApi32.lib")
#pragma warning( disable : 4996) 
#define TARGET_PORT 751
#define MAXSIZE 100

int main()
{
	WSADATA data;    
	WORD w = MAKEWORD(2, 2);                   //定义版本号码 
	int iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult)
	{
		cout << "WSAStartup 调用失败，程序退出" << endl;
		getchar();  //暂停，显示在屏幕
		return -1;
	}
	SOCKET c;                                 //定义连接套接字句柄
	sockaddr_in addr2;                        //定义套接字地址结构

	cout << "客户端启动" << endl;
	c = socket(AF_INET, SOCK_STREAM, 0);
	addr2.sin_family = AF_INET;
	addr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr2.sin_port = htons(751);

	while (1) {
		iResult = connect(c, (sockaddr*)&addr2, sizeof(SOCKADDR_IN));   //不断尝试连接
		cout << "zz" << endl;
		if (iResult != SOCKET_ERROR) {
			break;
		}
	}

	cout << "已成功连到服务器" << endl;

	char sendStringArray[100];
	memset(sendStringArray, 0, sizeof(sendStringArray));
	while (1) {
		iResult = recv(c, sendStringArray, 100, 0);

		if (iResult>0) {
			cout << "成功！" << endl;
		}
		else {
			cout << "断开!" << endl;
			break;
		}
	}
	cout << "............" << endl;
	printf("%s\n", sendStringArray);
	closesocket(c);
	WSACleanup();
	system("pause");
	return 0;
}

