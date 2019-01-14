
#include <windows.h>
#include<stdio.h>

void SendString(HWND h)
{
 char buf[256];
 int flag = 1;
 
 while(flag == 1)
 {
  printf("Enter string for sending to notepad:-\n");
  flushall();
  gets(buf);

  for(int i = 0; buf[i] != '\0'; i++)
   PostMessage(h, WM_CHAR, buf[i], 0);

  printf("Do you want send more yes=1 / No=0 :-");
  scanf("%d",&flag);
 }  
}

int main(int argc, char* argv[])
{
 HWND hWnd;

 ShellExecute(NULL, L"open", L"c:/windows/notepad.exe", NULL, NULL, SW_SHOWNORMAL);
 Sleep(100);

 HWND hNotepadWnd = FindWindow(NULL,  L"Untitled - Notepad");
 
 if(hNotepadWnd == NULL)
 {
  printf("Fail FindWindow\n");
  return 1;
 }

 hWnd = FindWindowEx(hNotepadWnd,NULL,L"Edit",NULL);
 if(hWnd == NULL)
 {
  printf("Fail FindWindowEx\n");
  return 1;
 }

    SendString(hWnd);

 return 0;
}
