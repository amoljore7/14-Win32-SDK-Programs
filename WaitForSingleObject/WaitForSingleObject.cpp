#include <stdio.h>
#include <windows.h>

int main()
{
	int iCount;
	STARTUPINFO appInfo;
	BOOL hProcess1, hProcess2;
	PROCESS_INFORMATION procInfo;
	char szAppName1[30], szAppName2[30];	

	//Initializing variables
	memset (&appInfo, 0, sizeof (appInfo));
	memset (&procInfo, 0, sizeof (procInfo));
	memset (szAppName1, 0 ,sizeof (szAppName1));
	memset (szAppName2, 0 ,sizeof (szAppName2));

	//copying application name
	lstrcpy ((LPWSTR)szAppName1, TEXT("notepad"));
	lstrcpy ((LPWSTR)szAppName2, TEXT("calc"));

	//loop for 3 times
	for (iCount = 0; iCount < 3; iCount++)
	{
		//Create Notepad Process
		hProcess1 = CreateProcess (NULL, (LPWSTR)szAppName1, NULL, NULL, TRUE, 0, NULL, NULL, &appInfo, &procInfo);

		//Checking whether process is created or not
		if (0 == hProcess1)
		{
			printf ("Process 1 not created\n");
			return 0;
		}
		//Main Thread Waiting for notepad process until user closed it.
		WaitForSingleObject (procInfo.hProcess, INFINITE);

		//Created Calculator Process
		hProcess2 = CreateProcess (NULL, (LPWSTR)szAppName2, NULL, NULL, TRUE, 0, NULL, NULL, &appInfo, &procInfo);

		//Checking whether process is created or not
		if (0 == hProcess2)
		{
			printf ("Process 1 not created\n");
			return 0;
		}
		//Main Thread Waiting for Calculator process until user closed it.
		WaitForSingleObject (procInfo.hProcess, INFINITE);		
	}
	
	return 0;
}