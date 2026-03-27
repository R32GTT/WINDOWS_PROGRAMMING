#include <windows.h>
#include <random>
#include <vector>
#include <string>
#include <format>
#define WINX 800
#define WINY 600
HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";
LPCTSTR lpszWindowName2 = L"windows program 2";
RECT WinSize{ 0,0,WINX,WINY };

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

std::random_device rd;
std::mt19937 mt19(rd());
std::uniform_int_distribution xRange(0, 600);
std::uniform_int_distribution yRange(0, 500);
std::uniform_int_distribution rgb(0, 255);
std::uniform_int_distribution f(1, 2);

class VecSize
{
public:
	VecSize(int X, int Y) :x(X), y(Y) {}
	VecSize operator+(VecSize rhs)
	{
		x += rhs.x; y += rhs.y; return *this;
	}

	int x;
	int y;
};

class Text
{
public:
	int rcount;
	int count;
	std::wstring wstr;
};

Text _text;
int x = xRange(mt19);
int y = yRange(mt19);
COLORREF textcolor = RGB(rgb(mt19), rgb(mt19), rgb(mt19));

SIZE _size;

RECT Rsize{ x,y,WINX,WINY };
std::wstring str;
HFONT hFont = CreateFontW(12, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	CLEARTYPE_QUALITY, FF_MODERN, L"Arial"
);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass{};
	g_hinst = hinstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.hInstance = hinstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpszClassName = lpszClass;
	WndClass.style = CS_CLASSDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	//WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// WndClass.hbrBackground = NULL;
	RegisterClassEx(&WndClass);

	//hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 960, NULL, (HMENU)NULL, hinstance, NULL);
	AdjustWindowRect(&WinSize, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(lpszClass, lpszWindowName2, WS_OVERLAPPEDWINDOW | WS_SIZEBOX, 100, 50, 800, 600, NULL, (HMENU)NULL, hinstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	HDC hDCS = GetDC(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	ReleaseDC(hWnd, hDCS);
	DeleteObject(hFont);
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HBRUSH rectBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//GetClientRect(hWnd, &WinSize);
	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 1, 12);
		ShowCaret(hWnd);
		SetCaretPos(x, y);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		//SelectObject(hDC, rectBrush);
		GetTextExtentPoint32(hDC, _text.wstr.c_str(), _text.wstr.size(), &_size);
		//TextOut(hDC, x, y, _text.wstr.c_str(), _text.wstr.size());
		DrawText(hDC, _text.wstr.c_str(), _text.wstr.size(), &Rsize, DT_LEFT | DT_TOP);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CHAR:

		HDC hDC;
		SIZE size;
		POINT caretPos;
		switch (wParam)
		{
		case VK_RETURN:

			if (y > 600)
				return 0;
			if (_text.rcount >= 4)
				return 0;

			_text.wstr += L"\n";
			_text.rcount++;
			hDC = GetDC(hWnd);

			GetCaretPos(&caretPos);
			GetTextExtentPoint32W(hDC, reinterpret_cast<LPCWSTR>(&wParam), 1, &size);
			SetCaretPos(x, caretPos.y + size.cy);

			ReleaseDC(hWnd, hDC);
			break;
		case VK_BACK:
			if (_text.wstr.empty())
				break;
			_text.wstr.pop_back();
			InvalidateRect(hWnd, NULL, true);
			hDC = GetDC(hWnd);
			GetCaretPos(&caretPos);
			GetTextExtentPoint32W(hDC, reinterpret_cast<LPCWSTR>(&wParam), 1, &size);
			SetCaretPos(x + size.cx, caretPos.y + size.cy);

			ReleaseDC(hWnd, hDC);
			break;
		case VK_ESCAPE:

			HideCaret(hWnd);
			DestroyCaret();
			DestroyWindow(hWnd);
			DeleteObject(hWnd);
			PostQuitMessage(0);
			return 0;
		default:
		{
			if (_text.wstr.size() == 105)
			{
				break;
			}
			hDC = GetDC(hWnd);
			SIZE size;
			POINT caretPos;
			GetCaretPos(&caretPos);
			GetTextExtentPoint32W(hDC, reinterpret_cast<LPCWSTR>(&wParam), 1, &size);
			if (_text.wstr.size() % 21 == 20)
			{
				_text.wstr += L'\n';
				SetCaretPos(x, caretPos.y + size.cy);
			}
			else {
				_text.wstr += wParam;
				SetCaretPos(caretPos.x + size.cx, caretPos.y);
			}
			ReleaseDC(hWnd, hDC);
			break;
		}
		}
		InvalidateRect(hWnd, NULL, true);

		break;
	case WM_DESTROY:

		HideCaret(hWnd);
		DestroyCaret();
		DestroyWindow(hWnd);
		DeleteObject(hWnd);
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}