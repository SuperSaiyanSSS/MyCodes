// n23_s.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//�洢���ν��յ�С�ڹ̶����ȵ��ַ���
	string save_string;
	//�洢��Ϣͷ����ı䳤�ĳ���
	int reclen;

	while (1) {
		cout << "���ڵȴ��ͻ������ӡ�����" << endl;
		clientSocket = accept(listenSocket, NULL, NULL);
		if (clientSocket != SOCKET_ERROR) {
			cout << "���ӳɹ�" << endl;
		}
		do {
			//���Ƚ�����Ϣͷ�����䳤�Ƕ��ٳ���
			iResult = recv(clientSocket, (char*)&reclen, sizeof(int), 0);
			if (iResult != sizeof(int)) {
				cout << "�����Ѿ��رա���" << endl;
			}
			//�����ֽ���תΪ�����ֽ���
			//���ﲻ��ת��ת�˳���
			//reclen = ntohl(reclen);
			cnt = reclen;
			cout << "Ҫ�յ��ĳ���Ϊ" << cnt << endl;
			memset(recvbuf, 0, sizeof(recvbuf));
			iResult = recv(clientSocket, recvbuf, cnt, 0);
			if (iResult > 0) {
				while (1) {
					//�����յ����ַ�����С��ָ��ʱ�������ظ����գ�ֱ�����ڵ���Ϊֹ

					cnt -= string(recvbuf).length();
					cout << "cnt " << cnt << endl;
					save_string += string(recvbuf);
					cout << "���յ� " << string(recvbuf) << endl;
					if (cnt <= 0) {
						break;
					}
					memset(recvbuf, 0, sizeof(recvbuf));
					iResult = recv(clientSocket, recvbuf, cnt, 0);
					if (iResult == SOCKET_ERROR) {
						cout << "����ʱ�������" << endl;
						break;
					}

				}
				//�����Ͻ���ƴ�ӱ�����ַ�����ֵ��recvbuf
				save_string.copy(recvbuf, save_string.length(), 0);
				//���ͻؿͻ���
				iResult = send(clientSocket, recvbuf, reclen, 0);
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

		} while (iResult > 0);
	}

	cout << "����" << endl;
	closesocket(clientSocket);
	WSACleanup();
	getchar();


	return 0;
}

