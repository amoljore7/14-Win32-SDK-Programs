#include <stdio.h>
#include <windows.h>

HANDLE g_hMutex;

int FirstThread();

int SecondThread();

int main()
{
	HANDLE hThread1, hThread2;

	//Creating Mutex object
	g_hMutex = CreateMutex (NULL, FALSE, (LPCWSTR)"Mutex1");

	//Creating two threads
	hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FirstThread, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SecondThread, NULL, 0, NULL);

	//Waiting for main till our child threads terminates
	WaitForSingleObject (hThread1, INFINITE);
	WaitForSingleObject (hThread2, INFINITE);

	//Freeing system resource for the mutex
	CloseHandle(g_hMutex);

	return 0;
}

int FirstThread()
{
	DWORD dwStatus;

	//Waiting for mutex
	dwStatus = WaitForSingleObject (g_hMutex, INFINITE);

	printf("\nMutex is allocated for first thread\n");

	if (WAIT_FAILED == dwStatus)
	{
		printf ("Thread not waiting\n");
		return 0;
	}

	int i;
	for(i = 0; i <= 20; i++)
	{
		printf(" %d ",i);
		Sleep(200);
	}

	printf("\nReleasing Mutex by First thread\n");

	//Releasing mutex
	ReleaseMutex (g_hMutex);

	return 1;	
}

int SecondThread()
{
	DWORD dwStatus;

	//Waiting for mutex
	dwStatus = WaitForSingleObject (g_hMutex, INFINITE);

	printf("\nMutex is allocated for Second thread\n");

	if (WAIT_FAILED == dwStatus)
	{
		printf ("Thread not waiting\n");
		return 0;
	}

	int i;
	for(i = 20; i>=0; i--)
	{
		printf(" %d ",i);
		Sleep(200);
	}

	printf("\nReleasing Mutex by Second thread\n");

	//Releasing mutex
	ReleaseMutex (g_hMutex);

	return 1;	
}