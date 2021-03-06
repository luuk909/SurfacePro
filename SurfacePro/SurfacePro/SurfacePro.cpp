// GT_HelloWorldWin32.cpp  
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c  

#include "stdafx.h"
#include "SurfacePro.h"
#include <windows.h>  
#include <windowsx.h>
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>

#define MAXPOINTS 10

// You will use this array to track touch points
int points[MAXPOINTS][2];

// You will use this array to switch the color / track ids
int idLookup[MAXPOINTS];


// You can make the touch points larger
// by changing this radius value
static int radius = 50;

// There should be at least as many colors
// as there can be touch points so that you
// can have different colors for each point
COLORREF colors[] = {
	RGB(153,255,51),
	RGB(153,0,0),
	RGB(0,153,0),
	RGB(255,255,0),
	RGB(255,51,204),
	RGB(0,0,0),
	RGB(0,153,0),
	RGB(153, 255, 255),
	RGB(153,153,255),
	RGB(0,51,153)
};
int wmId, wmEvent, i, x, y;

UINT cInputs;
PTOUCHINPUT pInputs;
POINT ptInput;

// For double buffering
static HDC memDC = 0;
static HBITMAP hMemBmp = 0;
HBITMAP hOldBmp = 0;

// For drawing / fills
PAINTSTRUCT ps;
HDC hdc;

// For tracking dwId to points
int index;

// Global variables  

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

static UINT windowWidth = 800;
static UINT windowHeight = 600;

HINSTANCE hInst;

// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SURFACEPRO));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

					   // The parameters to CreateWindow explained:  
					   // szWindowClass: the name of the application  
					   // szTitle: the text that appears in the title bar  
					   // WS_OVERLAPPEDWINDOW: the type of window to create  
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
					   // 500, 100: initial size (width, length)  
					   // NULL: the parent of this window  
					   // NULL: this application does not have a menu bar  
					   // hInstance: the first parameter from WinMain  
					   // NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowWidth, windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	RegisterTouchWindow(hWnd, 0);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// the following code initializes the points
	for (int i = 0; i < MAXPOINTS; i++) {
		points[i][0] = -1;
		points[i][1] = -1;
		idLookup[i] = -1;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	//ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

// This function is used to return an index given an ID
int GetContactIndex(int dwID) {
	for (int i = 0; i < MAXPOINTS; i++) {
		if (idLookup[i] == -1) {
			idLookup[i] = dwID;
			return i;
		}
		else {
			if (idLookup[i] == dwID) {
				return i;
			}
		}
	}
	// Out of contacts
	return -1;
}

//  
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  PURPOSE:  Processes messages for the main window.  
//  
//  WM_PAINT    - Paint the main window  
//  WM_DESTROY  - post a quit message and return  
//  
//  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH redbrush, whitebrush;
	//vars for WM_TOUCH
	int i, x, y, index;
	UINT cInputs;
	PTOUCHINPUT pInputs;
	POINT ptInput;


	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_TOUCH:
		//LOWORD(wParam) = number of touch points in this message
		//HIWORD(wParam) = reserved for future use
		//lParam = handle for use with GetTouchInputInfo
		cInputs = LOWORD(wParam);
		pInputs = new TOUCHINPUT[cInputs];
		if (pInputs)
		{
			if (GetTouchInputInfo((HTOUCHINPUT)lParam, cInputs, pInputs, sizeof(TOUCHINPUT)))
			{
				for (int i = 0; i < static_cast<INT>(cInputs); i++)
				{
					TOUCHINPUT ti = pInputs[i];
					index = GetContactIndex(ti.dwID);


					if (ti.dwID != 0 && index < MAXPOINTS)
					{
						//get screen corrdinates of touch
						ptInput.x = TOUCH_COORD_TO_PIXEL(ti.x);
						ptInput.y = TOUCH_COORD_TO_PIXEL(ti.y);

						//get coordinates relative to the top left of the application window
						ScreenToClient(hWnd, &ptInput);


						if (ti.dwFlags & TOUCHEVENTF_UP)
						{
							points[index][0] = -1;
							points[index][1] = -1;
						}
						else
						{
							points[index][0] = ptInput.x;
							points[index][1] = ptInput.y;
						}
					}
				}
			}
			CloseTouchInputHandle((HTOUCHINPUT)lParam);
			delete[] pInputs;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		/*case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;*/
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		RECT client;
		GetClientRect(hWnd, &client);

		// start double buffering
		if (!memDC)
		{
			memDC = CreateCompatibleDC(hdc);
		}
		hMemBmp = CreateCompatibleBitmap(hdc, client.right, client.bottom);
		hOldBmp = (HBITMAP)SelectObject(memDC, hMemBmp);
		whitebrush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(memDC, &client, whitebrush);
		redbrush = CreateSolidBrush(RGB(255, 0, 0));
		//Draw Touched Points                
		for (i = 0; i < MAXPOINTS; i++)
		{
			SelectObject(memDC, redbrush);
			x = points[i][0];
			y = points[i][1];
			if (x > 0 && y > 0)
			{
				Ellipse(memDC, x - radius, y - radius, x + radius, y + radius);
			}
		}
		BitBlt(hdc, 0, 0, client.right, client.bottom, memDC, 0, 0, SRCCOPY);
		DeleteObject(redbrush);
		DeleteObject(whitebrush);
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}