#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <unordered_map>
#include <Windows.h>
#include <WinUser.h>
#include <conio.h>

//숫자 0 ~9 (10개의 숫자)를 10세트 만들어 10x10의 보드판의 각 줄에 한 세트의 숫자를 랜덤한 위
//치에 넣는다.
//• 2차원 배열을 사용한다.
//• 시작 위치(커서)를 보드 칸에서 랜덤한 위치에 설정한다.
//• 시작 위치의 숫자는 빨강색으로 출력한다.
//• 다음의 명령어를 실행한다.
//• 0~9: 0부터 9 사이의 숫자를 입력하면 입력한 숫자를 배열에서 찾아 파랑 색상으로 출력한다.다시 누르면 원래 색
//상으로 출력한다.
//• w / a / s / d : 커서 위치를 좌 / 우 / 상 / 하 움직인다.이때 현재 커서 위치의 문자를 빨강색으로 출력한다.
//• 엔터키 : 엔터키를 치면 현재 위치의 숫자에 파랑색상으로 선택된 숫자들의 합이 출력된다.만약 파랑 색상 문자가
//없으면 현재 숫자가 그대로 출력된다.다시 엔터를 치면 원래의 숫자 값이 출력된다.
//• ↑ / ↓ : 현재 커서가 놓여져 있는 행을 한 칸 위 / 아래의 행과 바꾼다.
//• ← / → : 현재 커서가 놓여져 있는 열을 한 칸 좌 / 우의 열과 바꾼다.
//• r : 숫자를 랜덤하게 재배치하고 리셋 한다.
//• q : 프로그램 종료한다.

#define ARR_SIZE 10

std::random_device rd;
std::default_random_engine re(rd());
std::uniform_int_distribution<int> uni(0, 9);

class BaseClass
{
public:
	BaseClass(COORD pos) : _cursorPos(pos) {}
public:
	COORD _cursorPos;
	int _currentnum;
};



enum class DIR_KB
{
	RIGHT,
	DOWN,
	LEFT,
	UP
};

class Cursorpos
{
public:
	COORD pos;

};

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};


int MainVec[ARR_SIZE][ARR_SIZE];

class ConsoleHelper
{
public:
	static void SetCursorPosition(int x, int y);
	static void SetCursorColor(ConsoleColor color);
};

ConsoleColor GetTileColor(COORD pos)
{
	return ConsoleColor::WHITE;
}

void ConsoleHelper::SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<short>(color));
}

void ConsoleHelper::SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}



void Render(int arr[][ARR_SIZE])
{
	ConsoleHelper::SetCursorPosition(0, 0);

	int c;

	for (int y = 0; y < ARR_SIZE; y++)
	{
		for (int x = 0; x < ARR_SIZE; x++)
		{
			ConsoleColor color = GetTileColor(COORD(y, x));
			ConsoleHelper::SetCursorColor(color);
			c = arr[y][x];
			std::cout << c << ' ';
		}

		std::cout << std::endl;
	}
}

void init(int arr[][ARR_SIZE])
{
	for (auto i = 0; i < ARR_SIZE; i++)
	{
		for (auto f = 0; f < ARR_SIZE; f++)
		{
			arr[i][f] = uni(rd);
		}
	}
}

enum class MOVIN
{
	W = 0x57,
	A = 0x41,
	S = 0x53,
	D = 0x44

};
enum class NUM
{
	ZE = 0x30,
	ON = 0x31,
	TW = 0x32,
	TH = 0x33,
	FO = 0x34,
	FI = 0x35,
	SX = 0x36,
	SV = 0x37,
	EI = 0x38,
	NI = 0x39,
};

int SinVel[9]{}; // 0~9 까지 켜짐/꺼짐 확인하는 배열
bool;



void ChangeValue(int arr[][ARR_SIZE], COORD pos)
{

}

void ChangetoUp(int arr[][ARR_SIZE], COORD& pos) // 배열 위 또는 아래 위치 변경
{
	if (pos.Y == 0)
	{
		for (auto i = 0; i < ARR_SIZE; i++)
		{
			std::swap(arr[pos.Y][i], arr[9][i]);
			pos.Y = 9;
		}
		return;
	}
	for (auto i = 0; i < ARR_SIZE; i++)
	{
		std::swap(arr[pos.Y][i], arr[pos.Y - 1][i]);
	}
	pos.Y -= 1;
}
void ChangetoDown(int arr[ARR_SIZE][ARR_SIZE], COORD& pos) // 배열 위 또는 아래 위치 변경
{
	if (pos.Y == 9)
	{
		for (auto i = 0; i < ARR_SIZE; i++)
		{
			std::swap(arr[pos.Y][i], arr[0][i]);
			pos.Y = 0;
			
		}
		return;
	}
	for (auto i = 0; i < ARR_SIZE; i++)
	{
		std::swap(arr[pos.Y][i], arr[pos.Y + 1][i]);
	}
	pos.Y += 1;
}

