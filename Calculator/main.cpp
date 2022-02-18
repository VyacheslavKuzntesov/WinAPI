#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"

CONST UINT start_x = 10;
CONST UINT start_y = 70;

CONST UINT i_btn_size = 50;
CONST UINT interval = 2;

CONST UINT WINDOW_WIDTH = 293;
CONST UINT WINDOW_HEIGHT = 324;

CONST CHAR g_szClassName[] = "Calculator";
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//#define DZ

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = (HICON)LoadImage(hInstance, "calc8.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	wc.hIconSm = (HICON)LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_szClassName;
	wc.lpszMenuName = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND hwnd = CreateWindowEx
	(
		NULL,														//exSryles
		g_szClassName,												//Window class
		g_szClassName,												//Windows title
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,	//Style
		CW_USEDEFAULT, CW_USEDEFAULT,								//Position
		WINDOW_WIDTH, WINDOW_HEIGHT,								//Size
		NULL,														//Parent window
		NULL,														//Menu
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//////////////////////////////////////////////////
		///////////////		Create 	display		//////////
		//////////////////////////////////////////////////
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",							//Window class for EditControl
			NULL,
			WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY | ES_NUMBER | WS_BORDER,
			10, 10,
			(WINDOW_WIDTH - 35), i_btn_size,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);

		//////////////////////////////////////////////////
		///////////////		Create buttons		//////////
		//////////////////////////////////////////////////

		/*UINT	start_x = 10;
		UINT	start_y = 70;*/
		/*UINT	i_btn_size = 50;
		UINT	interval = 2;*/

		INT		digit = 1;
		CHAR	sz_digit[5];

		for (INT i = 2; i >= 0; i--)
		{

			for (INT j = 0; j < 3; j++)
			{
				CreateWindowEx
				(
					NULL, "Button", _itoa(digit, sz_digit, 10),
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					start_x + (i_btn_size + interval) * j, start_y + (i_btn_size + interval) * i,
					i_btn_size, i_btn_size,
					hwnd, (HMENU)(IDC_BTN_0 + digit),
					GetModuleHandle(NULL), NULL
				);
				digit++;
			}
		}
		//									Zero & Point
		CreateWindowEx
		(
			NULL, "BUTTON", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x, start_y + (i_btn_size + interval) * 3,
			i_btn_size * 2 + interval, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_0), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "BUTTON", ".", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 2, start_y + (i_btn_size + interval) * 3,
			i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_POINT), GetModuleHandle(NULL), NULL
		);

		//									Operations:

		CreateWindowEx
		(
			NULL, "BUTTON", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 3, start_y,
			i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_DIVISION), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "BUTTON", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 3, start_y + i_btn_size + interval,
			i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_MULTIPLICATION), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "BUTTON", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 3, start_y + (i_btn_size + interval)*2,
			i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_MINUS), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "BUTTON", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 3, start_y + (i_btn_size + interval) * 3,
			i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_PLUS), GetModuleHandle(NULL), NULL
		);

		CreateWindowEx
		(
			NULL, "BUTTON", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 4, start_y,
			i_btn_size, i_btn_size * 2 + interval,
			hwnd, (HMENU)(IDC_BTN_CLEAR), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "BUTTON", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 4, start_y + (i_btn_size + interval) * 2,
			i_btn_size, i_btn_size * 2 + interval,
			hwnd, (HMENU)(IDC_BTN_EQUAL), GetModuleHandle(NULL), NULL
		);
	}
	break;
	case WM_COMMAND:
	{

#ifdef DZ
		CONST INT SIZE = 256;
		CHAR buffer[SIZE]{};
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);

		if ((LOWORD(wParam) == IDC_BTN_0) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "0");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		if ((LOWORD(wParam) == IDC_BTN_1) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "1");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		if ((LOWORD(wParam) == IDC_BTN_2) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "2");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		if ((LOWORD(wParam) == IDC_BTN_3) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "3");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		if ((LOWORD(wParam) == IDC_BTN_4) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "4");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		if ((LOWORD(wParam) == IDC_BTN_5) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "5");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		if ((LOWORD(wParam) == IDC_BTN_6) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "6");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		if ((LOWORD(wParam) == IDC_BTN_7) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "7");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		if ((LOWORD(wParam) == IDC_BTN_8) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "8");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
	}
		if ((LOWORD(wParam) == IDC_BTN_9) && (HIWORD(wParam) == BN_CLICKED))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			strcat(buffer, "9");
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)buffer);
		}
#endif // DZ

		if (LOWORD(wParam) >= IDC_BTN_0 && LOWORD(wParam) <= IDC_BTN_9)
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			CHAR sz_digit[2] = {};
			sz_digit[0] = LOWORD(wParam) - 1000 + 48;
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
	return 0;
}