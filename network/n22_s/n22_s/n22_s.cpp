// n22_s.cpp : �������̨Ӧ�ó������ڵ㡣
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

int main()
{
	WSADATA data;
	WORD w = MAKEWORD(2, 2);                   //����汾����  

	int recvn_len;
	cout << "�����붨��" << endl;
	cin >> recvn_len;

	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult != 0)
	{
		cout << "WSAStartup ����ʧ��" << endl;
		getchar();
		return -1;
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); ;     //��������ʼ�������׽���
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); ;
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
	//ͳ������ڹ̶�����ʣ������ֽ���δ������
	int cnt;
	cnt = recvn_len;
	//�洢���ν��յ�С�ڹ̶����ȵ��ַ���
	string save_string;

	while (1) {
		cout << "���ڵȴ��ͻ������ӡ�����" << endl;
		clientSocket = accept(listenSocket, NULL, NULL);
		if (clientSocket != SOCKET_ERROR) {
			cout << "���ӳɹ�" << endl;
		}
		do {
			iResult = recv(clientSocket, recvbuf, recvn_len, 0);
			if (iResult > 0) {
				while (1) {
					cout << "���յ� " << recvbuf << endl;
					cnt -= string(recvbuf).length();
					cout << "cnt " << cnt << endl;
					save_string += string(recvbuf);
					if (cnt <= 0) {
						break;
					}
					iResult = recv(clientSocket, recvbuf, recvn_len, 0);
					if (iResult == SOCKET_ERROR) {
						cout << "����ʱ�������" << endl;
						break;
					}

				}
				save_string.copy(recvbuf, save_string.length(), 0);
				iResult = send(clientSocket, recvbuf, recvn_len, 0);
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
			}
			else {
				cout << "����ʱ���ִ��󣬴���" << WSAGetLastError() << endl;
				closesocket(clientSocket);
				WSACleanup();
				getchar();
				return -1;
			}
			cnt = recvn_len;
		} while (iResult > 0);
	}

	cout << "����" << endl;
	closesocket(clientSocket);
	WSACleanup();
	getchar();


	return 0;
}


