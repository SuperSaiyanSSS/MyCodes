// n1_s.cpp : �������̨Ӧ�ó������ڵ㡣
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

int main()
{
	WSADATA data;    
	WORD w = MAKEWORD(2, 2);                   //����汾���� 
	int iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult)
	{
		cout << "WSAStartup ����ʧ�ܣ������˳�" << endl;
		getchar();  //��ͣ����ʾ����Ļ
		return -1;
	}
	SOCKET c;                                 //���������׽��־��
	sockaddr_in addr2;                        //�����׽��ֵ�ַ�ṹ

	cout << "�ͻ�������" << endl;
	c = socket(AF_INET, SOCK_STREAM, 0);
	addr2.sin_family = AF_INET;
	addr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr2.sin_port = htons(751);

	while (1) {
		iResult = connect(c, (sockaddr*)&addr2, sizeof(SOCKADDR_IN));   //���ϳ�������
		cout << "zz" << endl;
		if (iResult != SOCKET_ERROR) {
			break;
		}
	}

	cout << "�ѳɹ�����������" << endl;

	char sendStringArray[100];
	memset(sendStringArray, 0, sizeof(sendStringArray));
	while (1) {
		iResult = recv(c, sendStringArray, 100, 0);

		if (iResult>0) {
			cout << "�ɹ���" << endl;
		}
		else {
			cout << "�Ͽ�!" << endl;
			break;
		}
	}
	cout << "............" << endl;
	printf("%s\n", sendStringArray);
	closesocket(c);
	WSACleanup();
	system("pause");
	return 0;
}

