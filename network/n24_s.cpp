// n24_s.cpp : 定义控制台应用程序的入口点。
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
#define DEFAULT_LINE 100
int recvn_len;
DWORD WINAPI ThreadProc(LPVOID clientSocket_p)
{
	char recvbuf[DEFAULT_LINE];

	//类型转换
	SOCKET* clientSocket_p2 = (SOCKET*)clientSocket_p;
	SOCKET clientSocket = *clientSocket_p2;
	int iResult;
	while (1) {

		if (clientSocket != SOCKET_ERROR) {
			cout << "连接成功" << endl;
		}
		do {
			memset(recvbuf, 0, sizeof(recvbuf));
			iResult = recv(clientSocket, recvbuf, DEFAULT_LINE, 0);
			if (iResult > 0) {
				cout << "接收到 " << recvbuf << endl;
				iResult = send(clientSocket, recvbuf, DEFAULT_LINE, 0);
				if (iResult == SOCKET_ERROR) {
					cout << "发送失败" << endl;
					closesocket(clientSocket);
					WSACleanup();
					getchar();
					return -1;
				}
				cout << "已发送" << endl;
			}
			else if (iResult == 0) {
				cout << "即将关闭连接。。。" << endl;

				closesocket(clientSocket);
				return -1;
			}
			else {
				cout << "接收时出现错误，代码" << WSAGetLastError() << endl;
				closesocket(clientSocket);

				return -1;
			}
		} while (iResult > 0);
	}
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}


int main()
{
	WSADATA data;
	WORD w = MAKEWORD(2, 2);                   //定义版本号码  


	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult != 0)
	{
		cout << "WSAStartup 调用失败" << endl;
		getchar();
		return -1;
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); ;     //声明并初始化两个套接字

	SOCKADDR_IN addr;	//服务器地址

	addr.sin_family = AF_INET;                //初始化地址结构  
	addr.sin_port = htons(751);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	iResult = bind(listenSocket, (sockaddr*)&addr, sizeof(SOCKADDR_IN));    //绑定套接字  
	if (iResult == SOCKET_ERROR) {
		cout << "绑定端口失败" << WSAGetLastError() << endl;
		WSACleanup();
		getchar();
		return -1;
	}

	iResult = listen(listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		cout << "监听失败" << endl;
		WSACleanup();
		getchar();
		return -1;
	}
	cout << "服务器已经启动，正在监听端口" << endl;

	//定义接受缓冲区，默认大小
	char recvbuf[DEFAULT_LINE];
	int len_of_recvbuf = DEFAULT_LINE;


	while (1) {
		cout << "正在等待客户端连接。。。" << endl;
		SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); ;
		clientSocket = accept(listenSocket, NULL, NULL);
		if (clientSocket != SOCKET_ERROR) {
			cout << "连接成功" << endl;
		}
		//向线程传递clientSocket地址这个参数
		HANDLE handle = CreateThread(NULL, 0, ThreadProc, &clientSocket, 0, NULL);
	
	}

	cout << "结束" << endl;
	closesocket(listenSocket);
	WSACleanup();
	getchar();


	return 0;
}