#include<iostream>
#include<winsock.h>
#include<string>
#include<windows.h>
using namespace std;

int main()
{
	SOCKET sock;
	WSADATA wsadata;
	struct sockaddr_in serv1, serv2;
	serv1.sin_family = AF_INET;
	serv1.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv1.sin_port = htons(12345);


	char str[100] = "i love NP!";
	int n, i;
	n = WSAStartup(0x101, (WSADATA*)&wsadata);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	cout << "socket:" << n << endl;

	int len_serv1 = sizeof(serv1), len_serv2 = sizeof(serv2);
	connect(sock, (struct sockaddr*)&serv1, len_serv1);
	for (int k = 0; k < 10; k++)
	{
		cout << "time : " << k + 1 << endl;
		n = sendto(sock, str, strlen(str) + 1, 0, (struct sockaddr*)&serv1, len_serv1);
		cout << "client 1 sends to 12345:" << str << ' ' << n + 1 << endl;
		Sleep(1000);
	}
	closesocket(sock);
	WSACleanup();
}	