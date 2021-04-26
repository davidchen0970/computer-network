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



	string number;
	cout << "input a name:";
	cin >> number;
	while (true)
	{
		//---------------------------------------------------------------
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
		getline(cin, output);
		//---------------------------------------------------------------
		//initialize connection
		WSAStartup(0x101, (LPWSADATA)&wsadata);
		sock = socket(AF_INET, SOCK_STREAM, 0);
		string temp = number;
		connect(sock, (LPSOCKADDR)&serv, sizeof(serv));

		if (output == "bye" || output == "Bye")
		{

			to_chr(temp + "\t" + output, send_data);

			send(sock, send_data, strlen(send_data) + 1, 0);

			closesocket(sock);
			WSACleanup();  // 結束 WinSock DLzL 的使用
			break;
		}
		if (output == "translate")
		{
			to_chr(output, send_data);
		}
		else
		{
			output = temp + '\t' + output;
			to_chr(output, send_data);
		}
		
		send(sock, send_data, strlen(send_data) + 1, 0);

		closesocket(sock);
		WSACleanup();
	}

}
