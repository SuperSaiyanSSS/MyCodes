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

#define TARGET_PORT 751
#define MAXSIZE 100

int main()
{
	WSADATA data;    
	WORD w = MAKEWORD(2, 2);                   //����汾���� 
	int testSuccess = WSAStartup(MAKEWORD(2, 2), &data);
	if (testSuccess)
	{
		cout << "WSAStartup ����ʧ�ܣ������˳�" << endl;
		getchar();  //��ͣ����ʾ����Ļ
		return -1;
	}
	SOCKET s;                                 //���������׽��־��  ������
	SOCKET c;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);          //����TCP�׽���  
	sockaddr_in addr;                         //�����׽��ֵ�ַ�ṹ  
	sockaddr_in addr2;
	addr.sin_family = AF_INET;                //��ʼ����ַ�ṹ  
	addr.sin_port = htons(TARGET_PORT);       //�˿�ΪTARGET_PORT
	addr.sin_addr.s_addr = INADDR_ANY;
	cout << "�ͻ�������" << endl;
	c = socket(AF_INET, SOCK_STREAM, 0);
	addr2.sin_family = AF_INET;
	addr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr2.sin_port = htons(751);

	while (1) {
		testSuccess = connect(c, (sockaddr*)&addr2, sizeof(SOCKADDR_IN));
		cout << "zz" << endl;
		if (testSuccess != SOCKET_ERROR) {
			break;
		}
	}

	cout << "�ѳɹ�����������" << endl;
	//cout << "������ 'query' ��ѯʱ��" << endl;
	//string query;
	//cin >> query;
	char sendStringArray[100];
	memset(sendStringArray, 0, sizeof(sendStringArray));

	testSuccess = recv(c, sendStringArray, 100, 0);
	if (testSuccess != SOCKET_ERROR) {
		cout << "�ɹ���" << endl;
	}
	cout << "............" << endl;
	printf("%s\n", sendStringArray);
	closesocket(c);
	WSACleanup();
	system("pause");
	return 0;
}

