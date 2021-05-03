#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<winsock.h>
using namespace std;

string dele_t(string in)
{
	while (in[0] != '\t')
	{
		in.erase(0, 1);
	}
	in.erase(0, 1);

	return in;
}

char* to_chr(int in, char out[])
{
	string temp;
	temp = to_string(in);
	for (int i = 0; i < 1024; i++)
	{
		if (i < temp.size())
		{
			out[i] = temp[i];
		}
		else
		{
			out[i] = 0;
		}
	}
	return out;
}

int to_int(char in[])
{
	stringstream cha;
	string temp;
	int out = 0;
	for (int i = 0; i < strlen(in); i++)
	{
		temp.push_back(in[i]);
	}
	cha << temp;
	cha >> out;
	cha.clear();
	return out;
}

char* to_chr(string in, char out[])
{
	for (int i = 0; i < 1024; i++)
	{
		if (i < in.size())
		{
			out[i] = in[i];
		}
		else
		{
			out[i] = 0;
		}
	}
	return out;

}

string find_fuck(string in)
{
	int ptr = 0;
	while (ptr != -1)
	{
		ptr = in.find("fuck", ptr);
		if (ptr > -1)
		{
			in[ptr + 1] = 'x';
			in[ptr + 2] = 'x';
		}
	}
	ptr = 0;
	while (ptr != -1)
	{
		ptr = in.find("Fuck", ptr);
		if (ptr > -1)
		{
			in[ptr + 1] = 'x';
			in[ptr + 2] = 'x';
		}
	}
	ptr = 0;
	while (ptr != -1)
	{
		ptr = in.find("shit", ptr);
		if (ptr > -1)
		{
			in[ptr + 1] = 'x';
			in[ptr + 2] = 'x';
		}
	}
	ptr = 0;
	while (ptr != -1)
	{
		ptr = in.find("Shit", ptr);
		if (ptr > -1)
		{
			in[ptr + 1] = 'x';
			in[ptr + 2] = 'x';
		}
	}
	return in;
}

bool find_bye(string in)
{
	int cont = 0;
	cont = in.find("bye", cont);
	if (cont != -1)	return true;
	cont = in.find("Bye", cont);
	if (cont != -1)	return true;
	else			return false;
}

int main()
{
	//---------------------------------------------------------------
	//initialize memory

	SOCKET Socket;
	WSAData wsadata;
	char sending[1024] = {};
	char Ip_Address[1024] = "127.0.0.1";
	int port = 1234, connect_num = 0, send_recv = 0;

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(Ip_Address);
	server.sin_port = htons(port);
	int server_length = sizeof(server);
	ifstream cin;
	cin.open("input.jpg", ios::binary);
	//---------------------------------------------------------------
	//initialize

	WSAStartup(0x101, (LPWSADATA)&wsadata);
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	//cout << "socket: \t" << Socket << endl;
	//cout << "port: \t\t" << port << endl;

	connect_num = connect(Socket, (struct sockaddr*)&server, server_length);
	//cout << "connect: \t" << connect_num << endl;

	char in;


	while (cin.get(in))
	{
		cin.putback(in);
		for (int i = 0; i < 1024; i++)
		{
			if (cin.get(in))
			{
				cout << in;
				sending[i] = in;
			}
			else
			{
				sending[i] = 0;
			}
		}
		int y = send(Socket, sending, 1024, 0);
		cout << y << endl;
		// cout << sending;
	}
	cin.close();
	closesocket(Socket);
	WSACleanup();
}
