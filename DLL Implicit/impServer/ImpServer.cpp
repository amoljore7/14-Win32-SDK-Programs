/*
	You should aware about the following topics before doing this application...
	1. Revise the difference between static linking and dynamic linking...
	2. Then read about what is difference between Explicit and Implicit linking?
	3. What is "extern" in C?? and also about the storage classes in C...
	4. also read about the "header file" and "preprocessor" concept...
	4. And also the difference between writing .def file and __declspec(dllexport)...
	5. And, try to map the concepts from Explicit linking...
	
			@@@@@@@@@@@@@   ABOUT THE PROGRAM   @@@@@@@@@@@@@
	//	This is just a server-sided code for writing the functions 
	//  which will going to be exported for the outsided applications...
*/

#ifndef UNICODE
	#define UNICODE
#endif
#include <windows.h>
#include "ImplicitServer.h" // Header file which contains the declaration of functions which are to be exported...

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
	switch(dwReson)
	{
		case DLL_PROCESS_ATTACH :
					// This is just for displaying whether it's inside the case or not...
						MessageBox(
									NULL,
									TEXT("Inside case of DLL_PROCESS_ATTACH"),
									TEXT("DLL Demo... "),
									MB_OK
								   );
					break;

		case DLL_PROCESS_DETACH :
					// This is just for displaying whether it's inside the case or not...
						MessageBox(
									NULL,
									TEXT("Inside case of DLL_PROCESS_DETACH"),
									TEXT("DLL"),
									MB_OK
								   );
					break;

		case DLL_THREAD_ATTACH :
					break;

		case DLL_THREAD_DETACH:
					break;
	}
	return(TRUE);	// return value for the DllMain()...
}

// exported functions...
// The "extern" keyword declares a function and specifies that it has external linkage.
// To export functions, " __declspec(dllexport)" keyword must appear to the left of the calling-convention keyword, 

extern "C" __declspec(dllexport) 
		int SumOfTwoIntegers(
		  					  int inum1,		// An integer argument to the user-defined funtion.
							  int inum2			// An integer argument to the user-defined funtion. 
							)
{
	int inum3;	// variable declarations.

	inum3 = inum1 + inum2;	//code for the user-defined function.
	
	return(inum3);	// computed result of addition inside the num3 return as a return value.
}

extern "C" __declspec(dllexport)
		 int SubtractionOfTwoIntegers(
									   int inum1,	//  An integer argument to the user-defined funtion.
									   int inum2		//  An integer argument to the user-defined funtion.
									  )
{
	int inum3;	// variable declarations.

	inum3 = inum1 - inum2;	//code for the user-defined function.
	
	return(inum3);	// computed result of subtraction inside the num3 return as a return value.
}