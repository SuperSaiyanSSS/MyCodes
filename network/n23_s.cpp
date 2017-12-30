// n23_s.cpp : 定义控制台应用程序的入口点。
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
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); ;
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
	//统计相对于固定长度剩余多少字节尚未被接收
	int cnt;
	//存储几次接收的小于固定长度的字符串
	string save_string;
	//存储消息头所存的变长的长度
	int reclen;

	while (1) {
		cout << "正在等待客户端连接。。。" << endl;
		clientSocket = accept(listenSocket, NULL, NULL);
		if (clientSocket != SOCKET_ERROR) {
			cout << "连接成功" << endl;
		}
		do {
			//首先接收消息头，即变长是多少长度
			iResult = recv(clientSocket, (char*)&reclen, sizeof(int), 0);
			if (iResult != sizeof(int)) {
				cout << "连接已经关闭。。" << endl;
			}
			//网络字节序转为主机字节序
			//这里不用转，转了出错
			//reclen = ntohl(reclen);
			cnt = reclen;
			cout << "要收到的长度为" << cnt << endl;
			memset(recvbuf, 0, sizeof(recvbuf));
			iResult = recv(clientSocket, recvbuf, cnt, 0);
			if (iResult > 0) {
				while (1) {
					//当接收到的字符数量小于指定时，不断重复接收，直到大于等于为止

					cnt -= string(recvbuf).length();
					cout << "cnt " << cnt << endl;
					save_string += string(recvbuf);
					cout << "接收到 " << string(recvbuf) << endl;
					if (cnt <= 0) {
						break;
					}
					memset(recvbuf, 0, sizeof(recvbuf));
					iResult = recv(clientSocket, recvbuf, cnt, 0);
					if (iResult == SOCKET_ERROR) {
						cout << "接收时意外错误" << endl;
						break;
					}

				}
				//将不断接收拼接保存的字符串赋值给recvbuf
				save_string.copy(recvbuf, save_string.length(), 0);
				//发送回客户端
				iResult = send(clientSocket, recvbuf, reclen, 0);
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
			}
			else {
				cout << "接收时出现错误，代码" << WSAGetLastError() << endl;
				closesocket(clientSocket);
				WSACleanup();
				getchar();
				return -1;
			}

		} while (iResult > 0);
	}

	cout << "结束" << endl;
	closesocket(clientSocket);
	WSACleanup();
	getchar();


	return 0;
}

