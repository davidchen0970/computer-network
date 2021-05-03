#include<iostream>
#include<winsock.h>

using namespace std;

int main()
{
	//------------------------------------------------
	//初始化記憶體空間
	SOCKET server_socket, client_socket;
	WSAData wsadata;
	struct sockaddr_in server, client;

	char recieve[1024] = {};
	char sending[1024] = "I love Algorithm?";
	char Ip_Address[1024] = "127.0.0.1";

	int port = 1234, binding = 0, send_recv = 0, listening = 0;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(Ip_Address);
	server.sin_port = htons(port);

	int client_length = sizeof(client);
	int server_length = sizeof(server);

	//------------------------------------------------
	//初始化程式
	WSAStartup(0x101, (LPWSADATA)&wsadata);
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	cout << "socket:\t\t" << server_socket << endl;

	binding = bind(server_socket, (struct sockaddr*)&server, server_length);
	cout << "bind():\t\t" << binding << endl;

	listening = listen(server_socket, 5);
	cout << "listen():\t" << listening << endl;

	client_length = sizeof(client);
	client_socket = accept(server_socket, (struct sockaddr*)&client, &client_length);

	//------------------------------------------------
	//先收後送
	while(true)
	{
		
		send_recv = recv(client_socket, recieve, 1024, 0);

		if (send_recv > 0)
		{
			
			cout << "recv():\t" << recieve << " (" << send_recv << " ) " << endl;
		}
		else
		{
			closesocket(server_socket);
			server_socket = socket(AF_INET, SOCK_STREAM, 0);
			cout << "socket:\t\t" << server_socket << endl;

			binding = bind(server_socket, (struct sockaddr*)&server, server_length);
			cout << "bind():\t\t" << binding << endl;

			listening = listen(server_socket, 5);
			cout << "listen():\t" << listening << endl;

			client_length = sizeof(client);
			client_socket = accept(server_socket, (struct sockaddr*)&client, &client_length);
		}
	}


	system("pause");

	closesocket(server_socket);
	WSACleanup();
}

