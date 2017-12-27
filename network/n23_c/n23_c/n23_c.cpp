// n23_c.cpp : 定义控制台应用程序的入口点。
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
	memset(sendStringArray, 0, sizeof(sendStringArray));
	char recvline[DEFAULT_LINE];
	memset(recvline, 0, sizeof(recvline));
	string input_string;
	string output_string;
	//要发送的数据的长度
	unsigned int send_length;
	//剩余要发送的长度
	unsigned int cnt;
	//保存每次获得的各段字符串
	string save_string;

	while (1) {
		cout << "请输入要发送的数据的长度" << endl;
		cin >> send_length;
		cnt = send_length;

		//输入'q'时结束
		if (char(cnt) == 'q') {
			break;
		}

		iResult = send(s, (char*)&send_length, sizeof(unsigned int), 0);
		if (iResult == SOCKET_ERROR) {
			cout << "发送消息头(要发送的数据长度)时失败，悲哀" << endl;
			WSACleanup();
			getchar();
			return -1;
		}

		
		do {
			cout << "请输入变长的要发送的内容，还剩下 " << cnt << " 个字符" << endl;
			memset(sendStringArray, 0, sizeof(sendStringArray));
			cin >> sendStringArray;

			input_string = string(sendStringArray);
			sendStringArray[input_string.length()] = '\0';
			cout << "要发送的长度" << input_string.length()+1 << endl;
			iResult = send(s, sendStringArray, input_string.length()+1, 0);

			if (iResult == SOCKET_ERROR) {
				cout << "发送失败" << endl;
				WSACleanup();
				getchar();
				return -1;
			}
			cnt -= input_string.length();

		} while (cnt > 0);
		
		if (cnt < 0) {
			cout << "发送的数据超过了事先声明的变长的长度!" << endl;
		}

		//发送变长数据完毕后，由于长度已知，所以接收长度为变长长度的数据
		cnt = send_length;
		do {
			iResult = recv(s, recvline, send_length, 0);
			output_string = string(recvline);
			cnt -= output_string.length();
			save_string += output_string;

		} while (cnt>0);

		output_string = save_string;
		cout << "echo: " << output_string << endl;
		output_string = "";
		save_string = "";
		
	}
	closesocket(s);
	WSACleanup();
	return 0;
}

