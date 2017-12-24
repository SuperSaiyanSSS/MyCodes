// n1_c.cpp : 定义控制台应用程序的入口点。
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
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"AdvApi32.lib")
#pragma warning( disable : 4996) 


int testSuccess;    //检测是否成功的flag

int main()
{
	WSADATA data;
	WORD w = MAKEWORD(2, 2);                   //定义版本号码  

	char buf[100];                           //字符串缓冲区
	char recvbuf[1024];

	time_t t;
	//获取系统时间
	t = time(0);
	strftime(buf, sizeof(buf), "%Y/%m/%d %X %A ", localtime(&t));//定义并初始化发送到客户端的字符数组  
	strcat(buf, "\n");
	//memset(buf, '1', sizeof(buf));
	testSuccess = WSAStartup(MAKEWORD(2, 2), &data);   
	if (testSuccess != 0)
	{
		cout << "WSAStartup 调用失败" << endl;
		getchar();
		return -1;
	}

	SOCKET s, client;                            //定义连接套接字和数据收发套接字句柄  

	SOCKADDR_IN addr;	//服务器地址
	SOCKADDR_IN addr2;	//客户端地址


	s = socket(AF_INET, SOCK_STREAM, 0);      //创建TCP套接字  
	

	int n = sizeof(addr2);                    //获取套接字地址结构大小  
	int len = sizeof(SOCKADDR_IN);

	addr.sin_family = AF_INET;                //初始化地址结构  
	addr.sin_port = htons(751);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(s, (sockaddr*)&addr, sizeof(SOCKADDR_IN));    //绑定套接字  
	listen(s, 3);                              //监听套接字  
	cout << "服务器已经启动，正在监听端口" << endl;
	while (1) {

			cout << "正在等待客户端。。。" << endl;
			client = accept(s, (sockaddr*)&addr2, &len);
			if (client != SOCKET_ERROR) {
				cout << "连接成功" << endl;
	
			}


			testSuccess = 1;
			if (testSuccess > 0) {
				testSuccess = send(client, buf, 100, 0);
				cout << "已发送" << endl;
				if (testSuccess == SOCKET_ERROR) {
					cout << "发送数据失败！" << endl;
					cout << WSAGetLastError() << endl;;
					closesocket(client);
					getchar();
					return -1;
				}
				else {
					cout << "666" << endl;
				}
			}
			else if (testSuccess == 0) {
				cout << "连接关闭" << endl;
			}
			else {
				cout << "连接失败.." << endl;
				closesocket(client);
				WSACleanup();
				return -1;
			}


	}
	closesocket(s);
	WSACleanup();

    return 0;
}

