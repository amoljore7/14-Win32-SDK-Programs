#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

//Function Prototype
BOOL Process();
BOOL Threads(DWORD);
BOOL DependentDLL(DWORD PID);