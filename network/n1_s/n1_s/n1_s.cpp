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

#define TARGET_PORT 751
#define MAXSIZE 100

int main()
{
	WSADATA data;    
	WORD w = MAKEWORD(2, 2);                   //定义版本号码 
	int testSuccess = WSAStartup(MAKEWORD(2, 2), &data);
	if (testSuccess)
	{
		cout << "WSAStartup 调用失败，程序退出" << endl;
		getchar();  //暂停，显示在屏幕
		return -1;
	}
	SOCKET s;                                 //定义连接套接字句柄  服务器
	SOCKET c;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);          //创建TCP套接字  
	sockaddr_in addr;                         //定义套接字地址结构  
	sockaddr_in addr2;
	addr.sin_family = AF_INET;                //初始化地址结构  
	addr.sin_port = htons(TARGET_PORT);       //端口为TARGET_PORT
	addr.sin_addr.s_addr = INADDR_ANY;
	cout << "客户端启动" << endl;
	c = socket(AF_INET, SOCK_STREAM, 0);
	addr2.sin_family = AF_INET;
	addr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr2.sin_port = htons(751);

	while (1) {
		testSuccess = connect(c, (sockaddr*)&addr2, sizeof(SOCKADDR_IN));
		cout << "zz" << endl;
		if (testSuccess != SOCKET_ERROR) {
			break;
		}
	}

	cout << "已成功连到服务器" << endl;
	//cout << "请输入 'query' 查询时间" << endl;
	//string query;
	//cin >> query;
	char sendStringArray[100];
	memset(sendStringArray, 0, sizeof(sendStringArray));

	testSuccess = recv(c, sendStringArray, 100, 0);
	if (testSuccess != SOCKET_ERROR) {
		cout << "成功！" << endl;
	}
	cout << "............" << endl;
	printf("%s\n", sendStringArray);
	closesocket(c);
	WSACleanup();
	system("pause");
	return 0;
}

