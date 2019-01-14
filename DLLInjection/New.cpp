#include<windows.h>
#include<string.h>
#include<stdio.h>
#include<tlhelp32.h>

#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)
unsigned long GetProcessIdFromProcname(char *procName);
//typedef unsigned long (__stdcall *PFN_OPERTION)(void *);

int main(int argc, char* argv[])
{
	HANDLE hThread,handle;
//	PFN_OPERTION pfnLoadLibrary;
	unsigned long procId;

	LPVOID String,pfnLoadLibrary;

	if(argc != 3)
	{
		printf("\nUsage : hooking <dll_file_complete_path> <tergetprocess_name>\n");
		return 1;
	}

	procId = GetProcessIdFromProcname(argv[2]);

	if(-1 == procId)
	{
		printf("Error to get pid\n");
		return 0;
	}	

	handle = OpenProcess(CREATE_THREAD_ACCESS,
						 FALSE,
						 procId
						 );

	if(NULL == handle)
	{
		printf("ERROR open process.\n");
		return 0;
	}
	
	pfnLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"),
											"LoadLibraryA"
											);

	if(NULL == pfnLoadLibrary)
	{
		printf("ERROR GetProcAddress\n");
		printf("%d\n",GetLastError());
		return 0;
	}
	
	String = (LPVOID)VirtualAllocEx(handle, 
									NULL, 
									strlen(argv[1]), 
									MEM_RESERVE|MEM_COMMIT, 
									PAGE_READWRITE
									);
	if(NULL == String)
	{
		printf("ERROR VIRTUAL ALLOC.\n");
		printf("%d\n",GetLastError());
		return 0;
	}

	BOOL ret = WriteProcessMemory(handle,(LPVOID)String, argv[1],strlen(argv[1]), NULL);
	
	if(ret == 0)
	{
		printf("ERROR writeProcessMemory.\n");
		printf("%d\n",GetLastError());
		return 0;
	}

	hThread = CreateRemoteThread(handle,
								NULL,
								0,
								(LPTHREAD_START_ROUTINE)pfnLoadLibrary,
								(LPVOID)String,
								NULL,
								NULL
								);
	
	if(hThread == NULL)
	{
		printf("Unable to create remote Thread\n");
		printf("%d\n",GetLastError());
		return 0;
	}
	printf("injected\n");
	CloseHandle(handle);
	return 0;
}

unsigned long GetProcessIdFromProcname(char *procName)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	TCHAR arr[256];

	MultiByteToWideChar(CP_UTF8,0,procName,-1,arr,sizeof(arr));
	while(1)
	{	
		hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
		if( hProcessSnap == INVALID_HANDLE_VALUE )
		{
			return -1;
		}

		pe32.dwSize = sizeof( PROCESSENTRY32 );

		if( !Process32First( hProcessSnap, &pe32 ) )
		{
			 
			CloseHandle( hProcessSnap );          
			return -1;
		}

		do
		{
		  if(lstrcmp((LPCWSTR)pe32.szExeFile,arr) == 0)
		  {
			return pe32.th32ProcessID ;
		  }
		} while( Process32Next( hProcessSnap, &pe32 ) );
	}
	CloseHandle( hProcessSnap );
	return -1;
}
