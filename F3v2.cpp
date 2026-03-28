#include <windows.h>
#include <random>
#include <vector>
#include <string>
#include <format>
#include <functional>

HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";
LPCTSTR lpszWindowName2 = L"windows program 2";

int WINX = 800;
int WINY = 600;
RECT WinSize{ 0,0,WINX,WINY };

std::wstring bufferStream;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class VecSize
{
public:
	VecSize(int X, int Y) :x(X), y(Y) {}
	VecSize() {}
	VecSize operator+(VecSize rhs)
	{
		return VecSize(x + rhs.x, y + rhs.y);
	}

	int x;
	int y;
};

class Text
{
public:
	Text() {}
	Text(int n, int cnt) : wcount(n), count(cnt) {	}

	void RENDER(HDC hDC)
	{
		SIZE size;
		POINT caretPos;
	}

	int count;
	int wcount;
	std::wstring wstr;
	COLORREF _textcolor;
	COLORREF _backgroundcolor;
};

Text _text;

SIZE _size;

std::wstring str;
HFONT hFont = CreateFontW(12, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	CLEARTYPE_QUALITY, FF_MODERN, L"Arial"
);

int x = 4;

VecSize Cursor;
std::vector<Text> Notepad;
TEXTMETRICW TM;

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPWSTR lpszCmdParam, int nCmdShow)
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

	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	RegisterClassEx(&WndClass);

	for (int i = 0; i < 10; i++)
		Notepad.push_back(Text(0, 0));

	AdjustWindowRect(&WinSize, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(lpszClass, lpszWindowName2, WS_OVERLAPPEDWINDOW | WS_SIZEBOX, 100, 50, WinSize.right - WinSize.left, WinSize.bottom - WinSize.top, NULL, (HMENU)NULL, hinstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	HDC HHDC = GetDC(hWnd);
	GetTextMetricsW(HHDC, &TM);
	ReleaseDC(hWnd, HHDC);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	DeleteObject(hFont);
	return Message.wParam;
}
std::vector<int> decode;
bool Looped = false;
std::wstring temp1;
std::wstring tems;
bool CHECKINSERT = false;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 2, 16);
		ShowCaret(hWnd);
		SetCaretPos(5, 0);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);

		for (int i = 0; i < 10; i++)
		{
			TextOut(hDC, x, (i * TM.tmHeight), Notepad[i].wstr.c_str(), Notepad[i].wstr.size());
		}

		SetTextColor(hDC, 0);
		SetBkColor(hDC, RGB(255, 255, 255));
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_KEYDOWN:
	{
		HDC hDC;
		SIZE size;
		POINT caretPos;
		switch (wParam)
		{
		case VK_PRIOR:
			hDC = GetDC(hWnd);
			tems.clear();
			Cursor.y = (Cursor.y + 7) % 10;
			GetCaretPos(&caretPos);
			if (!Notepad[Cursor.y].wstr.empty())
			{
				Cursor.x = Notepad[Cursor.y].wstr.size();
				temp1 = Notepad[Cursor.y].wstr;
				GetTextExtentPointW(hDC, temp1.c_str(), temp1.size(), &size);
				SetCaretPos(x + size.cx, TM.tmHeight * Cursor.y);
			}
			else
			{
				Cursor.x = 0;
				SetCaretPos(x, TM.tmHeight * Cursor.y);
			}

			ReleaseDC(hWnd, hDC);
			break;
		case VK_NEXT:
			Cursor.y = (Cursor.y + 3) % 10;
			GetCaretPos(&caretPos);
			hDC = GetDC(hWnd);
			tems.clear();

			GetCaretPos(&caretPos);
			if (!Notepad[Cursor.y].wstr.empty())
			{
				Cursor.x = Notepad[Cursor.y].wstr.size();
				temp1 = Notepad[Cursor.y].wstr;
				GetTextExtentPointW(hDC, temp1.c_str(), temp1.size(), &size);
				SetCaretPos(x + size.cx, TM.tmHeight * Cursor.y);
			}
			else
			{
				Cursor.x = 0;
				SetCaretPos(x, TM.tmHeight * Cursor.y);
			}
			break;
		case VK_LEFT:
			GetCaretPos(&caretPos);
			tems.clear();

			if (Cursor.x == 0 && Cursor.y == 0) // 00 리셋
				break;
			else if (Cursor.x == 0 && Cursor.y > 0 && !Notepad[Cursor.y - 1].wstr.empty()) //1칸 위 + 맨 끝
			{
				hDC = GetDC(hWnd);
				temp1 = Notepad[Cursor.y - 1].wstr;
				GetTextExtentPointW(hDC, temp1.c_str(), temp1.size(), &size);
				Cursor.x = Notepad[Cursor.y - 1].wstr.size();
				Cursor.y--;
				SetCaretPos(x + (size.cx), caretPos.y - TM.tmHeight);
				ReleaseDC(hWnd, hDC);
				break;
			}
			else if (Cursor.x == 0 && Cursor.y > 0 && Notepad[Cursor.y - 1].wstr.empty())
			{
				Cursor.y--;
				SetCaretPos(x, caretPos.y - TM.tmHeight);

				break;
			}
			else if (Cursor.x > 0)
			{
				hDC = GetDC(hWnd);
				Cursor.x--;
				temp1 = Notepad[Cursor.y].wstr[Cursor.x];
				GetTextExtentPointW(hDC, temp1.c_str(), 1, &size);
				SetCaretPos(caretPos.x - size.cx, caretPos.y);

				ReleaseDC(hWnd, hDC);
			}
			break;
			break;
		case VK_RIGHT:
			tems.clear();
			GetCaretPos(&caretPos);
			if ((Cursor.x == 30 && Cursor.y == 9) || (Cursor.x == Notepad[Cursor.y].wstr.size() && Cursor.y == 9)) // 00 리셋
			{
				Cursor.x = 0;
				Cursor.y = 0;
				SetCaretPos(x, 0);
				break;
			}
			else if (Cursor.x == Notepad[Cursor.y].wstr.size() && Cursor.y <= 9 && !Notepad[Cursor.y + 1].wstr.empty()) //1칸 아래  + 맨 끝
			{
				Cursor.x = 0;
				Cursor.y++;
				SetCaretPos(x, caretPos.y + TM.tmHeight);
				break;
			}

			else if (Cursor.x >= 0)
			{
				if (!Notepad[Cursor.y].wstr.empty())
				{
					if (Notepad[Cursor.y].wstr.size() >= (Cursor.x + 1))
					{
						hDC = GetDC(hWnd);

						temp1 = Notepad[Cursor.y].wstr[Cursor.x];
						Cursor.x++;
						GetTextExtentPointW(hDC, temp1.c_str(), 1, &size);
						SetCaretPos(caretPos.x + size.cx, caretPos.y);

						ReleaseDC(hWnd, hDC);
					}
				}
			}
			break;
		case VK_UP:
			tems.clear();
			GetCaretPos(&caretPos);
			if (Cursor.y > 0 && !Notepad[Cursor.y - 1].wstr.empty())
			{
				Cursor.y--;
				if (Notepad[Cursor.y].wstr.size() >= Cursor.x)
				{
					hDC = GetDC(hWnd);
					temp1 = Notepad[Cursor.y].wstr;
					GetTextExtentPointW(hDC, temp1.c_str(), Cursor.x, &size);
					ReleaseDC(hWnd, hDC);
					SetCaretPos(x + size.cx, caretPos.y - TM.tmHeight);
				}
				else
				{
					hDC = GetDC(hWnd);
					temp1 = Notepad[Cursor.y].wstr;
					GetTextExtentPointW(hDC, temp1.c_str(), temp1.size(), &size);
					ReleaseDC(hWnd, hDC);
					Cursor.x = temp1.size();
					SetCaretPos(x + size.cx, caretPos.y - TM.tmHeight);
				}
			}
			break;
		case VK_DOWN:
			tems.clear();
			GetCaretPos(&caretPos);
			if (Cursor.y < 9 && !Notepad[Cursor.y].wstr.empty())
			{
				Cursor.y++;
				if (Notepad[Cursor.y].wstr.size() >= Cursor.x)
				{
					hDC = GetDC(hWnd);
					temp1 = Notepad[Cursor.y].wstr;
					GetTextExtentPointW(hDC, temp1.c_str(), Cursor.x, &size);
					ReleaseDC(hWnd, hDC);
					SetCaretPos(x + size.cx, caretPos.y + TM.tmHeight);
				}
				else if (Notepad[Cursor.y].wstr.empty())
				{
					Cursor.x = 0;
					SetCaretPos(x, caretPos.y + TM.tmHeight);
				}
				else
				{
					hDC = GetDC(hWnd);
					temp1 = Notepad[Cursor.y].wstr;
					GetTextExtentPointW(hDC, temp1.c_str(), temp1.size(), &size);
					ReleaseDC(hWnd, hDC);
					Cursor.x = temp1.size();
					SetCaretPos(x + size.cx, caretPos.y + TM.tmHeight);
				}
			}

			break;
		case VK_INSERT:
			if (CHECKINSERT)
			{
				CHECKINSERT = false;
			}
			else
				CHECKINSERT = true;
			break;
		case VK_HOME:
			Cursor.x = 0;
			GetCaretPos(&caretPos);
			SetCaretPos(x, caretPos.y);
			break;
		case VK_END:
			hDC = GetDC(hWnd);
			GetCaretPos(&caretPos);
			int sk;
			sk = Notepad[Cursor.y].wstr.size();
			if (!Notepad[Cursor.y].wstr.empty() && sk == 30 && Cursor.y < 9)
			{
				Cursor.x = 0;
				Cursor.y++;
				SetCaretPos(x, caretPos.y + TM.tmHeight);
			}
			else if (!Notepad[Cursor.y].wstr.empty())
			{
				GetTextExtentPointW(hDC, Notepad[Cursor.y].wstr.c_str(), sk, &size);
				Cursor.x = sk;
				SetCaretPos(x + size.cx, caretPos.y);
			}

			ReleaseDC(hWnd, hDC);
			break;
		case VK_DELETE:
			if (Notepad[Cursor.y].wstr.empty())
				break;
			int front, last;
			for (int i = Cursor.x; i <= Notepad[Cursor.y].wstr.size(); i++) // 후열 공백 찾기
			{
				if (Notepad[Cursor.y].wstr[i] == L' ')
				{
					last = i;
					break;
				}
				else if (i == Notepad[Cursor.y].wstr.size())
				{
					last = i;
				}
			}
			for (int i = Cursor.x; i >= 0; i--) // 전열 공백 찾기
			{
				if (Notepad[Cursor.y].wstr[i] == L' ')
				{
					front = i;
					break;
				}
				else if (i == 0)
				{
					front = 0;
				}
			}
			Notepad[Cursor.y].wstr.erase(front, last);
			Cursor.x = front;
			hDC = GetDC(hWnd);
			GetCaretPos(&caretPos);
			tems.clear();
			GetTextExtentPointW(hDC, Notepad[Cursor.y].wstr.c_str(), Notepad[Cursor.y].wstr.size(), &size);
			SetCaretPos(x + size.cx, caretPos.y);
			ReleaseDC(hWnd, hDC);
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		break;
	}
	case WM_CHAR:

		HDC hDC;
		SIZE size;
		POINT caretPos;

		switch (wParam)
		{
		case VK_RETURN:

			hDC = GetDC(hWnd);
			GetCaretPos(&caretPos);
			if (Cursor.y == 9)
			{
				Cursor.x = 0;
				Cursor.y = 0;
				Looped = true;
				SetCaretPos(x, 0);
				ReleaseDC(hWnd, hDC);
				break;
			}
			else
			{
				Cursor.x = 0;
				Cursor.y++;
			}

			SetCaretPos(x, caretPos.y + TM.tmHeight);
			ReleaseDC(hWnd, hDC);
			break;
		case VK_BACK:
			hDC = GetDC(hWnd);
			SIZE size;
			POINT caretPos;
			GetCaretPos(&caretPos);
			tems.clear();
			if (Cursor.y > 0 && Cursor.x == 0)
			{
				Cursor.y--;
				Cursor.x = Notepad[Cursor.y].wstr.size();
				tems = Notepad[Cursor.y].wstr;
				GetTextExtentPointW(hDC, tems.c_str(), tems.size(), &size);

				SetCaretPos(x + size.cx, caretPos.y - TM.tmHeight);
				ReleaseDC(hWnd, hDC);
				break;
			}
			if (Notepad[Cursor.y].wstr.empty())
				break;
			if (Cursor.y == 0 && Cursor.x == 0)
				break;

			temp1 = Notepad[Cursor.y].wstr[Cursor.x - 1];
			GetTextExtentPointW(hDC, temp1.c_str(), 1, &size);
			if (Notepad[Cursor.y].wstr[Cursor.x] == NULL)
			{
				Notepad[Cursor.y].wstr.pop_back();
			}
			else
			{
				tems = Notepad[Cursor.y].wstr.substr(Cursor.x, Notepad[Cursor.y].wstr.size() - Cursor.x);
				Notepad[Cursor.y].wstr.erase(Cursor.x - 1, 30);
				Notepad[Cursor.y].wstr += tems;
			}

			Cursor.x--;
			SetCaretPos(caretPos.x - size.cx, caretPos.y);

			ReleaseDC(hWnd, hDC);
			break;
		case VK_ESCAPE:
			for (auto& a : Notepad)
				a.wstr.clear();
			Cursor.x = 0;
			Cursor.y = 0;
			SetCaretPos(x, 0);
			break;
		case VK_TAB:
			tems.clear();
			GetCaretPos(&caretPos);
			if (Cursor.y < 9)
			{
				std::wstring temp3;
				temp3 = L"    ";
				int delta;
				if (Notepad[Cursor.y].wstr.size() <= 26)
				{
					Notepad[Cursor.y].wstr.insert(Cursor.x, temp3);
					Cursor.x += 4;
					hDC = GetDC(hWnd);
					GetTextExtentPointW(hDC, temp3.c_str(), temp3.size(), &size);
					ReleaseDC(hWnd, hDC);
					SetCaretPos(caretPos.x + size.cx, caretPos.y);
				}
				else if (Cursor.x >= 27)
				{
					delta = 30 - Notepad[Cursor.y].wstr.size();
					temp3 = temp3.substr(0, delta);
					Notepad[Cursor.y].wstr.insert(Cursor.x, temp3);
					Cursor.x = 0;
					Cursor.y++;
					hDC = GetDC(hWnd);
					GetTextExtentPointW(hDC, temp3.c_str(), temp3.size(), &size);
					ReleaseDC(hWnd, hDC);
					SetCaretPos(x, caretPos.y + TM.tmHeight);
				}
				else
				{
					delta = 30 - Notepad[Cursor.y].wstr.size();
					temp3 = temp3.substr(0, delta);
					Notepad[Cursor.y].wstr.insert(Cursor.x, temp3);
					Cursor.x += delta;
					hDC = GetDC(hWnd);
					GetTextExtentPointW(hDC, temp3.c_str(), temp3.size(), &size);
					ReleaseDC(hWnd, hDC);
					SetCaretPos(caretPos.x + size.cx, caretPos.y);
				}
			}
			else if (Cursor.y == 9)
			{
				std::wstring temp3;
				temp3 = L"    ";
				int delta;
				if (Notepad[Cursor.y].wstr.size() <= 26)
				{
					Notepad[Cursor.y].wstr.insert(Cursor.x, temp3);
					Cursor.x += 4;
					hDC = GetDC(hWnd);
					GetTextExtentPointW(hDC, temp3.c_str(), temp3.size(), &size);
					ReleaseDC(hWnd, hDC);
					SetCaretPos(caretPos.x + size.cx, caretPos.y);
				}
				else
				{
					delta = 30 - Notepad[Cursor.y].wstr.size();
					temp3 = temp3.substr(0, delta);
					Notepad[Cursor.y].wstr.insert(Cursor.x, temp3);
					Cursor.x += delta;
					hDC = GetDC(hWnd);
					GetTextExtentPointW(hDC, temp3.c_str(), temp3.size(), &size);
					ReleaseDC(hWnd, hDC);
					SetCaretPos(caretPos.x + size.cx, caretPos.y);
				}
			}
			break;
		default:
		{
			hDC = GetDC(hWnd);
			SIZE size;
			POINT caretPos;
			GetCaretPos(&caretPos);
			std::wstring temp;
			temp.clear();
			temp = wParam;
			GetTextExtentPointW(hDC, temp.c_str(), temp.size(), &size);
			if (Cursor.x == 30 && Cursor.y == 9)
			{
				Cursor.x = 0; Cursor.y = 0;
				SetCaretPos(x, 0);
				Looped = true;
			}
			else if (Cursor.x < 30)
			{
				if (!CHECKINSERT)
				{
					if (Notepad[Cursor.y].wstr[Cursor.x] == NULL)
					{
						Notepad[Cursor.y].wstr.insert(Cursor.x++, temp);
					}
					else
					{
						Notepad[Cursor.y].wstr[Cursor.x++] = temp[0];
					}
					SetCaretPos(caretPos.x + size.cx, caretPos.y);
				}
				else
				{
					if (Cursor.x < 30 && Notepad[Cursor.y].wstr.size() < 30)
					{
						Notepad[Cursor.y].wstr.insert(Cursor.x++, temp);
						SetCaretPos(caretPos.x + size.cx, caretPos.y);
					}
				}
			}
			else if (Cursor.x >= 30)
			{
				Cursor.x = 0;
				Cursor.y++;
				SetCaretPos(x, caretPos.y + TM.tmHeight);
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