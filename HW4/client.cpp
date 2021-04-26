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
	int number = 0;							//in put a number and guess the number of server carried out
	int guess = 0;
	int recieve_num = 0;					//the number of server sended
	int guess_times = 0;					//count guessing times
	string output;							//prepare to send
	int recv_number_a = 0;
	int recv_number_b = 0;
	char send_data_a[1024] = { 0 };			//the data to aend
	char recieve_data_a[1024] = { 0 };
	char recieve_data_b[1024] = { 0 };
	bool too_big = 0;

	//---------------------------------------------------------------
	//initialize connection
	WSAStartup(0x101, (LPWSADATA)&wsadata);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	connect(sock, (LPSOCKADDR)&serv, sizeof(serv));

	//---------------------------------------------------------------
	// input number
	cout << "輸入一個給server猜的數字:";
	cin >> number;

	//---------------------------------------------------------------
	//start to "guess" loop
	while (++guess_times)
	{
		//---------------------------------------------------------------
		//guess
		cout << "回合" << guess_times << ":請輸入猜的數字：";
		cin >> guess;

		//---------------------------------------------------------------
		//send message
		to_chr(guess, send_data_a);
		send(sock, send_data_a, strlen(send_data_a) + 1, 0);

		//---------------------------------------------------------------
		//judge recieve
		recv_number_a = recv(sock, recieve_data_a, 1024, 0);
		string judge = to_string(recieve_data_a);				//自己寫得的函式

		if (judge == "get answer")
		{
			cout << "server說你猜對了。\n";
			break;
		}
		if (judge == "too large")
		{
			cout << "server說太大。";
		}
		else
		{
			cout << "server說太小。";
		}

		//---------------------------------------------------------------
		//judge recieve
		recv_number_b = recv(sock, recieve_data_b, 1024, 0);
		int judge_num = to_int(recieve_data_b);

		cout << "server猜" << judge_num;
		if (judge_num == number)
		{
			cout << "server猜對了。" << endl;
			break;
		}
		if (judge_num > number)
		{
			cout << "請回覆：too large" << endl;
			too_big = 1;
		}
		else
		{
			cout << "請回覆：too small" << endl;
			too_big = 0;
		}

		//---------------------------------------------------------------
		//send message
		if (too_big)
		{
			output = "too large";
		}
		else
		{
			output = "too small";
		}
		to_chr(output, send_data_a);
		send(sock, send_data_a, strlen(send_data_a) + 1, 0);

		//---------------------------------------------------------------
		//zeroing
		memset(send_data_a, 0, sizeof(*send_data_a));
		memset(recieve_data_a, 0, sizeof(*recieve_data_a));
		memset(recieve_data_b, 0, sizeof(*recieve_data_b));
		guess = 0;
		recieve_num = 0;					//the number of server sended
		output.clear();
		recv_number_a = 0;
		recv_number_b = 0;
		too_big = 0;

		//---------------------------------------------------------------
		cout << endl;
	}
}
