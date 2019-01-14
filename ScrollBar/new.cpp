//
// This program displays the scroll bar from starting.
//

#define UNICODE
#include <windows.h>

LRESULT CALLBACK WndProc(	HWND,
							UINT,
							WPARAM,
							LPARAM
						);

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR nCmdLine,
					int nCmdShow
)
{
	TCHAR AppName[]= TEXT("windows");

	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;


	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra =0;
	wndclass.cbWndExtra =0;
	wndclass.lpszClassName =AppName;
	wndclass.lpszMenuName =0;
	wndclass.lpfnWndProc =WndProc;
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance =hInstance;
	wndclass.hIcon =LoadIcon(hInstance,IDI_APPLICATION);
	wndclass.hIconSm =LoadIcon(hInstance,IDI_APPLICATION);
	wndclass.hCursor =LoadCursor(NULL,IDC_ARROW);

	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(	AppName,
							TEXT("ScrollBar Demo"),
							WS_OVERLAPPEDWINDOW | WS_VSCROLL,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							NULL,
							NULL,
							hInstance,
							NULL
						);

	if(NULL==hwnd)
	{
		MessageBox(NULL,TEXT("Not created"),TEXT("Error.."),0);
		exit(0);
	}

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);

}

LRESULT CALLBACK WndProc(	HWND hwnd,
							UINT imsg,
							WPARAM wParam,
							LPARAM lParam
						)
{
	HINSTANCE hInstance;
	static HDC hdc;
	static PAINTSTRUCT ps;

	switch(imsg)
	{
		case WM_CREATE:
			
				break;

		case WM_LBUTTONDOWN:

			break;

		case WM_DESTROY:
				PostQuitMessage(0);
				break;

		case WM_VSCROLL:
			switch(LOWORD(wParam))
			{
			case SB_LINEUP:
				MessageBox(hwnd,L"Unable to get messageBox",L"Error",NULL);
			hdc = BeginPaint(hwnd,&ps);
			if(hdc == NULL)
			{
				MessageBox(hwnd,L"Unable to get messageBox",L"Error",NULL);
			}
				TextOut(hdc,5,5,L"SB_LINEUP",9);
				break;
			
			case SB_LINEDOWN:
				MessageBox(hwnd,L"SB_LINEDOWN",L"ScrollBar Message",MB_OK);
				break;
			}
			break;

	}

	return(DefWindowProc(hwnd,imsg,wParam,lParam));
}
