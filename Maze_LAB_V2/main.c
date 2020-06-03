#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "maze_func.h"

const int MaxSize = 17;
const int SqSize = 50;
const char g_szClassName[] = "myWindowClass";
HWND hButton1;
HWND HwndStatic1;
HWND SizeWind;
#define BT_1		201
#define ST_1        202 


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int width, height;
	RECT rect = { 0, 0, 0, 0 };
	HWND hw;
	RECT textRect = { 900, 60, 1600, 80 };
	switch (msg)
	{
	case WM_COMMAND:
		// в параметре wParam идентификатор нажатой кнопки
		switch (LOWORD(wParam))
		{
		case BT_1:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LPCWSTR coordsString = (WCHAR*)malloc(30 * sizeof(WCHAR));				
				GetWindowText(SizeWind, coordsString, 30);
				DeleteMaze();
				Size = _wtoi(coordsString);
				srand((unsigned int)time(0));
				if (Size < 1 || Size > MaxSize) {
					Size = rand() % 10 + 5;
				}
				GenerateMaze();
				const RECT ReRect = { 0, 0, MaxSize * SqSize, MaxSize * SqSize };
				InvalidateRect(hwnd, &ReRect, TRUE);
				free(coordsString);
			}
			break;
		default:
			break;
		}
		break;
	
	case WM_SIZE:
		width = LOWORD(lParam);
		height = HIWORD(lParam);
	case WM_PAINT:		
		hdc = BeginPaint(hwnd, &ps);
		srand((unsigned int)time(0));
		HBRUSH hbrush;
		HPEN hpen;
		DrawText(hdc, L"Input Size [1, 17] here:", 24, &textRect, DT_LEFT);
		hbrush = CreateSolidBrush(RGB(63, 155, 11));
		SelectObject(hdc, hbrush);
		rect.left = 0;
		rect.top = 0;
		rect.right = Size * SqSize;
		rect.bottom = Size * SqSize;
		FillRect(hdc, &rect, hbrush);
		DeleteObject(hbrush);
		hpen = CreatePen(PS_SOLID, 2, RGB(150, 75, 0));
		SelectObject(hdc, hpen);
		Rectangle(hdc, 0, 0, Size * SqSize + 2, Size * SqSize + 2);
		DeleteObject(hpen);
		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++) {
				if (Maze[i][j] == 0) {
					hbrush = CreateSolidBrush(RGB(160, 54, 35));
					SelectObject(hdc, hbrush);
					Rectangle(hdc, i* SqSize, j* SqSize, i * SqSize + SqSize, j * SqSize + SqSize);
					DeleteObject(hbrush);
					hpen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
					SelectObject(hdc, hpen);
					MoveToEx(hdc, i * SqSize + 25, j * SqSize, NULL);
					LineTo(hdc, i * SqSize + 25, j * SqSize + 25);

					MoveToEx(hdc, i * SqSize, j * SqSize + 25, NULL);
					LineTo(hdc, i * SqSize + SqSize, j * SqSize + 25);

					MoveToEx(hdc, i * SqSize + 10, j * SqSize + 25, NULL);
					LineTo(hdc, i * SqSize + 10, j * SqSize + SqSize);

					MoveToEx(hdc, i * SqSize + 40, j * SqSize + 25, NULL);
					LineTo(hdc, i * SqSize + 40, j * SqSize + SqSize);

					DeleteObject(hpen);

				}
			}
		}
		EndPaint(hwnd, &ps);

		return 0;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Size = 10;	
	srand((unsigned int)time(0));
	GenerateMaze();

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Windows
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"LAB",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1100, 1000,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hButton1 = CreateWindow(L"button", L"button",
		WS_VISIBLE | WS_CHILD | BS_NOTIFY,
		900, 100,
		150, 50,
		hwnd, (HMENU)BT_1, hInstance, NULL);
	SetWindowText(hButton1, L"Confirm");
	
	SizeWind = CreateWindow(L"edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
		900, 80,
		150, 20,
		hwnd, (HMENU)ST_1, hInstance, NULL);
	SetWindowText(SizeWind, L"");

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	
	DeleteMaze();
	return Msg.wParam;
}