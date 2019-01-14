// process.cpp : Defines the entry point for the console application.
#include "ProcessExplorer.h"
////////////////////////////////////////////////////////////////////////////////////////////
				
int main(int argc, char* argv[])
{
	int i;
	printf("printing all running processes.....\n\n");
	printf("\n------------------------------------------------------------\n");

	printf("please press 1 to start:-\n");
	scanf("%d", &i);

	Process();
	
	printf("\n------------------------------------------------------------\n");
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL Process()
{
	HANDLE hProcessSnap;//for getting the snapshot HANDLE hProcess;
	PROCESSENTRY32 pe32;  //structure which contains all the information about the process
	
	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 ); 
	// Take a snapshot of all processes in the system.
	//it retuns INVALID_HANDLE_VALUE if it fails to take the snapshot
	//TH32CS_SNAPPROCESS Includes all processes in the system in the snapshot and second 
	//parameter is zero to indiacte the current process 
		
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("Unable to create the snapdhot of running processes");
		return(FALSE);
	}
		
	pe32.dwSize = sizeof(PROCESSENTRY32);
	//retrive the first process which requires handle of the snapshot 
	//and structure to fill the values
	
	if (!Process32First( hProcessSnap, &pe32)) 
	{
		printf("Error inf inding the first process..."); // Show cause of failure
		CloseHandle( hProcessSnap);    
		return FALSE;
	}
		
	do
	{		
		printf("\n------------------------------------------------------------");
	
		printf("\nPROCESS NAME:  %s\nPID: %d\nParent PID: %d\nNo of Thread: %d\n", pe32.szExeFile,pe32.th32ProcessID ,pe32.th32ParentProcessID, pe32.cntThreads);
	
		Threads(pe32.th32ProcessID);	//printing the threads of that process
			
		DependentDLL(pe32.th32ProcessID);

		printf("\n------------------------------------------------------------");					
		
	}while (Process32Next(hProcessSnap, &pe32)); //to get the next process
		
	CloseHandle(hProcessSnap);
	
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////

BOOL Threads(DWORD PID)
{
	HANDLE hThreadSnap; //handle for the thread snap
	THREADENTRY32 te32;//handle for each thread

	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, PID);// Take a snapshot of all running threads of this process   

	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		printf("Unable to create the snapshot of current thread pool");
		return FALSE; 
	}

	te32.dwSize = sizeof(THREADENTRY32);

	if (!Thread32First(hThreadSnap, &te32)) //get the first thread
	{
		printf("Error in Getting the first thread"); // Show cause of failure
		CloseHandle(hThreadSnap); //close the handle of thread   
		return FALSE;
	}
	
	printf("\n\tTHREAD OF THIS PROCESS:\n");
	
	do //for remaing thread
	{ 	
		if (te32.th32OwnerProcessID == PID) //check for the current process threads only
		{
			printf( "\n\t   THREAD ID:%d", te32.th32ThreadID); 
		}
	}while (Thread32Next(hThreadSnap, &te32));//traverse all the threads 

	CloseHandle(hThreadSnap);//close the handle of thread
	
	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////////////////

BOOL DependentDLL(DWORD PID)
{
	MODULEENTRY32 me32;
	HANDLE hProcessSnap;
		
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);// Take a snapshot of all running threads of this process   

	if( hProcessSnap == INVALID_HANDLE_VALUE )
	{
		printf("\n\nUnable to create the snapshot of current thread pool");
		return FALSE; 
	}
	me32.dwSize = sizeof(MODULEENTRY32);
	
	if (!Module32First(hProcessSnap, &me32)) //get the first thread
	{
		printf("\n FAILED");
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	printf("\n\n\tDEPENDENT DLL OF THIS PROCESS\n\n");

	do //for remaing thread
	{ 	
		printf("\t   %s\n", me32.szModule);

	}while (Module32Next(hProcessSnap, &me32)); //traverse all the threads 

	CloseHandle(hProcessSnap);
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////
