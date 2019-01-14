#include <windows.h>
#include<stdio.h>

void SendString(HWND h, char *text)
{
	int len = strlen(text);

	for(int i = 0; i < len; i++)
		PostMessage(h, WM_CHAR, text[i], 0);
}

int main(int argc, char* argv[])
{
	BOOL bRet;
	HWND hWnd;
	HMENU hNotepadMenu;
	TCHAR text[] = TEXT("it works!");

	ShellExecute(NULL, "open", "c:/windows/notepad.exe", NULL, NULL, SW_SHOWNORMAL);

	Sleep(100);

	HWND hNotepadWnd = FindWindow(NULL,  "Untitled - Notepad");
	
	if(hNotepadWnd == NULL)
	{
		printf("Fail FindWindow\n");
		return 1;
	}
	
	SendMessage(hNotepadWnd, WM_SETTEXT, 0, (LPARAM)text);

	hWnd = FindWindowEx(hNotepadWnd, NULL, "Edit", NULL);

	if(hWnd == NULL)
	{
		printf("Fail FindWindowEx\n");
		return 1;
	}

	hNotepadMenu = GetMenu(hNotepadWnd);

	if(hNotepadMenu == NULL)
	{
		printf("Fail GetMenu\n");
		return 1;
	}

	bRet = DeleteMenu(hNotepadMenu,4,MF_BYPOSITION);

	if (bRet == 0)
	{
		printf("Fail DeleteMenu ");
		printf("= %d\n",GetLastError());
		return 1;	
	}

	SetForegroundWindow(hWnd);
	Sleep(5);
	SetForegroundWindow(hNotepadWnd);
	
	//ShowWindow(hWnd, SW_HIDE);
	
//////////////////////////////////////////////////////////////

	//int extendedStyle = GetWindowLong(hNotepadWnd, GWL_STYLE);
	//SetWindowLong(hNotepadWnd, GWL_STYLE, extendedStyle | WS_EX_DLGMODALFRAME);
 	//SetWindowPos(NULL, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

//////////////////////////////////////////////////////////////
	
	SendString(hWnd, "Hello World line 1\n");
	SendString(hWnd, "Hello World line 2\n");
	SendString(hWnd, "Hello World line 3\n");

	return 0;
}
