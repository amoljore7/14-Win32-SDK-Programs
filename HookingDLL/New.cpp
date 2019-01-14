// HOOKDLL.cpp : Defines the entry point for the DLL application.

#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

BOOL APIENTRY DllMain(HANDLE hModule, 
						DWORD  ul_reason_for_call, 
						LPVOID lpReserved
						)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:

			MessageBox(NULL,L"DLL is Injected !!!",L"Inside the Process",MB_OK | MB_ICONERROR);


		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
