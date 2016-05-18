// Win32-Fractali.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include "Win32-Fractali.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name



HWND chBackColor;
HWND chLineColor;
HWND chWidthLine;
HWND chMinDist;
HWND chSpeed;
HWND square;
HWND triangle;
HWND hexagon;


CHOOSECOLOR  colorPick;
COLORREF acrCustClr[16]; // array of custom colors
COLORREF backColor;
COLORREF lineColor;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    Start(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32FRACTALI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32FRACTALI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32FRACTALI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32FRACTALI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 380,290 , nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		
		// creaza butoanele si controlerele
		chBackColor = CreateWindowEx(0, L"BUTTON", L"Background color", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			10, 10, 150, 24, hWnd, NULL, NULL, NULL);
		chLineColor = CreateWindowEx(0, L"BUTTON", L"Line color", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			10, 35, 150, 24, hWnd, NULL, NULL, NULL);
		square = CreateWindowEx(0, L"BUTTON", L"Patrat", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			200, 10, 150, 24, hWnd, NULL, NULL, NULL);
		triangle = CreateWindowEx(0, L"BUTTON", L"Triunghi", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			200, 55, 150, 24, hWnd, NULL, NULL, NULL);
		hexagon = CreateWindowEx(0, L"BUTTON", L"Hexagon", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			200, 100, 150, 24, hWnd, NULL, NULL, NULL);
		chWidthLine = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER,
			110, 60, 40, 20, hWnd, NULL, NULL, NULL);
		chMinDist = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER,
			110, 85, 40, 20, hWnd, NULL, NULL, NULL);
		chSpeed = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER,
			110, 110, 40, 20, hWnd, NULL, NULL, NULL);

		// Initialize CHOOSECOLOR
		ZeroMemory(&colorPick, sizeof(CHOOSECOLOR));
		colorPick.lStructSize = sizeof(CHOOSECOLOR);
		colorPick.hwndOwner = hWnd;
		colorPick.lpCustColors = (LPDWORD)acrCustClr;
		colorPick.Flags = CC_FULLOPEN | CC_RGBINIT;
	}
	break;
	
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
			switch (wmId)
			{

			case BN_CLICKED:
			{
				if (chBackColor == (HWND)lParam) {

					if (ChooseColor(&colorPick) == TRUE) {
						backColor = colorPick.rgbResult;
					}
				}
				if (chLineColor == (HWND)lParam) {
					if (ChooseColor(&colorPick) == TRUE) {
						lineColor = colorPick.rgbResult;
					}
				}
				if (square == (HWND)lParam)
				{
					HWND stDiag = CreateDialog(hInst, MAKEINTRESOURCE(IDD_START), hWnd, (DLGPROC)Start);
	
					HDC hdc = GetDC(stDiag);
					ShowWindow(stDiag, SW_SHOW);
					
				}
			}
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
		TextOut(hdc, 10, 60, L"Latime Linie:", 13);
		TextOut(hdc, 10, 85, L"Minim:",6);
		TextOut(hdc, 10, 110, L"Viteza:", 7);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hDlg, &ps);
	}
	break;
    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK Start(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);
		// TODO: Add any drawing code that uses hdc here...
		draw(hdc);
		EndPaint(hDlg, &ps);
	}
	break;
	}
	return (INT_PTR)FALSE;
}


