#include<iostream>
#include<string>
#include<sstream>
#include<winsock.h>
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

	while (1)
	{//---------------------------------------------------------------
	//initialize memory
		SOCKET sock;							//socket number
		struct sockaddr_in serv;
		{
			serv.sin_family = AF_INET;
			serv.sin_addr.s_addr = inet_addr("127.0.0.1");
			serv.sin_port = htons(5678);
		}
		WSADATA wsadata;
		string output;							//prepare to send
		char send_data[1024] = { 0 };			//the data to aend
		char recieve_data[1024] = { 0 };
		int recieve_data_len = 0;
		int number = rand() % 100 + 2;
		//---------------------------------------------------------------
		//initialize connection
		WSAStartup(0x101, (LPWSADATA)&wsadata);
		sock = socket(AF_INET, SOCK_STREAM, 0);
		connect(sock, (LPSOCKADDR)&serv, sizeof(serv));
		output = "0";
		to_chr(output, send_data);
		send(sock, send_data, strlen(send_data) + 1, 0);
		recieve_data_len = recv(sock, recieve_data, 1024, 0);
		string input = recieve_data;
		if (input == "bye")
		{
			closesocket(sock);
			WSACleanup();
			break;
		}
		string temp = recieve_data;
		cout << temp << endl;
	}
}
