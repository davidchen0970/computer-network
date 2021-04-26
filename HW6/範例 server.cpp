#include<iostream>
#include<string>
#include<winsock.h>
using namespace std;

int main()
{
	SOCKET sock;
	WSADATA wsadata;
	struct sockaddr_in serv, client;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(12345);
	char str[100] = {};
	int n, i;
	n = WSAStartup(0x101, (WSADATA*)&wsadata);
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	int len_serv = sizeof(serv);
	int len_client = sizeof(client);
	n = bind(sock, (struct sockaddr*)&serv, len_serv);
	cout << "Ready to recv on 12345......" << endl;
	n = recvfrom(sock, str, 100, 0, (struct sockaddr*)&client, &len_client);
	cout << "recv:" << str << ' ' << n << endl;
	closesocket(sock);
	WSACleanup();
	system("pause");
}
