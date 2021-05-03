#include<iostream>
#include<winsock.h>

using namespace std;

int main()
{
    //------------------------------------------------
    //初始化記憶體空間
    SOCKET Socket;
    WSAData wsadata;
    char sending[1024] ="I love NP??";
    char recieve[1024] = {};
    char Ip_Address[1024] = "127.0.0.1";
    int port = 1234, connect_num = 0, send_recv = 0;

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(Ip_Address);
    server.sin_port = htons(port);
    int server_length = sizeof(server);

    //------------------------------------------------
    //初始化程式
    WSAStartup(0x101, (LPWSADATA)&wsadata);
    Socket = socket(AF_INET, SOCK_STREAM, 0);
    cout << "socket: \t" << Socket << endl;
    cout << "port: \t\t" << port << endl;

    connect_num = connect(Socket, (struct sockaddr*)&server, server_length);
    cout << "connect: \t" << connect_num << endl;

    //------------------------------------------------
    //先送後收

    for(int i=0; i<10000; i++)
    {
        send_recv = send(Socket, sending, 1024, 0);
        cout << "send:\t\t" << sending << endl;
    }
    closesocket(Socket);
    WSACleanup();



}
