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
const int bSize = 40;

std::random_device rd;
std::mt19937 mt19(rd());
std::uniform_int_distribution RanXY(0, bSize - 1);
std::uniform_int_distribution RandTT(TileType::TT_EMPTY, TileType::TT_SIZE3);
std::uniform_int_distribution RandShape(PShape::P_TRI, PShape::P_ELI);

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
	VecSize operator=(VecSize rhs)
	{
		return VecSize(rhs.x, rhs.y);
	}
	bool operator==(VecSize rhs)
	{
		return(x == rhs.x && y == rhs.y);
	}

	int x;
	int y;
};

enum class PShape
{
	P_TRI,
	P_REC,
	P_CIR,
	P_ELI
};

enum class TileType
{
	TT_EMPTY = 0,
	TT_P1 = 1,
	TT_P2 = 2,
	TT_OBSTACLE = 3,
	TT_mSIZE1 = 4,
	TT_mSIZE2 = 5,
	TT_mSIZE3 = 6,
	TT_SIZE1 = 7,
	TT_SIZE2 = 8,
	TT_SIZE3 = 9,
	TT_GOAL = 10 
};

VecSize P1start{ 0,0 };
VecSize P2start{ (bSize - 1),0 };

class Player
{
public:

	Player()
	{
		cShape = RandShape(mt19);
		size = 0;
		sChanged = false;
		SinceChanged = 0;
		cColor;
	}


	bool sChanged;
	short size;
	short SinceChanged;
	short cColor;
	PShape cShape;
	VecSize pos;
};

class Goal
{
public:
	short size;
	VecSize pos;
};

class GameBoard
{
public:

	void init()
	{
		for (int y = 0; y < bSize; y++)
		{
			for (int x = 0; x < bSize; x++)
			{
				board[y][x] = TileType::TT_EMPTY;
			}
		}

		p1.pos = P1start;
		p2.pos = P2start;

		board[p1.pos.y][p1.pos.x] = TileType::TT_P1;
		board[p2.pos.y][p2.pos.x] = TileType::TT_P2;

		while (tCount != 0)
		{
			int x;
			int y;
			do
			{
				x = RanXY(mt19);
				y = RanXY(mt19);
			} while (CheckColi(VecSize(x, y)));


			tCount--;
		}
		
	}

	bool CheckColi(VecSize pos)
	{
		if (board[pos.y][pos.x] != TileType::TT_EMPTY)
			return true;
		else
			return false;
	}

	TileType board[bSize][bSize];
	bool inited = false;
	int tCount = 20;
	Goal goal;
	Player p1;
	Player p2;
};



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



	AdjustWindowRect(&WinSize, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(lpszClass, lpszWindowName2, WS_OVERLAPPEDWINDOW | WS_SIZEBOX, 100, 50, WinSize.right - WinSize.left, WinSize.bottom - WinSize.top, NULL, (HMENU)NULL, hinstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);

		

		SetTextColor(hDC, 0);
		SetBkColor(hDC, RGB(255, 255, 255));
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CHAR:

		HDC hDC;
		POINT caretPos;

		switch (wParam)
		{
		}
		break;
	case WM_DESTROY:
		DestroyWindow(hWnd);
		DeleteObject(hWnd);
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}