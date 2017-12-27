// n23_c.cpp : �������̨Ӧ�ó������ڵ㡣
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

	int iResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (iResult)
	{
		cout << "WSAStartup ����ʧ�ܣ������˳�" << endl;
		getchar();  //��ͣ����ʾ����Ļ
		return -1;
	}
	SOCKET s;                                 //���������׽��־��  ������
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);          //����TCP�׽���  

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(751);

	//���ϳ������ӷ�����
	while (1) {
		iResult = connect(s, (sockaddr*)&addr, sizeof(SOCKADDR_IN));
		cout << "���ڳ������ӷ�����..." << endl;
		if (iResult != SOCKET_ERROR) {
			cout << "�ѳɹ����������������" << endl;
			break;
		}
	}

	//��ʼ�����ͻ�����
	char sendStringArray[DEFAULT_LINE];
	memset(sendStringArray, 0, sizeof(sendStringArray));
	char recvline[DEFAULT_LINE];
	memset(recvline, 0, sizeof(recvline));
	string input_string;
	string output_string;
	//Ҫ���͵����ݵĳ���
	unsigned int send_length;
	//ʣ��Ҫ���͵ĳ���
	unsigned int cnt;
	//����ÿ�λ�õĸ����ַ���
	string save_string;

	while (1) {
		cout << "������Ҫ���͵����ݵĳ���" << endl;
		cin >> send_length;
		cnt = send_length;

		//����'q'ʱ����
		if (char(cnt) == 'q') {
			break;
		}

		iResult = send(s, (char*)&send_length, sizeof(unsigned int), 0);
		if (iResult == SOCKET_ERROR) {
			cout << "������Ϣͷ(Ҫ���͵����ݳ���)ʱʧ�ܣ�����" << endl;
			WSACleanup();
			getchar();
			return -1;
		}

		
		do {
			cout << "������䳤��Ҫ���͵����ݣ���ʣ�� " << cnt << " ���ַ�" << endl;
			memset(sendStringArray, 0, sizeof(sendStringArray));
			cin >> sendStringArray;

			input_string = string(sendStringArray);
			sendStringArray[input_string.length()] = '\0';
			cout << "Ҫ���͵ĳ���" << input_string.length()+1 << endl;
			iResult = send(s, sendStringArray, input_string.length()+1, 0);

			if (iResult == SOCKET_ERROR) {
				cout << "����ʧ��" << endl;
				WSACleanup();
				getchar();
				return -1;
			}
			cnt -= input_string.length();

		} while (cnt > 0);
		
		if (cnt < 0) {
			cout << "���͵����ݳ��������������ı䳤�ĳ���!" << endl;
		}

		//���ͱ䳤������Ϻ����ڳ�����֪�����Խ��ճ���Ϊ�䳤���ȵ�����
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

