#include<iostream>
#include<winsock.h>
using namespace std;

int main()
{
	char domain[2][40] = { "" };// 初始化

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA)&wsadata);
	//建立一個新的網路socket
	cout << "key in a start IP address: ";
	cin >> domain[0];
	cout << "key in a end IP address: ";
	cin >> domain[1];
	//起始到結束的IP address
	char temp[40] = "";
	for (auto i = inet_addr(domain[0]); i <= inet_addr(domain[1]); i += 16777216) //16777216 = 256 * 256 * 256
	{
		LPHOSTENT hp;
		struct in_addr sAddr;
		sAddr.s_addr = i;
		hp = gethostbyaddr((LPSTR)&sAddr, sizeof(sAddr), AF_INET);
		if (hp == nullptr)
		{
			cout << inet_ntoa(sAddr) << "'s get hp error, code:" << WSAGetLastError() << '\n';
		}
		else
		{
			cout << inet_ntoa(sAddr) << "'s domain name: " << hp->h_name << '\n';
		}
		if (i >= 255 * 16777216)
		{
			break;
		}
	}

}