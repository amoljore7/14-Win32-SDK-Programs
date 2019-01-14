/*
	You should aware about the following topics before doing this application...
	1. You should know about "BASIC C"...
	2. What does CreateThread() do?...
	3. Also read about the Thread Local Storage(TLS) concept...
*/

#include<stdio.h>
#include<windows.h>

int ThreadFun();

int TLSDemo(DWORD);

int main()
{
	HANDLE hThread;

	//Creating Thread and associating it with funtion fnTLS
	hThread = CreateThread(
							NULL,
							0,
							(LPTHREAD_START_ROUTINE)ThreadFun,
							NULL,
							0,
							NULL
						   );

	//Checking thread creation successfull or not
	if (hThread == NULL)
	{
		printf("Not able to create thread\n");
		return 0;
	}

	//Waiting for completion of child thread
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(
				 hThread
			    );

	return 0;
}

int ThreadFun()
{
	DWORD iIndex;

	//Getting index of free block in tls
	iIndex = TlsAlloc();

	printf("\nInside our thread function ThreadFun\n");

	//setting value at free block
	TlsSetValue(iIndex, (LPVOID)100);

	printf("\nValue set in TLS by ThreadFun is 100\n");

	//calling function
	TLSDemo(iIndex);

	//Printing allocated memory
	printf("\nValue retrived from TLS by ThreadFun is %d\n", TlsGetValue(iIndex));

	//Freeing allocated memory
	TlsFree(iIndex);
	
	return 1;
}

int TLSDemo( 
			 DWORD iIndex
			)
{
	//access memeory from TLS with index which is allocated by another function of same thread
	printf ("\nValue retrived by TLSDemo Function is %d\n", TlsGetValue (iIndex));

	//Updating value at index
	TlsSetValue (iIndex, (LPVOID)200);
	printf ("\nValue set by TLSDemo Function is 200\n");

	return 1;
}