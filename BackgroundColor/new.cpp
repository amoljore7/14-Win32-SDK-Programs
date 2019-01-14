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
		/* Vars */
    HDC dc; /* Standard Device Context; used to do the painting */
    
    /* rect = Client Rect of the window; 
    Temp = Temparary rect tangle for the color bands */
    RECT rect, temp; 
    HBRUSH color; /* A brush to do the painting with */
    
    /* Get the dc for the wnd */
    dc = GetDC(hwnd);
    
    /* Get the client rect */
    GetClientRect(hwnd, &rect);
    
    /* Start color; Change the R,G,B values 
    to the color of your choice */
    int r1 = 255, g1 = 0, b1 = 0;
    
    /* End Color; Change the R,G,B values 
    to the color of your choice */
    int r2 = 255, g2 = 255, b2 = 0;
    
    /* loop to create the gradient */
    for(int i=0;i<rect.right;i++) 
    { 
        /* Color ref. for the gradient */
        int r,g,b; 
        /* Determine the colors */
        r = r1 + (i * (r2-r1) / rect.right); 
        g = g1 + (i * (g2-g1) / rect.right);
        b = b1 + (i * (b2-b1) / rect.right);
        
        /* Fill in the rectangle information */
        
        /* The uper left point of the rectangle 
        being painted; uses i as the starting point*/
        temp.left = i;
        /* Upeer Y cord. Always start at the top */ 
        temp.top = 0; 
        /* Okay heres the key part, 
        create a rectangle thats 1 pixel wide */
        temp.right = i + 1; 
        /* Height of the rectangle */
        temp.bottom = rect.bottom; 
        
        /* Create a brush to draw with; 
        these colors are randomized */
        color = CreateSolidBrush(RGB(r, g, b));
        
        /* Finally fill in the rectange */
        FillRect(dc, &temp, color);
    }
	break;

	break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

