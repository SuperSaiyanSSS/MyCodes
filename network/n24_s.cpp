// n24_s.cpp : �������̨Ӧ�ó������ڵ㡣
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
#define TARGET_PORT 751
#define MAXSIZE 100
#define DEFAULT_LINE 100
int recvn_len;
DWORD WINAPI ThreadProc(LPVOID clientSocket_p)
{
	char recvbuf[DEFAULT_LINE];

	//����ת��
	SOCKET* clientSocket_p2 = (SOCKET*)clientSocket_p;
	SOCKET clientSocket = *clientSocket_p2;
	int iResult;
	while (1) {

		if (clientSocket != SOCKET_ERROR) {
			cout << "���ӳɹ�" << endl;
		}
		do {
			memset(recvbuf, 0, sizeof(recvbuf));
			iResult = recv(clientSocket, recvbuf, DEFAULT_LINE, 0);
			if (iResult > 0) {
				cout << "���յ� " << recvbuf << endl;
				iResult = send(clientSocket, recvbuf, DEFAULT_LINE, 0);
				if (iResult == SOCKET_ERROR) {
					cout << "����ʧ��" << endl;
					closesocket(clientSocket);
					WSACleanup();
					getchar();
					return -1;
				}
				cout << "�ѷ���" << endl;
			}
			else if (iResult == 0) {
				cout << "�����ر����ӡ�����" << endl;

				closesocket(clientSocket);
				return -1;
			}
			else {
				cout << "����ʱ���ִ��󣬴���" << WSAGetLastError() << endl;
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
	WORD w = MAKEWORD(2, 2);                   //����汾����  


	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult != 0)
	{
		cout << "WSAStartup ����ʧ��" << endl;
		getchar();
		return -1;
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); ;     //��������ʼ�������׽���

	SOCKADDR_IN addr;	//��������ַ

	addr.sin_family = AF_INET;                //��ʼ����ַ�ṹ  
	addr.sin_port = htons(751);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	iResult = bind(listenSocket, (sockaddr*)&addr, sizeof(SOCKADDR_IN));    //���׽���  
	if (iResult == SOCKET_ERROR) {
		cout << "�󶨶˿�ʧ��" << WSAGetLastError() << endl;
		WSACleanup();
		getchar();
		return -1;
	}

	iResult = listen(listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		cout << "����ʧ��" << endl;
		WSACleanup();
		getchar();
		return -1;
	}
	cout << "�������Ѿ����������ڼ����˿�" << endl;

	//������ܻ�������Ĭ�ϴ�С
	char recvbuf[DEFAULT_LINE];
	int len_of_recvbuf = DEFAULT_LINE;


	while (1) {
		cout << "���ڵȴ��ͻ������ӡ�����" << endl;
		SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); ;
		clientSocket = accept(listenSocket, NULL, NULL);
		if (clientSocket != SOCKET_ERROR) {
			cout << "���ӳɹ�" << endl;
		}
		//���̴߳���clientSocket��ַ�������
		HANDLE handle = CreateThread(NULL, 0, ThreadProc, &clientSocket, 0, NULL);
	
	}

	cout << "����" << endl;
	closesocket(listenSocket);
	WSACleanup();
	getchar();


	return 0;
}