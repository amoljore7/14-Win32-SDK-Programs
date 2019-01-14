//#define UNICODE
#include<windows.h>
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

	HWND hwnd1, hwnd2;
// WinMain()
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int nCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass1, wndclass2;

	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	// initialization of WNDCLASSEX
	wndclass1.cbSize=sizeof(WNDCLASSEX);
	wndclass1.style=CS_HREDRAW|CS_VREDRAW;
	wndclass1.cbClsExtra=0;
	wndclass1.cbWndExtra=0;
	wndclass1.lpfnWndProc=WndProc;
	wndclass1.hInstance=hInstance;
	wndclass1.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass1.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass1.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass1.lpszClassName=szAppName;
	wndclass1.lpszMenuName=NULL;
	wndclass1.hIconSm=LoadIcon(NULL,IDI_APPLICATION);

	// register above class
	RegisterClassEx(&wndclass1);

	// create window
	hwnd1 =CreateWindow(szAppName,
		              TEXT("First Window"),
					  WS_OVERLAPPEDWINDOW,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
						NULL,
					  NULL,
					  hInstance,
					  NULL);
	ShowWindow(hwnd1,nCmdShow);
	UpdateWindow(hwnd1);

	
	// initialization of WNDCLASSEX
	wndclass2.cbSize=sizeof(WNDCLASSEX);
	wndclass2.style=CS_HREDRAW|CS_VREDRAW;
	wndclass2.cbClsExtra=0;
	wndclass2.cbWndExtra=0;
	wndclass2.lpfnWndProc=WndProc;
	wndclass2.hInstance=hInstance;
	wndclass2.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass2.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass2.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass2.lpszClassName=szAppName;
	wndclass2.lpszMenuName=NULL;
	wndclass2.hIconSm=LoadIcon(NULL,IDI_APPLICATION);

	// register above class
	RegisterClassEx(&wndclass2);
	hwnd2=CreateWindow(szAppName,
		              TEXT("Second Wibndow"),
					  WS_OVERLAPPEDWINDOW,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					NULL,
					  NULL,
					  hInstance,
					  NULL);
	
	ShowWindow(hwnd2,nCmdShow);
	UpdateWindow(hwnd2);
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
	switch(iMsg)
	{
	case WM_CREATE:

		break;

	case WM_LBUTTONDOWN:
		if(hwnd == hwnd1)
		{
			SendMessage(hwnd2, WM_SETTEXT, 0, (LPARAM)L"Message sender");
		}
		else
		{
			SendMessage(hwnd1, WM_SETTEXT, 0, (LPARAM)L"Message receiver");
		}
		
		break;

		case WM_RBUTTONDOWN:
		if(hwnd == hwnd2)
		{
		MessageBox(hwnd2,L"Message arrived from first window",L"new",MB_OK);
		}

		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

