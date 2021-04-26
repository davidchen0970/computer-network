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
		in.erase(0,1);
	}
	in.erase(0,1);

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
	SOCKET server_socket, client_socket, all[1024];
	int hohoh[1024] = { 0 };
	int count = 0, hi = 1;
	int cuo = 0;
	char send_str[1024] = {}, recv_str_a[1024] = {}, recv_str_b[1024] = {};
	struct sockaddr_in serv_data, client_data;
	WSADATA wsadata;

	WSAStartup(0x101, &wsadata);
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	int client_data_len = sizeof(client_data), recv_str_len = 0, port = 5678;
	serv_data.sin_family = AF_INET;
	serv_data.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_data.sin_port = htons(port);//指定port
	string output;

	//---------------------------------------------------------------------------------
	cout << "binding" << '\n';
	bind(server_socket, (LPSOCKADDR)&serv_data, sizeof(serv_data));
	bool translates = 0;
	while (true)
	{
		cout << "listening" << '\t';
		listen(server_socket, 5);
		client_socket = accept(server_socket, (LPSOCKADDR)&client_data, &client_data_len);
		cout << "accepted" << '\n';
		recv_str_len = recv(client_socket, recv_str_a, 1024, 0);

		for (int i = 0; i < count; i++)
		{
			if (all[i] == client_socket)
			{
				hi = 0;
			}
		}
		if (hi)
		{
			all[count++] = client_socket;
		}
		if (count > 1023)
		{
			count = 0;
		}
		string input_a = recv_str_a;
		input_a = find_fuck(input_a);
		output = "Client " + input_a;
		cout << output << endl;
		to_chr(output, send_str);
		if (input_a == "0")
		{
			hohoh[count] = 1;
		}
		else if (input_a == "translate")
		{
			if (translates == 1)	translates = 0;
			else					translates = 1;
		}

		else if (find_bye(input_a))
		{
			closesocket(server_socket);
			for (int i = 0; i < count; i++)
			{
				send(all[i], to_chr("bye", send_str), 4, 0);
				closesocket(all[i]);
			}
			WSACleanup();
			break;
		}
		else
		{
			if (translates == 0)
			{
				for (int i = 0; i < count; i++)
				{
					send(all[i], send_str, strlen(send_str) + 1, 0);
				}
			}
			else
			{
				ifstream inn;
				inn.open("test.txt");
				string tempa, tempb;
				string temp = input_a;
				temp = dele_t(temp);
				while (inn >> tempa >> tempb)
				{
					
					if (temp==tempa)
					{
						tempb = output + "\t" + tempb;
						cout << tempb << endl;
						to_chr(tempb, send_str);
						break;
					}
				}
				for (int i = 0; i < count; i++)
				{
					send(all[i], send_str, strlen(send_str) + 1, 0);
				}
				inn.close();
			}
		}
		cout << "count" << count << endl << endl;
	}
}
