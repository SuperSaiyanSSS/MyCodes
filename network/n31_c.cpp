// n31_c.cpp : 定义控制台应用程序的入口点。
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
#define TARGET_PORT 27015
#define MAXSIZE 100
#define DEFAULT_LINE 100

int main()
{
	WSADATA data;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult == SOCKET_ERROR) {
		cout << "初始化地址失败" << endl;
		return -1;
	}
	SOCKET ConnectSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (ConnectSocket == INVALID_SOCKET) {
		cout << "建立套接字失败" << endl;
		return -1;
	}


	string send_string;
	char sendbuf[DEFAULT_LINE];
	char recvbuf[DEFAULT_LINE];
	

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(TARGET_PORT);

	cout << "输入q结束" << endl;
	cout << "--------------" << endl;
	while (1) {
		cin >> send_string;
		if (send_string == "q") {
			closesocket(ConnectSocket);
			break;
		}
		send_string.copy(sendbuf, send_string.length());
		iResult = sendto(ConnectSocket, sendbuf, send_string.length(), 0, (sockaddr*)&addr, sizeof(addr));
		if (iResult == SOCKET_ERROR) {
			cout << "发送数据失败" << endl;
			return -1;
		}
		//cout << "已发送" << endl;
		iResult = recvfrom(ConnectSocket, recvbuf, DEFAULT_LINE, 0, NULL, NULL);
		if (iResult > 0) {
			cout << string(recvbuf, iResult) << endl;
		}
		else if (iResult == 0) {
			cout << "连接已经关闭" << endl;
		}
		else {
			cout << "接收失败" << endl;
		}
	}
	WSACleanup();

    return 0;
}

