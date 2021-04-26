#include<iostream>
#include<string>
#include<winsock.h>
#include<fstream>

#define MAXLINE 1024

using namespace std;

int main()
{
	//-------------------------------------------------------------------------
	//initialize
	WSADATA wsadata;
	SOCKET sock_a, sock_b;
	struct sockaddr_in serv_a, serv_b;
	char ip_send[100000] = { '\0' };
	char* str_recv = new char[100000];
	char str_send[100000] = { '\0' };
	char str_send_b[100000] = { '\0' };
	string ip_send_string, str_recv_string, str_send_string, ip_address_string;
	int port = 0, result = 0;
	int recv_num = 0;
	for (int i = 0; i < 50000; i++)
	{
		str_recv[i] = '\0';
	}
	WSAStartup(0x101, (LPWSADATA)&wsadata);


	//end initialize

	//-------------------------------------------------------------------------

	//input a IP address


	cout << "input a address:";
	cin >> ip_address_string;
	memmove(ip_send, ip_address_string.c_str(), ip_address_string.length());
	port = 8000;
	cout << "port number:";
	cin >> port;

	//end input a IP address

	//-------------------------------------------------------------------------

	//build a socket


	sock_a = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_a == INVALID_SOCKET)
	{
		printf("socket() error, error code:%d", WSAGetLastError());
		exit(1);
	}

	//end build a socket
	//-------------------------------------------------------------------------

	//conmect to the server

	serv_a.sin_family = AF_INET;
	serv_a.sin_addr.s_addr = inet_addr(ip_send);
	serv_a.sin_port = htons(port);


	result = connect(sock_a, (LPSOCKADDR)&serv_a, sizeof(serv_a)); // 連接至 echo server   
	if (result == SOCKET_ERROR)
	{
		printf("connect() error, error code:%d", WSAGetLastError());
		exit(1);
	}

	//conmected 

	//-------------------------------------------------------------------------

	// get web data by "GET" method and print print "GET" data (get header)
	// the connect method is "close", refer to ended connect after got datas


	str_send_string = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
	memmove(str_send, str_send_string.c_str(), str_send_string.length());	//
	result = send(sock_a, str_send, strlen(str_send) + 1, 0); //傳送how are you至echo server 
	if (result == SOCKET_ERROR)
	{
		printf("send() error, error code:%d", WSAGetLastError());
		system("pause");
		exit(1);
	}
	cout << endl << "send to host:" << endl;
	cout << str_send << "(" << strlen(str_send) << " bytes)" << endl;

	// getton

	//-------------------------------------------------------------------------

	//get data again (web data)

	recv_num = recv(sock_a, str_recv, MAXLINE, 0); //由echo server接收 
	if (recv_num == SOCKET_ERROR)
	{
		printf("recv() error, error code:%d", WSAGetLastError());
		exit(1);
	}

	str_recv[recv_num] = '\0';

	cout << endl << "recv:" << endl << str_recv << "(" << recv_num << "bytes)\n";

	if (recv_num < 220 && recv_num>200)
	{
		delete[]str_recv;
		str_recv = new char[1024];
		recv_num = recv(sock_a, str_recv, MAXLINE, 0); //由echo server接收 
		if (recv_num == SOCKET_ERROR)
		{
			printf("recv() error, error code:%d", WSAGetLastError());
			exit(1);
		}

		str_recv[recv_num] = '\0';
		str_recv_string.clear();
		for (int i = 0; i < 1024; i++)
		{
			if (str_recv[i] == '\0')
			{
				break;
			}
			str_recv_string.push_back(str_recv[i]);
		}
		cout << endl << "recv:" << endl << str_recv_string << "(" << recv_num << "bytes)\n";

		//---------------------------------------------------------------------------
		//write index.html to storage 

		ofstream fout;
		fout.open("index.html");
		fout << str_recv_string;
		fout.close();
	}
	else
	{
		str_recv_string.clear();
		for (int i = 212; i < 1024; i++)
		{
			if (str_recv[i] == '\0')
			{
				break;
			}
			str_recv_string.push_back(str_recv[i]);

		}
	}
	closesocket(sock_a);
	WSACleanup();  // 結束 WinSock DLL 的使用
	delete[] str_recv;
	int temo = 0;
	while (temo = str_recv_string.find("a href=", temo + 1))
	{
		if (temo < str_recv_string.size())
		{
			//catch web path
			string in = str_recv_string;
			int temp = in.find(".html");
			string rept;
			rept.append(in, temo + 8, temp + 5);
			rept.erase(temp - temo - 3);
			cout << rept << '\n';

			//-------------------------------------------------------------------------
			//initialize

			WSAStartup(0x101, (LPWSADATA)&wsadata);
			cout << "address:" << ip_address_string << endl;
			memmove(ip_send, ip_address_string.c_str(), ip_address_string.length());
			port = 8000;
			cout << "port number:" << port << '\n';

			//-------------------------------------------------------------------------
			//build socket

			sock_b = socket(AF_INET, SOCK_STREAM, 0);
			if (sock_b == INVALID_SOCKET)
			{
				printf("socket() eroor, error code:%d", WSAGetLastError());
				exit(1);
			}

			//-------------------------------------------------------------------------
			//connect to server

			serv_b.sin_family = AF_INET;
			serv_b.sin_addr.s_addr = inet_addr(ip_send);
			serv_b.sin_port = htons(port);


			result = connect(sock_b, (LPSOCKADDR)&serv_b, sizeof(serv_b)); // 連接至 echo server   
			if (result == SOCKET_ERROR)
			{
				printf("connect() error, error code:%d", WSAGetLastError());
				exit(1);
			}

			//-------------------------------------------------------------------------
			// create GET data
			str_send_string.clear();

			str_send_string = "GET /";
			str_send_string += rept;
			str_send_string += " HTTP/1.1\r\n";
			str_send_string += "Host: ";
			str_send_string += ip_address_string;
			str_send_string += ":8000";
			str_send_string += "\r\n";
			str_send_string += "Connection: close\r\n\r\n";

			str_recv = new char[1024];
			for (int i = 0; i < 1024; i++)
			{
				str_recv[i] = '\0';
			}

			memmove(str_send_b, str_send_string.c_str(), str_send_string.length());

			//-------------------------------------------------------------------------
			// send GET data

			result = send(sock_b, str_send_b, strlen(str_send_b) + 1, 0); //傳送how are you至echo server 
			if (result == SOCKET_ERROR)
			{
				printf("send() error, error code:%d", WSAGetLastError());
				exit(1);
			}
			//cout << endl << "send to 1:" << endl << str_send_b << "(" << strlen(str_send) << " bytes)";
			//cout << endl << "here" << endl;

			//-------------------------------------------------------------------------
			//receive data from web server

			int recv_num = recv(sock_b, str_recv, MAXLINE, 0); //由echo server接收 
			if (recv_num == SOCKET_ERROR)
			{
				printf("recv() error, error code:%d", WSAGetLastError());
				exit(1);
			}

			str_recv[recv_num] = '\0';

			//cout << endl << "recv:" << str_recv << "(" << recv_num << "bytes)" << endl;

			//-------------------------------------------------------------------------
			//receive data from web server again
			//if (recv_num > 200 && recv_num << 220)
			//{
			recv_num = recv(sock_b, str_recv, MAXLINE, 0); //由echo server接收 
			if (recv_num == SOCKET_ERROR)
			{
				printf("recv() eroor, error code:%d", WSAGetLastError());
				exit(1);
			}

			str_recv[recv_num] = '\0';
			//cout << endl << "recv:" << str_recv << "(" << recv_num << "bytes)" << endl;
		//}
		//-------------------------------------------------------------------------
		// write data to storage by "ofstream

			ofstream oout;
			oout.open(rept);
			oout << str_recv;
			oout.close();

			//-------------------------------------------------------------------------
			// destory socket and clean all winsock 

			closesocket(sock_b);
			WSACleanup();  // 結束 WinSock DLL 的使用
			str_recv_string.erase(str_recv_string.begin() + temo + 8, str_recv_string.begin() + temo + 18);
		}
		else
		{
			break;
		}
	}
}