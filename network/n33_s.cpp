// n33_s.cpp : 定义控制台应用程序的入口点。
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
#define THIS_PORT 27015
#define MAXSIZE 100
#define DEFAULT_LINE 10

int main()
{
	WSADATA data;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult == SOCKET_ERROR) {
		cout << "初始化地址失败" << endl;
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	char recvbuf[DEFAULT_LINE];

	if (s == INVALID_SOCKET) {
		cout << "建立套接字失败" << endl;
		cout << WSAGetLastError() << endl;
		return -1;
	}



	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(THIS_PORT);

	//绑定地址和端口号
	//强制类型转换，将sockaddr_in*转化为sockaddr*
	iResult = bind(s, (sockaddr*)&addr, sizeof(SOCKADDR_IN));
	if (iResult == SOCKET_ERROR) {
		cout << "绑定端口失败" << endl;
		getchar();
		return -1;
	}

	cout << "UDP服务器已经启动。。。" << endl;
	int addr_len = sizeof(addr);
	int recv_size = 5;

	int recv_count = 0;

	cout << "请输入接收时内核缓存区的大小" << endl;
	cin >> recv_size;
	setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&recv_size, sizeof(recv_size));
	while (1) {
		//接收客户端发送的数据，地址是自己的地址
		iResult = recvfrom(s, recvbuf, DEFAULT_LINE, 0, (sockaddr*)&addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			cout << "接收数据失败" << endl;
			WSACleanup();
			return -1;
		}
		if (iResult > 0) {
			//cout << "成功接收到 " << iResult << " 个字节" << endl;
			//显示接收到的数据，根据iResult得知接收到多少个字节，从而截断
			//cout << string(recvbuf, iResult) << endl;
			recv_count++;
			cout << "已经接收了" << recv_count << "个包" << endl;

		}
		else if (iResult == 0) {
			cout << "连接已经关闭" << endl;
		}
		else {
			cout << "接收出现错误" << endl;
			closesocket(s);
			WSACleanup();
			return -1;
		}
		Sleep(3000);
	}
	closesocket(s);
	WSACleanup();

	return 0;
}

