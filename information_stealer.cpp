#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    WSADATA wsaData;
    WORD DLLversion = MAKEWORD(2, 1);
    if (WSAStartup(DLLversion, &wsaData) != 0)
        ExitProcess(EXIT_FAILURE);

    //Create Socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    ExitProcess(EXIT_SUCCESS);
}
