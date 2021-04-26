#include<iostream>
#include<string.h>
#include<winsock.h>
#include <ctime> // clock 函數所需之標頭檔
using namespace std;
int main(int argc, char* argv)
{
	int in;
	while (cout << "select a type:(7.Echo 9.Discard 13.Daytime 17.QUOTE 19.CHARGEN)")
	{
		cin >> in;
		if (in != 7 && in != 9 && in != 13 && in != 17 && in != 19)
		{
			continue;
		}
		WSADATA wsadata;
		SOCKET	sock;
		struct sockaddr_in serv;
		char  str[1024] = "I LOVE NCYU CSIE";
		char  str_r[1024] = {0};
		WSAStartup(0x101, (LPWSADATA)&wsadata);
		int pp;
		sock = socket(AF_INET, SOCK_STREAM, 0);
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = inet_addr("127.0.0.1");
		serv.sin_port = htons(in);

		connect(sock, (LPSOCKADDR)&serv, sizeof(serv));
		send(sock, str, strlen(str) + 1, 0);
		if (in != 9)
		{
			pp = recv(sock, str_r, 1024, 0);
		}
		
		cout << "send:" << str << " (" << strlen(str) + 1 << " bytes)\n";
		
		if (in != 9) 
		{
			cout << "recv:" << str_r << endl;
			cout << " (" << pp << " bytes)\n";
		}
		else
		{
			cout << "recv:" ;
			cout << "	(0 bytes)\n";
		}
		closesocket(sock);
		WSACleanup();
	}
}