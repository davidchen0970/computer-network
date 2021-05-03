#include<iostream>
#include<string>
#include<winsock.h>

using namespace std;

int main()
{
	SOCKET sock;
	WSADATA wsadata;
	struct sockaddr_in serv;
	int i, n;
	char str[100] = "[NCYU]";
	char str1[100]= "[NCYU][NCYU][NCYU][NCYU][NCYU]";

	WSAStartup(0x101, &wsadata);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sock, (struct sockaddr*)&serv, sizeof(serv));

	for (int i = 0; i < 5; i++)
	{
		send(sock, str, strlen(str), 0);
	}
	closesocket(sock);
	WSACleanup();

}
