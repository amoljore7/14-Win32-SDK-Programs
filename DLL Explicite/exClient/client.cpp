//#define UNICODE
#include<windows.h>
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
// WinMain()
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int nCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[]=TEXT("MyApp");
	// code
	// initialization of WNDCLASSEX
	wndclass.cbSize=sizeof(WNDCLASSEX);
	wndclass.style=CS_HREDRAW|CS_VREDRAW;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.lpfnWndProc=WndProc;
	wndclass.hInstance=hInstance;
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName=szAppName;
	wndclass.lpszMenuName=NULL;
	wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	// register above class
	RegisterClassEx(&wndclass);
	// create window
	hwnd=CreateWindow(szAppName,
		              TEXT("User Of Explicit Sever's Dll"),
					  WS_OVERLAPPEDWINDOW,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
                      NULL,
					  NULL,
					  hInstance,
					  NULL);
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	// message loop
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	// variable declarations
	static HMODULE hLib=NULL;
	typedef int (*pFunctionPointer)(int,int);
	pFunctionPointer pfn=NULL;
	int n1,n2,n3;
	TCHAR str[255];
	// code
	switch(iMsg)
	{
	case WM_CREATE:
		hLib=LoadLibrary(TEXT("exServer.dll"));
		if(hLib==NULL)
		{
			MessageBox(hwnd,TEXT("Can Not Load Dll.\nExitting."),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
			return -1;
		}
		pfn=(pFunctionPointer)GetProcAddress(hLib,"SumOfTwoIntegers");
		if(pfn==NULL)
		{
			MessageBox(hwnd,TEXT("Can Not Get Address Of SumOfTwoIntegers().\nExitting."),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
			return -1;
		}
		n1=100;
		n2=50;
		n3=pfn(n1,n2);
		wsprintf(str,TEXT("Sum Of %d And %d = %d"),n1,n2,n3);
		MessageBox(hwnd,str,TEXT("Sum"),MB_OK);
		pfn=(pFunctionPointer)GetProcAddress(hLib,"SubtractionOfTwoIntegers");
		if(pfn==NULL)
		{
			MessageBox(hwnd,TEXT("Can Not Get Address Of SubtractionOfTwoIntegers().\nExitting."),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}
		n3=pfn(n1,n2);
		wsprintf(str,TEXT("Subtraction Of %d And %d = %d"),n1,n2,n3);
		MessageBox(hwnd,str,TEXT("Subtraction"),MB_OK);
		break;
	case WM_DESTROY:
		if(hLib)
			FreeLibrary(hLib);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
