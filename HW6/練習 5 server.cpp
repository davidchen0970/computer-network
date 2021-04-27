#include<iostream>
#include<string>
#include<winsock.h>
#include<sstream>

using namespace std;

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
			out[i] = '\0';
		}
	}
	return out;
}

string to_string(char in[])
{
	string out;
	for (int i = 0; i < strlen(in); i++)
	{
		out.push_back(in[i]);
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
			out[i] = '\0';
		}
	}
	return out;

}


int main()
{
	SOCKET sock;
	WSADATA wsadata;
	struct sockaddr_in serv, client;
	int port = 0;
	cout << "port number:";
	cin >> port;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(port);
	char str[1024] = {};
	int n, i;
	n = WSAStartup(0x101, (WSADATA*)&wsadata);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	int k = 0;
	int len_serv = sizeof(serv);
	int len_client = sizeof(client);
	n = bind(sock, (struct sockaddr*)&serv, len_serv);
	cout << "Ready to recv on " << port << "......" << endl;

	while (true)
	{
		//cout << endl << "time " << ++k << endl;
		
		n = recvfrom(sock, str, 100, 0, (struct sockaddr*)&client, &len_client);
		auto ip = inet_ntoa(client.sin_addr);
		int porr = ntohs(client.sin_port);

		cout << "recv:" << str << ' '<<"(" << n <<")"<< endl;
		memset(str, '\0', sizeof(str));
		Sleep(100);

	}
	//system("pause");
	closesocket(sock);
	WSACleanup();
}
