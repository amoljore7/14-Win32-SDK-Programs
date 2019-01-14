#define UNICODE
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
	wndclass.hbrBackground=NULL;
	wndclass.lpszClassName=szAppName;
	wndclass.lpszMenuName=NULL;
	wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	// register above class
	RegisterClassEx(&wndclass);
	// create window
	hwnd=CreateWindow(szAppName,
		              TEXT("Coloring Demo"),
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

	switch(iMsg)
	{
	case WM_CREATE:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ERASEBKGND:

    HDC dc; /* Standard Device Context; used to do the painting */
    
    RECT rect, temp; 
    HBRUSH color; /* A brush to do the painting with */
    
    /* Get the dc for the wnd */
    dc = GetDC(hwnd);
    
    /* Get the client rect */
    GetClientRect(hwnd, &rect);
        int r,g,b;
    /* loop to create the gradient */
    int cnt = 1;
	for(int i=0; ;i++) 
    { 
		if(cnt == 1 && r != 255)
		{
        /* Color ref. for the gradient */
 
		g =0;
		r = i;
		b = 0;

        /* Create a brush to draw with; 
        these colors are randomized */
        color = CreateSolidBrush(RGB(r, g, b));
        
        /* Finally fill in the rectange */
        FillRect(dc, &rect, color);
		Sleep(50);
		if(r == 254)
		{
			++cnt;
			g = 0;
		}
		}
		else if(cnt == 2 && g != 255)
		{
        /* Color ref. for the gradient */
 
		g = i;
		r = 0;
		b = 0;

        /* Create a brush to draw with; 
        these colors are randomized */
        color = CreateSolidBrush(RGB(r, g, b));
        
        /* Finally fill in the rectange */
        FillRect(dc, &rect, color);
		Sleep(50);
		if(g == 254)
		{
			++cnt;
			b = 0;
		}
		}
		else if(cnt == 3 && b != 255)
		{
        /* Color ref. for the gradient */
 
		g = 0;
		r = 0;
		b = i;

        /* Create a brush to draw with; 
        these colors are randomized */
        color = CreateSolidBrush(RGB(r, g, b));
        
        /* Finally fill in the rectange */
        FillRect(dc, &rect, color);
		Sleep(50);
		if(r == 254)
		{
			++cnt;
			g = 0;
		}
		}
    }
	break;

	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

