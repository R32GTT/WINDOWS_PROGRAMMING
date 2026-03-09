#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <unordered_map>
#include <Windows.h>

#define ARR_SIZE 20
#define MAX_ITEM 10


std::random_device rd;
std::default_random_engine re(rd());
std::uniform_int_distribution<int> uni(0,20);




class Player
{
public:
	Player(COORD pos, int icnt) : _pos(pos), _itemcount(icnt) {}

public:
	COORD _pos;
	int _itemcount;

};

int Board[ARR_SIZE][ARR_SIZE]{};

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
}

bool CheckForCoord() // 아이템 생성할때 쓸 것. 현 위치에 아이템 생성 가능한지 확인함.
{

}

COORD CheckForSpawn(int arr[][ARR_SIZE], int oid) // 장애물 생성할 때 쓸 것. 위치 반납할 예정
{
	int x = uni(rd);
	int y = uni(rd);
	bool isblocked = false;
	switch (oid)
	{
	case 0: // 3*4 사이즈
		do
		{
			for (int i = 0; i < 4; i++)
			{
				for (int f = 0; f < 3; f++)
				{
					if (arr[y+i][x+f] != 0)
					{
						isblocked = true;
					}
				}
			}
			x = uni(rd);	//막혀있으면 다시 생성
			y = uni(rd);
		}
		while (isblocked);
		COORD startpos(x, y);	//안막혔으면 시작위치 반환
		return startpos;
		break;
	case 1: // 5*2 사이즈
		do
		{
			for (int i = 0; i < 2; i++)
			{
				for (int f = 0; f < 5; f++)
				{
					if (arr[y + i][x + f] != 0)
					{
						isblocked = true;
					}
				}
			}
			x = uni(rd);	//막혀있으면 다시 생성
			y = uni(rd);
		} while (isblocked);
		COORD startpos(x, y);	//안막혔으면 시작위치 반환
		return startpos;
		break;
	case 2: // 4*4 사이즈
		do
		{
			for (int i = 0; i < 4; i++)
			{
				for (int f = 0; f < 3; f++)
				{
					if (arr[y + i][x + f] != 0)
					{
						isblocked = true;
					}
				}
			}
			x = uni(rd);	//막혀있으면 다시 생성
			y = uni(rd);
		} while (isblocked);
		COORD startpos(x, y);	//안막혔으면 시작위치 반환
		return startpos;
		break;
	}
}

void SpawnObstacle(int arr[][ARR_SIZE])
{
	int obstacleid = 0;
	
	switch (obstacleid)
	{
	case 0:
		CheckForSpawn(arr, obstacleid);

		break;
	case 1:

		break;
	case 2:

		break;
	default:
		break;
	}

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




int main()
{


}