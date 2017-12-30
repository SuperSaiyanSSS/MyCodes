// n21_c.cpp : �������̨Ӧ�ó������ڵ㡣
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

	while (1) {
		cout << "������Ҫ���͵�����" << endl;
		cin >> sendStringArray;
		//����qʱ����
		if (sendStringArray[0] == 'q') {
			break;
		}
		input_string = string(sendStringArray);
		// ���뻻�з��ʹ����ַ����ս�ķ���
		sendStringArray[input_string.length()] = '\n';
		sendStringArray[input_string.length() + 1] = '\0';
		iResult = send(s, sendStringArray, input_string.length() + 2, 0);
		if (iResult == SOCKET_ERROR) {
			cout << "����ʧ��" << endl;
			WSACleanup();
			getchar();
			return -1;
		}
		iResult = recv(s, recvline, DEFAULT_LINE, 0);
		while (iResult>0) {
			//���ڽ���һ�����ݣ���������������յ������飬���������з�ʱ��ֹ
			if (iResult == 0) {
				cout << "�������" << endl;
				break;
			}
			else if (iResult < 0) {
				cout << "����ʧ��" << endl;
			}
			else{
				int next_flag = 0;
				for (int i = 0; i < DEFAULT_LINE; i++) {
					if (recvline[i] != '\n' && recvline[i] != '\0') {
						output_string += recvline[i];
						//����������з���\0��־����֤����һ�о��ӽ������
						next_flag = 1;
					}
					else {
						next_flag = 0;
						break;
					}
				}
				//���next_flagΪ1 ��һ��û�н�����ɣ�����
				if (next_flag == 1) {
					iResult = recv(s, recvline, DEFAULT_LINE, 0);
				}
				else {
					cout << output_string << endl;
					break;
				}
			}
		}
		output_string = "";
	}
	closesocket(s);
	WSACleanup();
    return 0;
}

