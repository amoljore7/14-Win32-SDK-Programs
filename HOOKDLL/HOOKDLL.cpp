// HOOKDLL.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

bool HOOKED = false;

BOOL __stdcall m_CloseHandle(HANDLE hObject)
{
	printf("\n IN HOOK closehandle \n");
	return TRUE;
}

BOOL APIENTRY DllMain(HANDLE hModule, 
						DWORD  ul_reason_for_call, 
						LPVOID lpReserved
						)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:

			if (!HOOKED)
			{
				printf("INJECTED\n");
			
				HMODULE handle = GetModuleHandle("Kernel32.dll");
			
				// Get address 
				FARPROC addr = GetProcAddress(handle,"CloseHandle");

				// Unprotect 1024 bytes
				DWORD oldProtection;
	
				VirtualProtect(addr, 1024, PAGE_EXECUTE_READWRITE, &oldProtection);
	
				DWORD our_addr = (DWORD) &m_CloseHandle;

				// Write some code to address
				unsigned char* func = (unsigned char*) addr;
				
				// mov eax, our_addr
				func[0] = 0xb8;
				func[1] = (unsigned char)(our_addr & 0xff);
				func[2] = (unsigned char)((our_addr >> 8) & 0xff);
				func[3] = (unsigned char)((our_addr >> 16) & 0xff);
				func[4] = (unsigned char)((our_addr >> 24) & 0xff);
				// jmp eax
				func[5] = 0xff;
				func[6] = 0xe0;

				// Restore protection
				VirtualProtect(addr, 1024, oldProtection, NULL);
				HOOKED = true;
			}

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
