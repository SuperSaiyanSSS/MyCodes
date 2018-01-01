// n33_s.cpp : �������̨Ӧ�ó������ڵ㡣
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

#pragma comment(lib,"Ws2_32.lib")       //��ʾ�����׽��ֿ� 
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
		cout << "��ʼ����ַʧ��" << endl;
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	char recvbuf[DEFAULT_LINE];

	if (s == INVALID_SOCKET) {
		cout << "�����׽���ʧ��" << endl;
		cout << WSAGetLastError() << endl;
		return -1;
	}



	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(THIS_PORT);

	//�󶨵�ַ�Ͷ˿ں�
	//ǿ������ת������sockaddr_in*ת��Ϊsockaddr*
	iResult = bind(s, (sockaddr*)&addr, sizeof(SOCKADDR_IN));
	if (iResult == SOCKET_ERROR) {
		cout << "�󶨶˿�ʧ��" << endl;
		getchar();
		return -1;
	}

	cout << "UDP�������Ѿ�����������" << endl;
	int addr_len = sizeof(addr);
	int recv_size = 5;

	int recv_count = 0;

	cout << "���������ʱ�ں˻������Ĵ�С" << endl;
	cin >> recv_size;
	setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&recv_size, sizeof(recv_size));
	while (1) {
		//���տͻ��˷��͵����ݣ���ַ���Լ��ĵ�ַ
		iResult = recvfrom(s, recvbuf, DEFAULT_LINE, 0, (sockaddr*)&addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			cout << "��������ʧ��" << endl;
			WSACleanup();
			return -1;
		}
		if (iResult > 0) {
			//cout << "�ɹ����յ� " << iResult << " ���ֽ�" << endl;
			//��ʾ���յ������ݣ�����iResult��֪���յ����ٸ��ֽڣ��Ӷ��ض�
			//cout << string(recvbuf, iResult) << endl;
			recv_count++;
			cout << "�Ѿ�������" << recv_count << "����" << endl;

		}
		else if (iResult == 0) {
			cout << "�����Ѿ��ر�" << endl;
		}
		else {
			cout << "���ճ��ִ���" << endl;
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

