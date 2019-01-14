// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Winsock2.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


int main()
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
	SOCKET SendingSocket = socket(AF_INET,
								SOCK_STREAM,
								IPPROTO_TCP);
	if (INVALID_SOCKET == SendingSocket)
	{
		printf("\nError occured during creating socket");
		exit(1);
	}
	
	//Connect to server
	printf("\nconnecting to server");
	int iIsConnect = connect(SendingSocket,						// Socket Descriptor
							(SOCKADDR *)&saSocket,
							sizeof(saSocket));					// How Many client to listen
	if(SOCKET_ERROR == iIsConnect)
	{
		printf("\nError Occured while Listening");
		closesocket(SendingSocket);
		exit(1);
	}

	
	//Sending msg to server

	char msg[256];

	printf("\nEnter msg :");
	gets(msg);

	int iIsSend = send(	SendingSocket,
						msg,
						strlen(msg),
						0);

	if(SOCKET_ERROR == iIsSend)
	{
		printf("\nError occured while Sending the msg");
		exit(1);
	}
	
	//receiving msg
	char buffer[256];
	int iMsgLen=256;
	int iIsRecv;

	iIsRecv= recv(	SendingSocket,
					buffer,
					iMsgLen,
					0);

	if(SOCKET_ERROR == iIsRecv)
	{
		printf("\nError occured while Receiving the file data");
		exit(1);
	}
	buffer[iIsRecv] = '\0';
	printf("\n%s", buffer);
	
	printf("\n\n");

	return 0;
}