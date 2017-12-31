// n32_s.cpp : 定义控制台应用程序的入口点。
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
#define DEFAULT_LINE 100

typedef struct Cnode {
	char recvbuf[DEFAULT_LINE];
	int iResult;
	SOCKET old_s;
	sockaddr_in old_addr;
};


DWORD WINAPI ThreadProc(LPVOID info)
{
	//用于生成随机的端口号
	srand((unsigned)time(NULL));
	Cnode* info_p = (Cnode*)info;
	cout << "接收到" << string(info_p->recvbuf, info_p->iResult) << endl;
	int iResult = info_p->iResult;

	//在回显之前，先发送新的源端口，要求客户端之后连接服务端的新端口
	int new_port = rand()%10000+5000;
	//int转string
	stringstream ss;
	ss << new_port;
	string new_port_string;
	ss >> new_port_string;
	//string转char[]
	char recvbuf[DEFAULT_LINE];
	new_port_string.copy(recvbuf, new_port_string.length());

	if (iResult > 0) {
		cout << "成功接收到 " << iResult << " 个字节" << endl;
		//显示接收到的数据，根据iResult得知接收到多少个字节，从而截断
		cout << string(info_p->recvbuf, iResult) << endl;
		iResult = sendto(info_p->old_s, recvbuf, new_port_string.length(), 0, (sockaddr*)&(info_p->old_addr), sizeof(info_p->old_addr));
		if (iResult == SOCKET_ERROR) {
			cout << "发送新端口时失败" << endl;
			return -1;
		}
		iResult = sendto(info_p->old_s, info_p->recvbuf, iResult, 0, (sockaddr*)&(info_p->old_addr), sizeof(info_p->old_addr));
		if (iResult == SOCKET_ERROR) {
			cout << "发送数据时失败" << endl;
			return -1;
		}
		cout << "已发送" << endl;
	}
	else if (iResult == 0) {
		cout << "连接已经关闭" << endl;
	}
	else {
		cout << "接收出现错误" << endl;
		return -1;
	}


	//开启一个新的端口，与其客户端通信
	WSADATA data;
	iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult == SOCKET_ERROR) {
		cout << "初始化地址失败" << endl;
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);


	if (s == INVALID_SOCKET) {
		cout << "建立套接字失败" << endl;
		cout << WSAGetLastError() << endl;
		return -1;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//新端口
	addr.sin_port = htons(new_port);

	//绑定地址和端口号
	//强制类型转换，将sockaddr_in*转化为sockaddr*
	iResult = bind(s, (sockaddr*)&addr, sizeof(SOCKADDR_IN));
	if (iResult == SOCKET_ERROR) {
		cout << "aaa绑定端口失败" << endl;
		cout << WSAGetLastError() << endl;
		getchar();
		return -1;
	}

	cout << "UDP新的服务器已经启动。。。正在侦听新端口" << endl;

	int addr_len = sizeof(addr);
	while (1) {
		//接收客户端发送的数据，地址是自己的地址
		iResult = recvfrom(s, recvbuf, DEFAULT_LINE, 0, (sockaddr*)&addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			cout << "接收数据失败" << endl;
			WSACleanup();
			return -1;
		}
		if (iResult > 0) {
			cout << "成功接收到 " << iResult << " 个字节" << endl;
			//显示接收到的数据，根据iResult得知接收到多少个字节，从而截断
			cout << string(recvbuf, iResult) << endl;
			iResult = sendto(s, recvbuf, iResult, 0, (sockaddr*)&addr, sizeof(addr));
			if (iResult == SOCKET_ERROR) {
				cout << "发送失败" << endl;
				closesocket(s);
				WSACleanup();
				return 1;
			}
			cout << "已发送" << endl;
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
	}
	closesocket(s);
	WSACleanup();
	return 0;
}


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

	

	while (1) {
		cout << "正在等待客户端连接。。。" << endl;
		//接收客户端发送的数据，地址是自己的地址
		iResult = recvfrom(s, recvbuf, DEFAULT_LINE, 0, (sockaddr*)&addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			cout << "接收数据失败" << endl;
			WSACleanup();
			return -1;
		}
		//向线程传递参数，信息存放在参数所属的数据结构中
		Cnode* info = (Cnode*)malloc(sizeof(Cnode));
		info->iResult = iResult;
		for (int i = 0; i < iResult; i++) {
			info->recvbuf[i] = recvbuf[i];
		}
		info->old_s = s;
		info->old_addr = addr;
		HANDLE handle = CreateThread(NULL, 0, ThreadProc, info, 0, NULL);
	}

	while (1) {
		//接收客户端发送的数据，地址是自己的地址
		iResult = recvfrom(s, recvbuf, DEFAULT_LINE, 0, (sockaddr*)&addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			cout << "接收数据失败" << endl;
			WSACleanup();
			return -1;
		}
		if (iResult > 0) {
			cout << "成功接收到 " << iResult << " 个字节" << endl;
			//显示接收到的数据，根据iResult得知接收到多少个字节，从而截断
			cout << string(recvbuf, iResult) << endl;
			iResult = sendto(s, recvbuf, iResult, 0, (sockaddr*)&addr, sizeof(addr));
			if (iResult == SOCKET_ERROR) {
				cout << "发送失败" << endl;
				closesocket(s);
				WSACleanup();
				return 1;
			}
			cout << "已发送" << endl;
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
	}
	closesocket(s);
	WSACleanup();

	return 0;
}
