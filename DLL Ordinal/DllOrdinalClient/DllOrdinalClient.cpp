/*
	You should aware about the following topics before doing this application...
	1. It's being assumed that you tried the Windows first application... "ATLEAST ONCE"
	2. Revise about the topics such as : 
		a. What is difference between Explicit and Implicit Linking??
		b. How to load the created DLL...??
		c. How to use GetProcAddress()...?
		d. and also the topic related with DLL's BASIC CONCEPT...
	3. Basic knowledge about "POINTER from C" and "Function pointer" also...

				@@@@@@@@@@@@@   ABOUT THE PROGRAM   @@@@@@@@@@@@@
	//	This application is client-sided application...
	//  This will show about, how the one can import the functions which already
	//  are exported in the server-sided application...
*/

#ifndef UNICODE
	#define UNICODE
#endif
#include<windows.h>

/* **************************************************************************
// See the syntax of GetProcAddress().. 
// 2nd parameter is the ordinal number for the respective exported function...
***************************************************************************** */

// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	NAME		: WinMain()
//	Input		: 1. Handle to the current instance of the application.
//				  2. Handle to the previous instance of the application, generally we always give this as NULL.
//				  3. Pointer to a null-terminated string specifying the command line for the application,
//					   excluding the program name.
//				  4. Specifies how the window is to be shown.
//	Output		: The exit value contained in WM_QUIT message's wParam parameter on success and zero on failure.
//	Description : The WinMain function is the conventional name for the user-provided entry point for a 
//					  Microsoft Windows-based application.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(
				    HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpszCmdLine,
					int nCmdShow
				   )
{
	// variable declarations
	WNDCLASSEX wndclass;	// The WNDCLASSEX structure contains window class information and here we created object of it...
	HWND hwnd;				// Handle to window
	MSG msg;				// Contains message information from a thread's message queue. 

	TCHAR szAppName[]=TEXT("MyApp");

	// initialization of WNDCLASSEX members...

	wndclass.cbSize=sizeof(WNDCLASSEX);		// Specifies the size, in bytes, of this structure.
	wndclass.style=CS_HREDRAW|CS_VREDRAW;	// Specifies the class style(s).This member can be any combination of the Class Styles.
	wndclass.cbClsExtra=0;	// Specifies the number of extra bytes to allocate following the window-class structure.
	wndclass.cbWndExtra=0;	// Specifies the number of extra bytes to allocate following the window instance.
	wndclass.lpfnWndProc=WndProc;	// Pointer to the window procedure. i.e. callback function...
	wndclass.hInstance=hInstance;	// Handle to the instance that contains the window procedure for the class.
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	// Handle to the class icon. This member must be a handle to an icon resource.
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);	// Handle to the class cursor, member must be a handle to a cursor resource.
	wndclass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);	// Handle to the class background brush.
	wndclass.lpszClassName=szAppName;	// Pointer to a null-terminated string, specifies the window class name. 
	wndclass.lpszMenuName=NULL;	// Pointer to a null-terminated character string, specifies the resource name of the class menu.
	wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);	// Handle to a small icon that is associated with the window class.

	// registers above window class for subsequent use in calls to the CreateWindow or CreateWindowEx function
	RegisterClassEx(&wndclass);

	// CreateWindow() creates an overlapped, pop-up, or child window.
	hwnd=CreateWindow
		 (
				szAppName, // Pointer to a null-terminated string or a class atom.
		        TEXT("User Of Explicit Sever's Dll"), // Pointer to a null-terminated string that specifies the window name.
				WS_OVERLAPPEDWINDOW, // Specifies the style of the window, it can be a combination of window styles,
				CW_USEDEFAULT, // Specifies the initial horizontal position of the window. i.e. x co-ordinate
				CW_USEDEFAULT, // Specifies the initial vertical position of the window. i.e. y co-ordinate
				CW_USEDEFAULT, // Specifies the width, in device units, of the window.
				CW_USEDEFAULT, // Specifies the height, in device units, of the window.
                NULL, // Handle to the parent or owner window of the window being created.
				NULL, // Handle to a menu, or specifies a child-window identifier depending on the window style
				hInstance, // Handle to the instance of the module to be associated with the window
				NULL // Pointer to value, passed to the window through the CREATESTRUCT pointed to by lParam of the WM_CREATE msg.
		  );

	ShowWindow(hwnd,nCmdShow); // The ShowWindow function sets the specified window's show state. 

	UpdateWindow(hwnd); // Updates the client area by sending a WM_PAINT message if the update region is not empty.

	// message loop
	while(GetMessage(		// The GetMessage function retrieves a message from the calling thread's message queue.
					 &msg,	// Pointer to an MSG structure that receives message information from the thread's message queue.
					 NULL,	// Handle to the window whose messages are to be retrieved.
					 0,		// Specifies the integer value of the lowest message value to be retrieved.
					 0		// Specifies the integer value of the highest message value to be retrieved.
					 )) 	
	{
		TranslateMessage(&msg);	// Translates virtual-key messages into character messages.
		DispatchMessage(&msg);	// Dispatches a message to a window procedure and used to dispatch message retrieved by GetMessage function.
	}
	return((int)msg.wParam);	// specifies additional information about the message, exact meaning depends on value of the message.
}

