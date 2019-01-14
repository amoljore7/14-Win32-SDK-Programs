// DownloadFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<windows.h>
#include<urlmon.h>

int main(int argc, char* argv[])
{
	HRESULT hResult;
	char url[500], fName[260];

	printf("Enter URL : ");
	gets(url);

	printf("\nEnter file name : ");
	gets(fName);

	hResult = URLDownloadToFile(NULL, url, fName, 0, NULL);

	if(hResult == INET_E_DOWNLOAD_FAILURE)
	{
		printf("\nThe download of the specified resource has failed due to invalid URL..");
	}
	else if(hResult == E_OUTOFMEMORY)
	{
		printf("\nInsufficient memory to complete the operation..");
	}

	else
	{
		printf("\nDownloaded successfully..!!");
	}

	return 0;
}
