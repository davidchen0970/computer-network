#include<iostream>
#include<winsock.h>
#include<string>
#include<windows.h>
using namespace std;

int main()
{
	SOCKET sock;
	WSADATA wsadata;
	struct sockaddr_in serv1, client;
	int n, i;

	n = WSAStartup(0x101, (WSADATA*)&wsadata);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	int len_client = sizeof(client);
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	client.sin_port = htons(2080); //若設0，則為隨機
	bind(sock, (struct sockaddr*)&client, len_client);
	char str[100] = "i love NP!";

	
	serv1.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv1.sin_port = htons(12345);
	serv1.sin_family = AF_INET;
	cout << "socket:" << n << endl;

	int len_serv1 = sizeof(serv1);
	connect(sock, (struct sockaddr*)&serv1, len_serv1);
	for (int k = 0; k < 10; k++)
	{
		cout << "time : " << k + 1 << endl;
		n = send(sock, str, strlen(str) + 1, 0);
		cout << "client 1 sends to 12345:" << str << ' ' << n + 1 << endl;


	}
	closesocket(sock);
	WSACleanup();
}