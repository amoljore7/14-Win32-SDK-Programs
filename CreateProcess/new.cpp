#include<stdio.h>
#include<windows.h>

int main()
{

	int iStatus;
	STARTUPINFO sStartupInfo;
	char szApplicationName[100];	
	PROCESS_INFORMATION piProcessInfo;

	//Initializing variables
	memset (&sStartupInfo, 0, sizeof (sStartupInfo));
	memset (&piProcessInfo, 0, sizeof (piProcessInfo));
	memset (szApplicationName, 0, sizeof (szApplicationName));

	sStartupInfo.cb = sizeof (sStartupInfo);
	lstrcpy ((LPWSTR)szApplicationName, TEXT("notepad"));					//copying appliaction name to array

	//Creating process
	iStatus = CreateProcess (NULL, (LPWSTR)szApplicationName, NULL, NULL, FALSE, 0, NULL, NULL, &sStartupInfo, &piProcessInfo);

	//Checking whether process is created or not
	if (iStatus == 0)
	{
		printf("Can't Create Process...");
		return 0;
	}

	//Waiting for notepad process for maximum 5 minutes
	WaitForSingleObject (piProcessInfo.hProcess, 10000);
	//Terminating notepad process
	TerminateProcess (piProcessInfo.hProcess, 0);
	//Releasing resources since externally terminating notepad process.
	CloseHandle (piProcessInfo.hProcess);

	return 0;
}