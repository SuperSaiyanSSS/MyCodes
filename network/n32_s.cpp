// n32_s.cpp : �������̨Ӧ�ó������ڵ㡣
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
#define DEFAULT_LINE 100

typedef struct Cnode {
	char recvbuf[DEFAULT_LINE];
	int iResult;
	SOCKET old_s;
	sockaddr_in old_addr;
};


DWORD WINAPI ThreadProc(LPVOID info)
{
	//������������Ķ˿ں�
	srand((unsigned)time(NULL));
	Cnode* info_p = (Cnode*)info;
	cout << "���յ�" << string(info_p->recvbuf, info_p->iResult) << endl;
	int iResult = info_p->iResult;

	//�ڻ���֮ǰ���ȷ����µ�Դ�˿ڣ�Ҫ��ͻ���֮�����ӷ���˵��¶˿�
	int new_port = rand()%10000+5000;
	//intתstring
	stringstream ss;
	ss << new_port;
	string new_port_string;
	ss >> new_port_string;
	//stringתchar[]
	char recvbuf[DEFAULT_LINE];
	new_port_string.copy(recvbuf, new_port_string.length());

	if (iResult > 0) {
		cout << "�ɹ����յ� " << iResult << " ���ֽ�" << endl;
		//��ʾ���յ������ݣ�����iResult��֪���յ����ٸ��ֽڣ��Ӷ��ض�
		cout << string(info_p->recvbuf, iResult) << endl;
		iResult = sendto(info_p->old_s, recvbuf, new_port_string.length(), 0, (sockaddr*)&(info_p->old_addr), sizeof(info_p->old_addr));
		if (iResult == SOCKET_ERROR) {
			cout << "�����¶˿�ʱʧ��" << endl;
			return -1;
		}
		iResult = sendto(info_p->old_s, info_p->recvbuf, iResult, 0, (sockaddr*)&(info_p->old_addr), sizeof(info_p->old_addr));
		if (iResult == SOCKET_ERROR) {
			cout << "��������ʱʧ��" << endl;
			return -1;
		}
		cout << "�ѷ���" << endl;
	}
	else if (iResult == 0) {
		cout << "�����Ѿ��ر�" << endl;
	}
	else {
		cout << "���ճ��ִ���" << endl;
		return -1;
	}


	//����һ���µĶ˿ڣ�����ͻ���ͨ��
	WSADATA data;
	iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult == SOCKET_ERROR) {
		cout << "��ʼ����ַʧ��" << endl;
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);


	if (s == INVALID_SOCKET) {
		cout << "�����׽���ʧ��" << endl;
		cout << WSAGetLastError() << endl;
		return -1;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//�¶˿�
	addr.sin_port = htons(new_port);

	//�󶨵�ַ�Ͷ˿ں�
	//ǿ������ת������sockaddr_in*ת��Ϊsockaddr*
	iResult = bind(s, (sockaddr*)&addr, sizeof(SOCKADDR_IN));
	if (iResult == SOCKET_ERROR) {
		cout << "aaa�󶨶˿�ʧ��" << endl;
		cout << WSAGetLastError() << endl;
		getchar();
		return -1;
	}

	cout << "UDP�µķ������Ѿ��������������������¶˿�" << endl;

	int addr_len = sizeof(addr);
	while (1) {
		//���տͻ��˷��͵����ݣ���ַ���Լ��ĵ�ַ
		iResult = recvfrom(s, recvbuf, DEFAULT_LINE, 0, (sockaddr*)&addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			cout << "��������ʧ��" << endl;
			WSACleanup();
			return -1;
		}
		if (iResult > 0) {
			cout << "�ɹ����յ� " << iResult << " ���ֽ�" << endl;
			//��ʾ���յ������ݣ�����iResult��֪���յ����ٸ��ֽڣ��Ӷ��ض�
			cout << string(recvbuf, iResult) << endl;
			iResult = sendto(s, recvbuf, iResult, 0, (sockaddr*)&addr, sizeof(addr));
			if (iResult == SOCKET_ERROR) {
				cout << "����ʧ��" << endl;
				closesocket(s);
				WSACleanup();
				return 1;
			}
			cout << "�ѷ���" << endl;
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

	

	while (1) {
		cout << "���ڵȴ��ͻ������ӡ�����" << endl;
		//���տͻ��˷��͵����ݣ���ַ���Լ��ĵ�ַ
		iResult = recvfrom(s, recvbuf, DEFAULT_LINE, 0, (sockaddr*)&addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			cout << "��������ʧ��" << endl;
			WSACleanup();
			return -1;
		}
		//���̴߳��ݲ�������Ϣ����ڲ������������ݽṹ��
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
		//���տͻ��˷��͵����ݣ���ַ���Լ��ĵ�ַ
		iResult = recvfrom(s, recvbuf, DEFAULT_LINE, 0, (sockaddr*)&addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			cout << "��������ʧ��" << endl;
			WSACleanup();
			return -1;
		}
		if (iResult > 0) {
			cout << "�ɹ����յ� " << iResult << " ���ֽ�" << endl;
			//��ʾ���յ������ݣ�����iResult��֪���յ����ٸ��ֽڣ��Ӷ��ض�
			cout << string(recvbuf, iResult) << endl;
			iResult = sendto(s, recvbuf, iResult, 0, (sockaddr*)&addr, sizeof(addr));
			if (iResult == SOCKET_ERROR) {
				cout << "����ʧ��" << endl;
				closesocket(s);
				WSACleanup();
				return 1;
			}
			cout << "�ѷ���" << endl;
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
	}
	closesocket(s);
	WSACleanup();

	return 0;
}
