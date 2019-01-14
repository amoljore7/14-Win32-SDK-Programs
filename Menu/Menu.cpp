/*
	You should aware about the following topics before doing this application...
	1. It's being assumed that you tried the Windows first application... "ATLEAST ONCE"
	2. Revise the concepts of Menus and all it's resources...
	3. Read about resource file and all...
	4. Read about WM_COMMAND...

				@@@@@@@@@@@@@   ABOUT THE PROGRAM   @@@@@@@@@@@@@
	//	This application is able to display the Menu list...
	//  Whatever menu is selected, appropriate message box is displayed for that...
*/

#ifndef UNICODE
	#define UNICODE
#endif
#include<windows.h>
#include"Menu.h"	// Menu.h conatins all the macros defined with some values...
 
// Also write the .rc file which contains the resource script for the MENU...

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
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[]=TEXT("Menu Demo");
	HANDLE hMenu;

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
		        TEXT("Windows Menu Demo"), // Pointer to a null-terminated string that specifies the window name.
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

//	The LoadMenu() function loads the specified menu resource from .exe file associated with an application instance. 
	hMenu = LoadMenuA(
					   hInstance,		// Handle of instance
					   "MENUDEMO"		// Name of menu
					  );

//	The SetMenu function assigns a new menu to the specified window. 
	SetMenu(
			 hwnd,			// Handle of window...
			 (HMENU)hMenu	// Handle of Menu...
			);

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
	switch(iMsg)
	{
		case WM_COMMAND :
/*
	The WM_COMMAND message is sent when the user selects a command item from a menu,
	when a control sends a notification message to its parent window,
	or when an accelerator keystroke is translated. ...
*/
				// switch case for handling the selection of menu if any...
						switch(wParam)
						{
							case IDM_FILE_NEW :
												MessageBox(
															hwnd,
															TEXT("New menu selected"),
															TEXT("NEW"),
															MB_OK
														   );
									break;

							case IDM_FILE_OPEN :
												MessageBox(
															hwnd,
															TEXT("Open menu selected"),
															TEXT("OPEN"),
															MB_OK
														   );
									break;
		
							case IDM_FILE_SAVE :
												MessageBox(
															hwnd,
															TEXT("Save menu selected"),
															TEXT("SAVE"),
															MB_OK
														   );
									break;

							case IDM_FILE_SAVE_AS :
												MessageBox(
															hwnd,
															TEXT("Save As menu selected"),
															TEXT("SAVE_AS"),
															MB_OK
														   );
									break;

							case IDM_APP_EXIT :
												MessageBox(
															hwnd,
															TEXT("Exit menu selected"),
															TEXT("EXIT"),
															MB_OK
														   );
												DestroyWindow(hwnd);
									break;

							case IDM_EDIT_UNDO :
												MessageBox(
															hwnd,
															TEXT("Undo menu selected"),
															TEXT("UNDO"),
															MB_OK
														   );
									break;
						}	// inner switch...
				break;

		case WM_CREATE :
				break;

		case WM_DESTROY :
						PostQuitMessage(0);
				break;
	}	// outer switch...
	return(DefWindowProc(
						  hwnd,
						  iMsg,
						  wParam,
						  lParam)
						 );
}