/*
	You should aware about the following topics before doing this application...
	1. Revise the difference between static linking and dynamic linking...
	2. Then read about DLL concept i.e What is exported functions...???
	3. What is "extern" in C?? and also about the storage classes in C...
	4. And also the difference between writing .def file and __declspec(dllexport)...
	
			@@@@@@@@@@@@@   ABOUT THE PROGRAM   @@@@@@@@@@@@@
	//	This is just a server-sided code for writing the functions 
	//  which will going to be exported for the outsided applications...
*/
#ifndef UNICODE
	#define UNICODE
#endif
#include<windows.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	NAME		: DllMain()
//	Input		: 1. A handle to the DLL module. The value is the base address of the DLL.
//				  2. The reason code that indicates why the DLL entry-point function is being called.
//					   This parameter can be one of the following values :
//						a. DLL_PROCESS_ATTACH, 
//						b. DLL_PROCESS_DETACH, 
//						c. DLL_THREAD_ATTACH, 
//						d. DLL_THREAD_DETACH.
//				  3. If fdwReason is DLL_PROCESS_ATTACH, lpvReserved is NULL for dynamic loads and non-NULL for 
//					  static loads. If fdwReason is DLL_PROCESS_DETACH, lpvReserved is NULL if FreeLibrary has  
//					  been called or the DLL load failed.
//	Output		: When the system calls the DllMain function with DLL_PROCESS_ATTACH value,
//					the function returns TRUE, FALSE on failure. 
//	Description : DllMain is a placeholder for the library-defined function name. You must specify the 
//					actual name you use when you build your DLL. 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// An optional entry point into a dynamic-link library (DLL). 
BOOL WINAPI DllMain(
					 HANDLE hModule,
					 DWORD dwReason,
					 LPVOID lpReserved
					)	
{
	// code
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH :	
			// Indicates that the DLL is being loaded into the virtual address space of the current 
			// process as a result of the process starting or as a result of a call to LoadLibrary. 
			break;

		case DLL_PROCESS_DETACH :
			// Indicates that the DLL is being unloaded from the virtual address space of the 
			// calling process as a result of either a process exit or a call to FreeLibrary. 
			break;

		case DLL_THREAD_ATTACH :
			// Indicates that the current process is creating a thread. 
			break;

		case DLL_THREAD_DETACH :
			// Indicates that a thread is exiting cleanly. 
			break;
	}
	return(TRUE);	// return value for the DllMain()...
}

// exported functions...
// The "extern" keyword declares a function and specifies that it has external linkage.
// To export functions, " __declspec(dllexport)" keyword must appear to the left of the calling-convention keyword, 

extern "C" __declspec(dllexport) 
		int SumOfTwoIntegers(
		  					  int num1,		// An integer argument to the user-defined funtion.
							  int num2		// An integer argument to the user-defined funtion. 
							)
{
	int num3;	// variable declarations.

	num3 = num1+num2;	//code for the user-defined function.
	
	return(num3);	// computed result of addition inside the num3 return as a return value.
}

extern "C" __declspec(dllexport)
		 int SubtractionOfTwoIntegers(
									   int num1,	//  An integer argument to the user-defined funtion.
									   int num2		//  An integer argument to the user-defined funtion.
									  )
{
	int num3;	// variable declarations.

	num3 = num1-num2;	//code for the user-defined function.
	
	return(num3);	// computed result of subtraction inside the num3 return as a return value.
}