// CALLBACK function defination goes here...
LRESULT CALLBACK WndProc(
						  HWND hwnd,
						  UINT iMsg,
						  WPARAM wParam,
						  LPARAM lParam
						 )
{
	// variable declarations
	static HMODULE hLib=NULL;
	typedef int (*pFunctionPointer)(int,int);
	pFunctionPointer pfn=NULL;
	int n1,n2,n3;
	TCHAR str[255];
	int ordinal1 = 500;

	switch(iMsg)
	{
		case WM_CREATE:
		/*			
		This message is sent when an application requests that a window be created by calling the CreateWindow function.
		The window procedure of the new window receives this message after the window is created
		*/	
				// Maps the specified executable module into the address space of the calling process.
					hLib=LoadLibrary(
									  TEXT("DLL_Server_Ordinal.dll")	// Name of the executable module (.dll or .exe file).
									 );

					if(hLib==NULL)	// checks whether LoadLibrary returns handle for module.
					{
						// appropriate code for failure checking...
						// The MessageBox function creates, displays, and operates a message box.
						MessageBox(
									hwnd,
									TEXT(
										  "Can Not Load Dll...\nExiting."
										 ),
									TEXT("Error"),
									MB_OK
								   );
						DestroyWindow(hwnd);  // LoadLibrary fails so need to Destroy the created window at here only...
						return -1;			  // Return from the function.. no further code will execute...
					}

			// Retrieves the address of an exported function or variable from the specified dynamic-link library (DLL).
					pfn=(pFunctionPointer)GetProcAddress(
														  hLib,			// handle to the DLL module that contains the function or variable.
														  (LPCSTR)500	// ordinal number which we written inside .def file against SumOfTwoIntegers().
														 );
					
					if(pfn==NULL)		// checks whether GetProcAddress fails or not...
					{
						// appropriate code for failure checking...
						MessageBox(
									hwnd,
									TEXT("Can Not Get Address Of SumOfTwoIntegers() through ordinal number...\nExitting."),
									TEXT("Error"),
									MB_OK
								   );
						DestroyWindow(hwnd);  // GetProcAddress fails so need to Destroy the created window at here only...
						return -1;			  // Return from the function.. no further code will execute...
					}
					// pfn now holds address of the "SumOfTwoIntgers()" function ...				
					n1=100;
					n2=50;

				// appropriate function get called using function pointer and return value will get stored in n3...
					n3 = pfn(n1,n2);	

				// The wsprintf function formats and stores a series of characters and values in a buffer.
					wsprintf(str,TEXT("Sum Of %d And %d = %d"),n1,n2,n3);

				// Above stored message get displayed through the message box...
					MessageBox(
							    hwnd,
								str,
								TEXT("Sum"),
								MB_OK
							   );

				// Retrieves the address of an exported function or variable from the specified dynamic-link library (DLL).
						pfn = (pFunctionPointer)GetProcAddress(
																hLib,		// handle to the DLL module that contains the function or variable.
																LPCSTR(501) // ordinal number which we written inside .def file against SubtractionOfTwoIntegers().
															   );					
						if(pfn==NULL)	// checks whether GetProcAddress fails or not...
						{
							MessageBox(
										hwnd,
										TEXT("Can Not Get Address Of SubtractionOfTwoIntegers() through ordinal number...\nExiting."),
										TEXT("Error"),
										MB_OK
									  );
							DestroyWindow(hwnd);	// GetProcAddress fails so need to Destroy the created window at here only...
							return -1;				// Return from the function.. no further code will execute...
						}

				// appropriate function get called using function pointer and return value will get stored in n3...
						n3 = pfn(n1,n2);

				// The wsprintf function formats and stores a series of characters and values in a buffer.
						wsprintf(str,TEXT("Subtraction Of %d And %d = %d"),n1,n2,n3);

				// Above stored message get displayed through the message box...
						MessageBox(
									hwnd,
									str,
									TEXT("Subtraction"),
									MB_OK
								  );
				break;	// WM_CREATE ends here...

		case WM_DESTROY:
		/*
		This message is sent when a window is being destroyed.This message is sent first to the window being destroyed 
		and then to the child windows, if any, as they are destroyed.
		During the processing of the message, it can be assumed that all child windows still exist.
		*/
					if(hLib)
						FreeLibrary(hLib); //Decrements the reference count of the loaded dynamic-link library (DLL).
		
					PostQuitMessage(0);
			// Indicates to Windows that a thread has made a request to terminate (quit). It's typically used in response to WM_DESTROY message.
	
				break;	// WM_DESTROY ends here...
	}// switch
	return(DefWindowProc(
						  hwnd,		// Handle to the window procedure that received the message. 
						  iMsg,		// Specifies the message. 
						  wParam,	// Specifies additional message information.
						  lParam)	// Specifies additional message information.
						 );
	/*
	The DefWindowProc function calls the default window procedure to provide default processing for any window messages that 
	an application does not process. This function ensures that every message is processed. 
	DefWindowProc is called with the same parameters received by the window procedure. 
	*/

}	// WndProc()