#include<iostream>
#include<winsock.h>
#include<string>
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
			out[i] = 0;
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
			out[i] = 0;
		}
	}
	return out;

}


int main()
{
	//---------------------------------------------------------------------------------
	//create a new number from 1 to 100
	int number = rand() % 100 + 1, upper_bound = 100, lower_bound = 1, guess = (upper_bound + lower_bound) / 2;

	//---------------------------------------------------------------------------------
	//initialize memory
	/*SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET client_socket;
	int port = 5678;
	char send_str[1024] = {};
	char recv_str[1024] = {};
	struct sockaddr_in serv_data;
		serv_data.sin_family = AF_INET;
		serv_data.sin_addr.s_addr = 0;
		serv_data.sin_port = htons(port);
	struct sockaddr_in client_data;
	int client_data_len = sizeof(client_data);
	int recv_str_len = 0;
	WSADATA wsadata;
	int count = 0;
	string output;*/
	SOCKET server_socket, client_socket;
	char send_str[1024] = {}, recv_str[1024] = {};
	struct sockaddr_in serv_data, client_data;
	WSADATA wsadata;
	WSAStartup(0x101, &wsadata);
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	int client_data_len = sizeof(client_data), recv_str_len = 0, port = 5678;
	serv_data.sin_family = AF_INET;
	serv_data.sin_addr.s_addr = 0;
	serv_data.sin_port = htons(port);//指定port
	int count = 0;
	string output;

	//---------------------------------------------------------------------------------
	//start connection and listen
	//伺服器使用 bind()來指定本身的端點位址
	// accept() 伺服器使用 accept 來取得下一個連線要求。產生一個新的 socket，用來傳送連線的資料; 原本的 socket 繼續接受新的連線要求。
	bind(server_socket, (LPSOCKADDR)&serv_data, sizeof(serv_data));
	listen(server_socket, 5);
	client_socket = accept(server_socket, (LPSOCKADDR)&client_data, &client_data_len);
	while (++count)
	{
		client_data_len = sizeof(client_data);
		cout << "server is wating for client..." << endl;	//最後要馬調

		//---------------------------------------------------------------------------------
		//recieve client data 1
		recv_str_len = recv(client_socket, recv_str, 1024, 0);
		cout << "server recieve: " << recv_str << " (" << recv_str_len << " bytes)\n";	//最後要馬調

		//---------------------------------------------------------------------------------
		//judge input
		int judge = to_int(recv_str);

		if (judge == number)
		{
			output = "get answer";
		}
		if (judge > number)
		{
			output = "too large";
		}
		else
		{
			output = "too small";
		}

		//---------------------------------------------------------------------------------
		//send string 1
		to_chr(output, send_str);
		send(client_socket, send_str, strlen(send_str) + 1, 0);

		//---------------------------------------------------------------------------------
		//send string 2
		guess = (upper_bound + lower_bound) / 2;
		to_chr(guess, send_str);
		send(client_socket, send_str, strlen(send_str) + 1, 0);

		//---------------------------------------------------------------------------------
		//recieve data 2
		recv_str_len = recv(client_socket, recv_str, 1024, 0);
		cout << "server recieve: " << recv_str << " (" << recv_str_len << " bytes)\n";	//最後要馬調

		//---------------------------------------------------------------------------------
		//judge result
		string input = to_string(recv_str);
		if (input == "too small")
		{
			lower_bound = guess;
		}
		else if (input == "too large")
		{
			upper_bound = guess;
		}
		else
		{
			break;
		}
		guess = (upper_bound + lower_bound) / 2;
		cout << endl;
	}
	closesocket(server_socket);
	closesocket(client_socket);
	WSACleanup();//結束 WinSock DLL的使用
}