void ChangetoLeft(int arr[][ARR_SIZE], COORD& pos) // 배열 양 옆 위치 변경 (ㅁ <-> ㅇ) -> (ㅇ ㅁ)
{
	if (pos.X == 0)
		return;
	for (auto i = 0; i < ARR_SIZE; i++)
	{
		std::swap(arr[i][pos.X], arr[i][pos.X - 1]);
	}
	pos.X -= 1;
}
void ChangetoRight(int arr[][ARR_SIZE], COORD& pos) // 배열 양 옆 위치 변경 (ㅁ <-> ㅇ) -> (ㅇ ㅁ)
{
	if (pos.X == 9)
		return;
	for (auto i = 0; i < ARR_SIZE; i++)
	{
		std::swap(arr[i][pos.X], arr[i][pos.X + 1]);
	}
	pos.X += 1;
}

int main()
{
	int BArr[ARR_SIZE][ARR_SIZE];
	init(BArr);
	
	COORD curPos{ uni(rd),uni(rd) };

	int cnt = 0;
	while (true)
	{
		Render(BArr);
		ConsoleHelper::SetCursorPosition(2*curPos.X,curPos.Y);

		Sleep(100); // 키보드 레이턴시 문제
					//1khz 일때 이정도여야 정상 작동함 더 안좋은 키보드거나 더 좋은 키보드라면 줄이거나 늘릴수 있을듯.
		while (_kbhit()==0)
		{

		}
		_getch();
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			//y축 기반 연산
			ChangetoLeft(BArr, curPos);
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			//y축 기반 연산 
			ChangetoRight(BArr, curPos);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			//x축 기반 연산
			ChangetoUp(BArr, curPos);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			//x축 기반 연산
			ChangetoDown(BArr, curPos);
			cnt++;
			
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			//현재값 저장
			//값 합계 계산
			//출력
		}
		else if (GetAsyncKeyState((int)MOVIN::W) & 0x8000) // 커서 이동 시리즈
		{
			if (curPos.Y == 0)
				continue;
			ConsoleHelper::SetCursorPosition(2 * curPos.X, curPos.Y-=1);
		}
		else if (GetAsyncKeyState((int)MOVIN::A) & 0x8000)
		{
			if (curPos.X == 0)
				continue;
			ConsoleHelper::SetCursorPosition(2 * (curPos.X -= 1), curPos.Y);
		}
		else if (GetAsyncKeyState((int)MOVIN::S) & 0x8000)
		{
			if (curPos.Y == 9)
				continue;
			ConsoleHelper::SetCursorPosition(2 * curPos.X, curPos.Y += 1);
		}
		else if (GetAsyncKeyState((int)MOVIN::D) & 0x8000)
		{
			if (curPos.X == 9)
				continue;
			ConsoleHelper::SetCursorPosition(2 * (curPos.X += 1), curPos.Y);
		}
		else if (GetAsyncKeyState(0x52) & 0x8000) // R
		{
			init(BArr);
		}
		else if (GetAsyncKeyState(0x51) & 0x8000) // Q 입력받으면
		{
			return 0;
		}
		else if (GetAsyncKeyState((int)NUM::ON) & 0x8000) // 1
		{

		}
		else if (GetAsyncKeyState((int)NUM::TW) & 0x8000) // 2
		{

		}
		else if (GetAsyncKeyState((int)NUM::TH) & 0x8000) // 3
		{

		}
		else if (GetAsyncKeyState((int)NUM::FO) & 0x8000) // 4
		{

		}
		else if (GetAsyncKeyState((int)NUM::FI) & 0x8000) // 5
		{

		}
		else if (GetAsyncKeyState((int)NUM::SX) & 0x8000) // 6
		{

		}
		else if (GetAsyncKeyState((int)NUM::SV) & 0x8000) // 7
		{

		}
		else if (GetAsyncKeyState((int)NUM::EI) & 0x8000) // 8
		{

		}
		else if (GetAsyncKeyState((int)NUM::NI) & 0x8000) // 9
		{

		}
		else if (GetAsyncKeyState((int)NUM::ZE) & 0x8000) // 0
		{

		}
	}
		

}