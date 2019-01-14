/*
	You should aware about the following topics before doing this application...
	1. It's being assumed that you tried the Windows first application... "ATLEAST ONCE"
	2. Revise "THE MOUSE" topic i.e. message handling of LBUTTONDOWN and RBUTTONDOWN and all...
	3. Revise Device context also...
	4. Basic knowledge about Graphics...
				@@@@@@@@@@@@@   ABOUT THE PROGRAM   @@@@@@@@@@@@@
	//	This application is displaying "SOME" message on respective co-ordinates continiously 
	//  after some interval of time on the Left button clicked of mouse...
*/

#ifndef UNICODE
	#define UNICODE
#endif
#include<windows.h>

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

// WinMain() defination goes here...
int WINAPI WinMain(
				    HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpszCmdLine,
					int nCmdShow
				   )
{
	// variable declarations
	WNDCLASSEX wndclass;	// The WNDCLASSEX structure contains window class information and here we created object of it...
	HWND hwnd;	// Handle to window
	MSG msg;	// Contains message information from a thread's message queue. 

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
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);	// Handle to the class background brush.
	wndclass.lpszClassName=szAppName;	// Pointer to a null-terminated string, specifies the window class name. 
	wndclass.lpszMenuName=NULL;	// Pointer to a null-terminated character string, specifies the resource name of the class menu.
	wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);	// Handle to a small icon that is associated with the window class.

	// registers above window class for subsequent use in calls to the CreateWindow or CreateWindowEx function
	RegisterClassEx(&wndclass);

	// CreateWindow() creates an overlapped, pop-up, or child window.
	hwnd=CreateWindow
		 (
				szAppName, // Pointer to a null-terminated string or a class atom.
		        TEXT("Windows Coloring Demo"), // Pointer to a null-terminated string that specifies the window name.
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
	int a=0,b=0,c=0,i=0;		// some integers defined, which used for setting color value and co-ordinates also...

	HDC hdc;					// handle to device context...
	
	TCHAR arr[]=L"Win32 SDK";	// TCHAR array is declared with contents... "Win32 SDK"

	switch(iMsg)
	{
		case WM_CREATE: // CODE...
	/*			
	This message is sent when an application requests that a window be created by calling the CreateWindow function.
	The window procedure of the new window receives this message after the window is created
	*/	
			break;

		case WM_DESTROY:
	/*
	This message is sent when a window is being destroyed.This message is sent first to the window being destroyed 
	and then to the child windows, if any, as they are destroyed.
	During the processing of the message, it can be assumed that all child windows still exist.
	*/
						PostQuitMessage(0);	
	// Indicates to Windows that a thread has made a request to terminate (quit). It's typically used in response to WM_DESTROY message.
			break;

		case WM_LBUTTONDOWN:
	/*
	This message is posted when the user presses the touch screen in the client area of a window or presses the left mouse button.
	*/
						hdc = GetDC(hwnd); 
			// Retrieves a handle to a display device context for the client area of a specified window or for the entire screen. 
			// You can use the returned handle in subsequent GDI functions to draw in the DC.

						for(i=0;i<1000;i++)
						{
							SetTextColor(			// Sets the text color for specified device context to specified color. 
										  hdc,		// Handle to the device context. 
 										  RGB(a,b,c)// Specifies the color of the text.
										 ); 
							TextOut(				// Writes a character string at the specified location, using the currently selected font, background color, and text color. 
									 hdc,			//  Handle to the device context.
									 a,				// Specifies the x-coordinate, in logical coordinates.
									 b,				// Specifies the x-coordinate, in logical coordinates.
									 (LPCWSTR)arr,	// Pointer to the string to be drawn.
									 lstrlen(L"Win32 SDK")	// Specifies the length of the string pointed to by lpString.
									); 

							a+=1;b+=1;c+=1;		// values for color variables, x, y cordinate will gets updated here...

							Sleep(		// Suspends script execution for a specified length of time, then continues execution.
									40	// Integer value indicating the interval (msec) you want the script process to be inactive.
								  );
						}
						ReleaseDC(hwnd,hdc);	// Releases a device context (DC), freeing it for use by other applications.
			break;
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