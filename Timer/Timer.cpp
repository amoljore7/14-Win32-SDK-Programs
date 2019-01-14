/*
	You should aware about the following topics before doing this application...
	1. It's being assumed that you tried the Windows first application... "ATLEAST ONCE"
	2. Revise the concepts of Timer...
			a. Read about SetTimer() API...
	3. and also the topic related with Timer's BASIC CONCEPT...

				@@@@@@@@@@@@@   ABOUT THE PROGRAM   @@@@@@@@@@@@@
	//	This application is able to show the message box after the specified interval 
	//  of time continuously (here 7 sec and 10sec.) until user explicitly handle with that.
*/

#define UNICODE
#include<windows.h>

// two macros defined for using as timer identifier...
#define IDT_TIMER1 100
#define IDT_TIMER2 200

// global function declarations...
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// global function declaration of Timerproc...
VOID CALLBACK MyTimerProc( HWND,UINT,UINT,DWORD);

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

// WinMain()
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
	TCHAR szAppName[] = TEXT("Timer Demo");
	
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
		        TEXT("Windows Timer Demo"), // Pointer to a null-terminated string that specifies the window name.
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

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_CREATE:
			// The SetTimer() function creates a timer with the specified time-out value.
					SetTimer(
							  hwnd,				// handle to main window 
							  IDT_TIMER1,		// timer identifier 
							  10000,			// 10-second interval 
							  MyTimerProc		// no timer callback 
							 );

					SetTimer(
							  hwnd,				// handle to main window 
							  IDT_TIMER2,		// timer identifier 
							  7000,				// 7-second interval 
							  MyTimerProc		// no timer callback 
							 );
			break;

		case WM_DESTROY:
				// while destroying the window we need to Kill the timer...
					KillTimer(hwnd,IDT_TIMER1);	// for timer one... 
					KillTimer(hwnd,IDT_TIMER2);	// for timer second...
		
					PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(
						  hwnd,
						  iMsg,
						  wParam,
						  lParam
						 )
		    );
}
/*
	An application can process WM_TIMER messages by including a WM_TIMER case statement in the window 
	procedure or by specifying a TimerProc callback function when creating the timer. When you specify a 
	TimerProc callback function, the default window procedure calls the callback function when it processes WM_TIMER.
	The wParam parameter of the WM_TIMER message contains the value of the nIDEvent parameter. 
*/

VOID CALLBACK MyTimerProc( 
							HWND hwnd,		// handle to window for timer messages 
							UINT message,	// Specifies the WM_TIMER message. 
							UINT idTimer,	// Specifies the timer's identifier. 
							DWORD dwTime)	//Specifies the number of milliseconds that have elapsed since the system was started.
{ 
	switch(idTimer)
	{
		// case will execute for the appropriate Timer's identifier...
		case IDT_TIMER1 :
				// just for displaying the message... after "dwTime" number of seconds...
						MessageBox(hwnd,TEXT("After 10 seconds"),TEXT("IDT_TIMER1"),MB_OK);
				break;

		case IDT_TIMER2 :
				// just for displaying the message... after "dwTime" number of seconds...
						MessageBox(hwnd,TEXT("After 7 seconds"),TEXT("IDT_TIMER2"),MB_OK);
				break;
	}
}