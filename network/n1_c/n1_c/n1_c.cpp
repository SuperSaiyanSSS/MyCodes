// n1_c.cpp : �������̨Ӧ�ó������ڵ㡣
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
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"AdvApi32.lib")
#pragma warning( disable : 4996) 


int testSuccess;    //����Ƿ�ɹ���flag

int main()
{
	WSADATA data;
	WORD w = MAKEWORD(2, 2);                   //����汾����  

	char buf[100];                           //�ַ���������
	char recvbuf[1024];

	time_t t;
	//��ȡϵͳʱ��
	t = time(0);
	strftime(buf, sizeof(buf), "%Y/%m/%d %X %A ", localtime(&t));//���岢��ʼ�����͵��ͻ��˵��ַ�����  
	strcat(buf, "\n");
	//memset(buf, '1', sizeof(buf));
	testSuccess = WSAStartup(MAKEWORD(2, 2), &data);   
	if (testSuccess != 0)
	{
		cout << "WSAStartup ����ʧ��" << endl;
		getchar();
		return -1;
	}

	SOCKET s, client;                            //���������׽��ֺ������շ��׽��־��  

	SOCKADDR_IN addr;	//��������ַ
	SOCKADDR_IN addr2;	//�ͻ��˵�ַ


	s = socket(AF_INET, SOCK_STREAM, 0);      //����TCP�׽���  
	

	int n = sizeof(addr2);                    //��ȡ�׽��ֵ�ַ�ṹ��С  
	int len = sizeof(SOCKADDR_IN);

	addr.sin_family = AF_INET;                //��ʼ����ַ�ṹ  
	addr.sin_port = htons(751);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(s, (sockaddr*)&addr, sizeof(SOCKADDR_IN));    //���׽���  
	listen(s, 3);                              //�����׽���  
	cout << "�������Ѿ����������ڼ����˿�" << endl;
	while (1) {

			cout << "���ڵȴ��ͻ��ˡ�����" << endl;
			client = accept(s, (sockaddr*)&addr2, &len);
			if (client != SOCKET_ERROR) {
				cout << "���ӳɹ�" << endl;
	
			}


			testSuccess = 1;
			if (testSuccess > 0) {
				testSuccess = send(client, buf, 100, 0);
				cout << "�ѷ���" << endl;
				if (testSuccess == SOCKET_ERROR) {
					cout << "��������ʧ�ܣ�" << endl;
					cout << WSAGetLastError() << endl;;
					closesocket(client);
					getchar();
					return -1;
				}
				else {
					cout << "666" << endl;
				}
			}
			else if (testSuccess == 0) {
				cout << "���ӹر�" << endl;
			}
			else {
				cout << "����ʧ��.." << endl;
				closesocket(client);
				WSACleanup();
				return -1;
			}


	}
	closesocket(s);
	WSACleanup();

    return 0;
}

