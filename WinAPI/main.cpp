#include<Windows.h>
#include"resource.h"

CONST CHAR INVITATION[] = "Введите логин";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(FindWindow(NULL,"WinAPI - Microsoft Visual Studio Preview"), "Привет! Это мое первое окно сообщения.", "Hello World",
	//	MB_ICONWARNING | MB_YESNOCANCEL | MB_HELP | MB_DEFBUTTON3 | MB_SYSTEMMODAL);
	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:		//Инициализация окна(создание значков и т.д.)
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		//Установка фокуса:
		//SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETFOCUS, NULL, 0);
	}
		break;
	case WM_COMMAND:		//Обработка команд нажатия кнопок и т.д.
	{
		//WORD = 2BYTES
		//DWORD = 4 BYTES
		//LOWORD - два младших Байта в двойном слове
		//HIWORD - два старших Байта в двойном слове
		switch (LOWORD(wParam))
		{
			case IDC_BTN_COPY:
			{
				CONST INT SIZE = 256;
				CHAR buffer[SIZE]{};
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_LOGIN);					//Получаем HWND элемента окна по его ResourceID
				SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
				SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_SETTEXT, 0, (LPARAM)buffer);
			}
			break;
			case IDOK:	   MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_ICONINFORMATION | MB_OK); break;
			case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
		break;
	case WM_CLOSE:			//Закрытие окна
		EndDialog(hwnd, 0);
	}
	return FALSE;
}