// n22_c.cpp : 定义控制台应用程序的入口点。
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

	int iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult)
	{
		cout << "WSAStartup 调用失败，程序退出" << endl;
		getchar();  //暂停，显示在屏幕
		return -1;
	}
	SOCKET s;                                 //定义连接套接字句柄  服务器
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);          //创建TCP套接字  

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(751);

	//不断尝试连接服务器
	while (1) {
		iResult = connect(s, (sockaddr*)&addr, sizeof(SOCKADDR_IN));
		cout << "正在尝试连接服务器..." << endl;
		if (iResult != SOCKET_ERROR) {
			cout << "已成功与服务器建立连接" << endl;
			break;
		}
	}

	//初始化发送缓冲区
	char sendStringArray[DEFAULT_LINE];
	memset(sendStringArray, 0, DEFAULT_LINE);
	char recvline[DEFAULT_LINE];
	memset(recvline, 0, DEFAULT_LINE);
	string input_string;
	string output_string;

	while (1) {
		cout << "请输入要发送的内容" << endl;
		cin >> sendStringArray;
		//输入q时结束
		if (sendStringArray[0] == 'q') {
			break;
		}
		input_string = string(sendStringArray);
		// 加入代表字符串终结的符号
		sendStringArray[input_string.length()] = '\0';
		iResult = send(s, sendStringArray, input_string.length() + 1, 0);
		if (iResult == SOCKET_ERROR) {
			cout << "发送失败" << endl;
			WSACleanup();
			getchar();
			return -1;
		}
		iResult = recv(s, recvline, DEFAULT_LINE, 0);
		while (iResult>0) {
			//由于接受一行数据，所以逐个遍历接收到的数组，当遇到换行符时终止
			if (iResult == 0) {
				cout << "接收完成" << endl;
				break;
			}
			else if (iResult < 0) {
				cout << "连接失败" << endl;
			}
			else {
				int next_flag = 0;
				for (int i = 0; i < DEFAULT_LINE; i++) {
					if (recvline[i] != '\n' && recvline[i] != '\0') {
						output_string += recvline[i];
						//如果遇到换行符或\0标志，则证明这一行句子接收完成
						next_flag = 1;
					}
					else {
						next_flag = 0;
						break;
					}
				}
				//如果next_flag为1 则一行没有接收完成，继续
				if (next_flag == 1) {
					iResult = recv(s, recvline, DEFAULT_LINE, 0);
				}
				else {
					cout << output_string << endl;
					break;
				}
			}
		}
		output_string = "";
	}
	closesocket(s);
	WSACleanup();
	return 0;
}


