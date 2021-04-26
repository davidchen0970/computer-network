#include<iostream>
#include<winsock.h>
#include<string>

using namespace std;

int main()
{
	SOCKET sock ;
	WSADATA wsadata;
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(12345);

	char str[100] = "i love NP!";
	int n, i;
	n = WSAStartup(0x101, (WSADATA*)&wsadata);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	cout << "socket:" << n << endl;

	int len_serv = sizeof(serv);

	n = sendto(sock, str,strlen(str) + 1, 0, (struct sockaddr*)&serv, len_serv);
	cout << "send:" << str << ' ' << n + 1 << endl;

	closesocket(sock);
	WSACleanup();
}