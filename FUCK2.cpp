#include <windows.h>
#include <random>
#include <vector>
#include <string>
#include <format>
#include <functional>
#define WINX 800
#define WINY 600
HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";
LPCTSTR lpszWindowName2 = L"windows program 2";
RECT WinSize{ 0,0,WINX,WINY };
std::wstring bufferStream;
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
	VecSize() {}
	VecSize operator+(VecSize rhs)
	{
		return VecSize(x += rhs.x, y += rhs.y);
	}

	int x;
	int y;
};
class Text
{
public:
	Text() {}
	Text(int sx, int sy, int n, int cnt) : sx(sx), sy(sy), N(n), count(cnt)
	{
		std::wstring temp;
		std::wstring ntemp = std::to_wstring(n);
		for (int i = 0; i < count; i++)
		{
			temp += ntemp;
		}
		temp += L'\n';
		for (int i = 0; i < count; i++)
		{
			wstr += temp;
		}

		_textcolor = RGB(rgb(mt19), rgb(mt19), rgb(mt19));
		_backgroundcolor = RGB(rgb(mt19), rgb(mt19), rgb(mt19));
	}
	void RENDER(HDC hDC)
	{
		SIZE size;
		POINT caretPos;
		std::wstring tems = std::to_wstring(N);
		GetTextExtentPoint32W(hDC, tems.c_str(), tems.size(), &size);
		Drect = RECT{ sx,sy,sx + (size.cx * count) + size.cx,sy + (size.cy * count) + size.cy };
		//HBRUSH BGCOLOR = CreateSolidBrush(_backgroundcolor);
		//FillRect(hDC, &Drect, BGCOLOR);
		//DeleteObject(BGCOLOR);
		SetTextColor(hDC, _textcolor);
		SetBkColor(hDC, _backgroundcolor);
		DrawText(hDC, wstr.c_str(), wstr.size(), &Drect, DT_TOP | DT_CENTER | DT_WORDBREAK);
	}

	int count;
	int N;
	std::wstring wstr;
	int sx;
	int sy;
	RECT Drect;
	COLORREF _textcolor;
	COLORREF _backgroundcolor;
};

Text _text;
int x = 20;
int y = 500;

SIZE _size;

RECT Rsize{ x,y,WINX,WINY };
std::wstring str;
HFONT hFont = CreateFontW(12, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	CLEARTYPE_QUALITY, FF_MODERN, L"Arial"
);

std::vector<std::function<bool(int)>> Funcarray
{
	[](int x)->bool {return 0 <= x && x <= 600; },
	[](int y)->bool {return 0 <= y && y <= 400; },
	[](int n)->bool {return 0 <= n && n <= 200; },
	[](int cnt)->bool {return 5 <= cnt && cnt <= 20; }
};

std::vector<Text> TextVec;

std::vector<int> Decode(std::wstring Buffer)
{
	std::vector<int> empty;
	try
	{
		std::stoi(Buffer);
	}
	catch (std::invalid_argument&)
	{
		return empty;
	}

	std::wstring parsed;
	std::vector<int> pst;

	for (auto& a : Buffer)
	{
		if (a == ' ')
		{
			pst.push_back(stoi(parsed));
			parsed.clear();
			continue;
		}
		else if (&a == &Buffer.back())
		{
			parsed += a;
			pst.push_back(stoi(parsed));
		}
		parsed += a;
	}

	for (int i = 0; i < 4; i++)
	{
		if (Funcarray[i](pst[i]) != true)
		{
			pst.clear();
			return pst;
		}
	}

	return pst;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow)
{
	TextVec.clear();
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
std::vector<int> decode;
bool CHECKA = false;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//GetClientRect(hWnd, &WinSize);

	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 1, 16);
		ShowCaret(hWnd);
		SetCaretPos(x, y);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);

		GetTextExtentPoint32(hDC, bufferStream.c_str(), bufferStream.size(), &_size);
		TextOut(hDC, x, y, bufferStream.c_str(), bufferStream.size());
		if (CHECKA)
		{
			for (auto& a : TextVec)
			{
				a.RENDER(hDC);
			}
		}
		else if (!CHECKA && !TextVec.empty())
		{
			TextVec.back().RENDER(hDC);
		}
		if (!TextVec.empty())
		{
			TextVec.back().RENDER(hDC);
		}
		SetTextColor(hDC, 0);
		SetBkColor(hDC, RGB(255, 255, 255));
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
			if (TextVec.size() == 10)
				break;
			if (bufferStream.empty())
				break;
			decode.clear();
			decode = Decode(bufferStream);
			if (decode.empty())
			{
				bufferStream.clear();
				SetCaretPos(x, y);
				InvalidateRect(hWnd, NULL, true);
				return 0;
			}
			TextVec.push_back(Text(decode[0], decode[1], decode[2], decode[3])); // x y n cnt

			bufferStream.clear();
			SetCaretPos(x, y);

			break;
		case VK_BACK:
			hDC = GetDC(hWnd);
			SIZE size;
			POINT caretPos;
			if (bufferStream.empty())
				break;
			bufferStream.pop_back();
			GetCaretPos(&caretPos);
			GetTextExtentPoint32W(hDC, bufferStream.c_str(), bufferStream.size(), &size);

			SetCaretPos(x + size.cx, caretPos.y);

			ReleaseDC(hWnd, hDC);
			break;
		case VK_ESCAPE:

			HideCaret(hWnd);
			DestroyCaret();
			DestroyWindow(hWnd);
			DeleteObject(hWnd);
			PostQuitMessage(0);
			return 0;
		case 'r':
			TextVec.clear();
			break;
		case 'a':
			if (CHECKA)
			{
				CHECKA = false; break;
			}
			CHECKA = true;
			break;
		case 'q':
			PostQuitMessage(0);
			break;
		default:
		{
			hDC = GetDC(hWnd);
			SIZE size;
			POINT caretPos;
			GetCaretPos(&caretPos);
			GetTextExtentPoint32W(hDC, reinterpret_cast<LPCWSTR>(&wParam), 1, &size);
			bufferStream += wParam;
			SetCaretPos(caretPos.x + size.cx, caretPos.y);

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