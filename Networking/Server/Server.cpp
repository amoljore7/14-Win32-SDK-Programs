// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Winsock2.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	// initialize socket library
	struct sockaddr_in saSocket;
	saSocket.sin_family = AF_INET;
	saSocket.sin_addr.s_addr = inet_addr("127.0.0.1");
	saSocket.sin_port = 8888;

	// Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR) 
	{
		printf("\nWSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	//creating socket
	printf("\nCreating Socket ...");
	SOCKET ListenSocket = socket(AF_INET,
								SOCK_STREAM,
								IPPROTO_TCP);
	if (INVALID_SOCKET == ListenSocket)
	{
		printf("\nError occured during creating socket");
		getch();
		exit(1);
	}

	//bind the socket
	printf("\nBinding ...");
	int iIsBind = bind(ListenSocket,(SOCKADDR *)&saSocket,sizeof(saSocket));
	if(SOCKET_ERROR == iIsBind)
	{
		printf("\nError Occured while Binding");
		closesocket(ListenSocket);
		exit(1);
	}

	//Listen on socket
	printf("\nListening for socket");
	int iIsListen = listen(ListenSocket,		// Socket Descriptor
			1);								// How Many client to listen
	if(SOCKET_ERROR == iIsListen)
	{
		printf("\nError Occured while Listening");
		closesocket(ListenSocket);
		exit(1);
	}

	//Accept the client socket
	SOCKET AcceptSocket;
	AcceptSocket = accept(ListenSocket,
							NULL,				//out parameter for getting sockaddr_out
							NULL);				//length of socket

	if(INVALID_SOCKET == AcceptSocket)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;

	}
	printf("\nsocket accepted..wait for msg..");

	//receiving msg
	
	char buffer[256];
	int iMsgLen=256;
	int iIsRecv;
	
	iIsRecv= recv(	AcceptSocket,
					buffer,
					iMsgLen,
					0);
	
	if(SOCKET_ERROR == iIsRecv)
	{
		printf("\nError occured while Receiving the msg");
		exit(1);
	}
	buffer[iIsRecv] = '\0';
	printf("\n%s", buffer);

	//sending msg

	char msg[256];

	printf("\nEnter msg :");
	gets(msg);

	int iIsSend = send(	AcceptSocket,
						msg,
						strlen(msg),
						0);

	if(SOCKET_ERROR == iIsSend)
	{
		printf("\nError occured while Sending the msg");
		exit(1);
	}
	printf("\nMsg sent to client..");

	printf("\n\n");
	getchar();
	return 0;
}
