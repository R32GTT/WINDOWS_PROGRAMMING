#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <Windows.h>
#include <conio.h>
#include <WinUser.h>
#include <memory>
#include "Board.h"
#include "Object.h"
#include "Coord.h"


#define ARR_SIZE 20
#define MAX_ITEM 10







enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

class ConsoleHelper
{
public:
	static void SetCursorPosition(int x, int y);
	static void SetCursorColor(ConsoleColor color);
};

ConsoleColor GetTileColor(COORD pos, COORD pos2, int c)
{
	if (pos.X == pos2.X && pos.Y == pos2.Y)//커서 색 반환
	{
		return ConsoleColor::RED;
	}

	return ConsoleColor::WHITE;

}

void ConsoleHelper::SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<short>(color));
}


bool CheckForColision()
{

	return false;
}

bool CheckForCoord() // 아이템 생성할때 쓸 것. 현 위치에 아이템 생성 가능한지 확인함.
{
	return false;
}





void Render(int arr[][ARR_SIZE])
{

	for (int i = 0; i < ARR_SIZE; i++)
	{
		for (int f = 0; f < ARR_SIZE; f++)
		{

		}
	}


}

void Binit(int arr[][ARR_SIZE])
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		for (int f = 0; f < ARR_SIZE; f++)
		{

		}
	}
	for (int i = 0; i < ARR_SIZE; i++)
	{
		for (int f = 0; f < ARR_SIZE; f++)
		{

		}
	}
	for (int i = 0; i < ARR_SIZE; i++)
	{
		for (int f = 0; f < ARR_SIZE; f++)
		{

		}
	}
}


enum class MOVIN
{
	W = 0x57,
	A = 0x41,
	S = 0x53,
	D = 0x44,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C

};

int main()
{
	Board mainBoard;
	mainBoard.Init();

	mainBoard.SpawnObject();

	mainBoard.SpawnItem();

	mainBoard.SpawnPlayer();
	
	//mainBoard.Render();


	while (true)
	{
		mainBoard.Render();
			mainBoard.PrintPlayerPoints();
			if (mainBoard.HasEnded())
			{
				mainBoard.CheckForWinner();
				return 0;
			}


		Sleep(100);												// 키보드 레이턴시 문제
		//1khz 일때 이정도여야 정상 작동함 더 안좋은 키보드거나 더 좋은 키보드라면 줄이거나 늘릴수 있을듯.
		while (_kbhit() == 0)										// 키보드 안누르고 있을때
		{														// 한번 눌러도 키보드 반응이 늦어서 지속으로 입력되는 버그 발생

		}
		_getch();												// 한번 누르고 나서 버퍼를 비워줌? 아마도
		if (GetAsyncKeyState((int)MOVIN::W) & 0x8000) // 커서 이동 시리즈
		{
			mainBoard.P1Up();
		}
		else if (GetAsyncKeyState((int)MOVIN::A) & 0x8000)
		{
			mainBoard.P1left();
		}
		else if (GetAsyncKeyState((int)MOVIN::S) & 0x8000)
		{
			mainBoard.P1Down();
		}
		else if (GetAsyncKeyState((int)MOVIN::D) & 0x8000)
		{
			mainBoard.P1RIght();
		}
		else if (GetAsyncKeyState((int)MOVIN::I) & 0x8000)
		{
			mainBoard.P2Up();
		}
		else if (GetAsyncKeyState((int)MOVIN::J) & 0x8000)
		{
			mainBoard.P2left();
		}
		else if (GetAsyncKeyState((int)MOVIN::K) & 0x8000)
		{
			mainBoard.P2Down();
		}
		else if (GetAsyncKeyState((int)MOVIN::L) & 0x8000)
		{
			mainBoard.P2RIght();
		}
		else if (GetAsyncKeyState(0x52) & 0x8000)	// R 
		{
			mainBoard.Init();

			mainBoard.SpawnObject();

			mainBoard.SpawnItem();

			mainBoard.SpawnPlayer();							// 배열 내부값 재생성
		}
		else if (GetAsyncKeyState(0x51) & 0x8000)	// Q 입력받으면
		{
			mainBoard.CheckForWinner();
			return 0;								// 프로그램 종료
		}


	}


}