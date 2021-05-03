#include<iostream>
#include<string>
#include<winsock.h>

using namespace std;

int main()
{
	SOCKET sock, client_sock;
	WSADATA wsadata;
	struct sockaddr_in serv, clinet;
	char str[100] = {};

	WSAStartup(0x101, &wsadata);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sock, (struct sockaddr*)&serv, sizeof(serv));

	int client_length=sizeof(clinet);
	cout << "Server waits." << endl;
	Sleep(1000);
	while (true)
	{
		int n = recv(sock, str, 100, 0);
		cout << "Server recieve:" << str << ", byte:" << n << endl;
	}
	closesocket(sock);
	WSACleanup();
	system("pause");


}
