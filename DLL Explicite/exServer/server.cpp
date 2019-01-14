//#define UNICODE
#include<windows.h>
// DllMain
BOOL WINAPI DllMain(HANDLE hModule,DWORD dwReason,LPVOID lpReserved)
{
	// code
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return(TRUE);
}
// exported functions
extern "C" __declspec(dllexport)int SumOfTwoIntegers(int num1,int num2)
{
	// variable declarations
	int num3;
	// code
	num3=num1+num2;
	return(num3);
}
extern "C" __declspec(dllexport)int SubtractionOfTwoIntegers(int num1,int num2)
{
	// variable declarations
	int num3;
	// code
	num3=num1-num2;
	return(num3);
}
