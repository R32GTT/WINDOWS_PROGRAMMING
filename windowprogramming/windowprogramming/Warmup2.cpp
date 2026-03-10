#include <iostream>
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
//상으로 출력한다.ㅇ
//• w / a / s / d : 커서 위치를 좌 / 우 / 상 / 하 움직인다.이때 현재 커서 위치의 문자를 빨강색으로 출력한다. ㅇ
//• 엔터키 : 엔터키를 치면 현재 위치의 숫자에 파랑색상으로 선택된 숫자들의 합이 출력된다.만약 파랑 색상 문자가
//없으면 현재 숫자가 그대로 출력된다.다시 엔터를 치면 원래의 숫자 값이 출력된다. SEMI-DONE
//• ↑ / ↓ : 현재 커서가 놓여져 있는 행을 한 칸 위 / 아래의 행과 바꾼다. ㅇ
//• ← / → : 현재 커서가 놓여져 있는 열을 한 칸 좌 / 우의 열과 바꾼다. ㅇ
//• r : 숫자를 랜덤하게 재배치하고 리셋 한다. ㅇ
//• q : 프로그램 종료한다. ㅇ

#define ARR_SIZE 10

std::random_device rd;
std::default_random_engine re(rd());
std::uniform_int_distribution<int> uni(0, 9);


class BaseClass
{
public:
	BaseClass(COORD pos, int num) : _originPos(pos), _originnum(num), _currentnum(num) { _currentPos = _originPos; }
	BaseClass() {};
public:
	COORD _originPos;
	int _originnum;
	int _currentnum;
	int _willnum{ 32767 };
	COORD _currentPos;

};

int SinVel[10]{}; // 0~9 까지 켜짐/꺼짐 확인하는 배열
std::unordered_map<int, BaseClass> NUMMEM;
bool isinited = false;

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

ConsoleColor GetTileColor(COORD pos, COORD pos2, int c)
{
	if (pos.X == pos2.X && pos.Y == pos2.Y)//커서 색 반환
	{
		return ConsoleColor::RED;
	}
	
	if (SinVel[c] == 1)
			return ConsoleColor::BLUE;
	
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



void Render(int arr[][ARR_SIZE], COORD pos)
{
	ConsoleHelper::SetCursorPosition(0, 0);

	int c{};

	for (int y = 0; y < ARR_SIZE; y++)
	{
		for (int x = 0; x < ARR_SIZE; x++)
		{
			c = arr[y][x];
			ConsoleColor color = GetTileColor(COORD(y, x),COORD(pos.Y,pos.X), c);
			ConsoleHelper::SetCursorColor(color);
			
			std::cout << c << ' ';
		}

		std::cout << std::endl;
	}
}

void init(int arr[][ARR_SIZE])
{
	int fullcnt = 0;
	int rnm;
	for (short i = 0; i < ARR_SIZE; i++)
	{
		for (short f = 0; f < ARR_SIZE; f++)
		{
			
			if (isinited == false)
			{
				
				arr[i][f] = rnm = uni(rd);
				NUMMEM.insert(std::make_pair(fullcnt, BaseClass(COORD{ f,i }, rnm)));
				fullcnt++;
			}
			else if (isinited)
			{
				
				arr[i][f] = rnm = uni(rd);
				NUMMEM[fullcnt]._originnum = rnm;
				NUMMEM[fullcnt]._currentnum = rnm;
				fullcnt++;
			}
			
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


bool operator==(COORD rhs, COORD lhs)
{
	return (rhs.X == lhs.X && rhs.Y == lhs.Y);
}

// 필요 없는 코드 - 이미 원본 좌표 있는데 왜씀?
//COORD FindOriginPos(COORD pos) //현 위치에 있는 값의 origin 위치 받고 COORD값 반환
//{
//	/*원본 좌표로 감
//		만약 현 좌표랑 원 좌표랑 같다면
//		본인 위치 반환
//		아니라면
//		재귀함수 ON*/
//	//pos는 처음 시작한 위치
//	//NUMMEM로 원좌표 찾아가는 것임
//	COORD temp = NUMMEM[((pos.Y * 10) + pos.X)]._currentPos;
//	if (temp == NUMMEM[((temp.Y * 10) + temp.X)]._originPos)
//	{
//		return NUMMEM[((temp.Y * 10) + temp.X)]._originPos;
//	}
//	else
//	{
//		return FindOriginPos(temp);
//	}
//
//	
//}

void ChangeValue(int arr[ARR_SIZE][ARR_SIZE], COORD pos)
{
	int cnt{};
	COORD temp = NUMMEM[((pos.Y * 10) + pos.X)]._currentPos;
	for (auto a = 0; a < 9; a++)
	{
		if (SinVel[a])				//괜히 시간만 낭비하는거 같지만,(사실은 맞지만) 이거랑 다르게 구현하려면 저 밑에다가 불린값 설정하는거 하나하나 적어야 하니 일단 이걸로...
			cnt++;
	}
	if (cnt > 0)//하나라도 켜져 있다면
	{
		if (NUMMEM[((temp.Y * 10) + temp.X)]._willnum != NUMMEM[((temp.Y * 10) + temp.X)]._currentnum)
		{
			int sum{};

			for (int base = 0; base < 9; base++)
			{

				for (int f = 0; f < 10; f++)
				{
					for (int e = 0; e < 10; e++)
					{
						if (SinVel[base] && arr[f][e] == base)		// base값이 켜져 있는지 확인하고, ARRAY에서 그 값이 존재할때마다
							sum += base;							// base 값 만큼 SUM에 더함.
						// 비효율적인거 알지만 어떡하나 하나하나 다 체크하는 수밖에 모르는데...

					}
				}
			}
			NUMMEM[((temp.Y * 10) + temp.X)]._currentnum = sum;		// 더한 값들 현재값에 넣어주고
			NUMMEM[((temp.Y * 10) + temp.X)]._willnum = sum;			// 변경된 값으로 바꿔주고
			arr[pos.Y][pos.X] = sum;								// 배열 값도 바꿔줌
		}
		else

		{
			//NUMMEM[((pos.Y * 10) + pos.X)]._currentnum = NUMMEM[((pos.Y * 10) + pos.X)]._originnum; //willnum값은 변치 않을 예정이니 일단 이대로 냅두고...
			//arr[pos.Y][pos.X] = NUMMEM[((pos.Y * 10) + pos.X)]._originnum;							// 배열값 원본으로 복귀
			
			int tempO = NUMMEM[((temp.Y * 10) + temp.X)]._currentnum = NUMMEM[((temp.Y * 10) + temp.X)]._originnum; // 현재값 원본값으로 복귀
			arr[pos.Y][pos.X] = tempO;																				// 똑같이 복귀

		}
	}
	else
	// 꺼져 있더라도 값 복구 해야 하니...
	{
		NUMMEM[((temp.Y * 10) + temp.X)]._currentnum = NUMMEM[((temp.Y * 10) + temp.X)]._originnum;					//똑같은 상황
		arr[pos.Y][pos.X] = NUMMEM[((temp.Y * 10) + temp.X)]._originnum;
	}
	

	


}

void ChangetoUp(int arr[][ARR_SIZE], COORD& pos) // 배열 위 또는 아래 위치 변경
{
	if (pos.Y == 0)
	{
		for (auto i = 0; i < ARR_SIZE; i++)
		{
			std::swap(arr[pos.Y][i], arr[9][i]);
			std::swap(NUMMEM[((pos.Y * 10) + i)]._currentPos.Y, NUMMEM[(9*10) + i]._currentPos.Y);
			pos.Y = 9;
		}
		return;
	}
	for (auto i = 0; i < ARR_SIZE; i++)
	{
		std::swap(arr[pos.Y][i], arr[pos.Y - 1][i]);
		std::swap(NUMMEM[((pos.Y * 10) + i)]._currentPos.Y, NUMMEM[(((pos.Y - 1) * 10) + i)]._currentPos.Y);
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
			std::swap(NUMMEM[((pos.Y * 10) + i)]._currentPos.Y, NUMMEM[0 + i]._currentPos.Y);
			pos.Y = 0;
			
		}
		return;
	}
	for (auto i = 0; i < ARR_SIZE; i++)
	{
		std::swap(arr[pos.Y][i], arr[pos.Y + 1][i]);
		std::swap(NUMMEM[((pos.Y * 10) + i)]._currentPos.Y, NUMMEM[(((pos.Y + 1) * 10) + i)]._currentPos.Y);
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
		std::swap(NUMMEM[((i * 9) + pos.X)]._currentPos.X, NUMMEM[((i * 9) + pos.X - 1)]._currentPos.X);
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
		std::swap(NUMMEM[((i * 9) + pos.X)]._currentPos.X, NUMMEM[((i * 9) + pos.X + 1)]._currentPos.X);
	}
	pos.X += 1;
}




int main()
{
	int BArr[ARR_SIZE][ARR_SIZE];
	init(BArr);
	isinited = true;
	
	COORD curPos{ uni(rd),uni(rd) };


	while (true)
	{
		Render(BArr,curPos);
		ConsoleHelper::SetCursorPosition(2*curPos.X,curPos.Y);

		Sleep(100);												// 키보드 레이턴시 문제
																//1khz 일때 이정도여야 정상 작동함 더 안좋은 키보드거나 더 좋은 키보드라면 줄이거나 늘릴수 있을듯.
		while (_kbhit()==0)										// 키보드 안누르고 있을때
		{														// 한번 눌러도 키보드 반응이 늦어서 지속으로 입력되는 버그 발생

		}
		_getch();												// 한번 누르고 나서 버퍼를 비워줌? 아마도
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
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			//현재값 저장
			//값 합계 계산
			//출력
			ChangeValue(BArr, curPos);
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
		else if (GetAsyncKeyState(0x52) & 0x8000)	// R 
		{
			init(BArr);								// 배열 내부값 재생성
		}
		else if (GetAsyncKeyState(0x51) & 0x8000)	// Q 입력받으면
		{
			return 0;								// 프로그램 종료
		}
		else if (GetAsyncKeyState((int)NUM::ON) & 0x8000) // 1
		{
			if (SinVel[1] == 1)
			{
				SinVel[1] = 0;
				continue;
			}
			SinVel[1] = 1;

		}
		else if (GetAsyncKeyState((int)NUM::TW) & 0x8000) // 2
		{
			if (SinVel[2] == 1)
			{
				SinVel[2] = 0;
				continue;
			}
			SinVel[2] = 1;
		}
		else if (GetAsyncKeyState((int)NUM::TH) & 0x8000) // 3
		{
			if (SinVel[3] == 1)
			{
				SinVel[3] = 0;
				continue;
			}
			SinVel[3] = 1;
		}
		else if (GetAsyncKeyState((int)NUM::FO) & 0x8000) // 4
		{
			if (SinVel[4] == 1)
			{
				SinVel[4] = 0;
				continue;
			}
			SinVel[4] = 1;
		}
		else if (GetAsyncKeyState((int)NUM::FI) & 0x8000) // 5
		{
			if (SinVel[5] == 1)
			{
				SinVel[5] = 0;
				continue;
			}
			SinVel[5] = 1;
		}
		else if (GetAsyncKeyState((int)NUM::SX) & 0x8000) // 6
		{
			if (SinVel[6] == 1)
			{
				SinVel[6] = 0;
				continue;
			}
			SinVel[6] = 1;
		}
		else if (GetAsyncKeyState((int)NUM::SV) & 0x8000) // 7
		{
			if (SinVel[7] == 1)
			{
				SinVel[7] = 0;
				continue;
			}
			SinVel[7] = 1;
		}
		else if (GetAsyncKeyState((int)NUM::EI) & 0x8000) // 8
		{
			if (SinVel[8] == 1)
			{
				SinVel[8] = 0;
				continue;
			}
			SinVel[8] = 1;

		}
		else if (GetAsyncKeyState((int)NUM::NI) & 0x8000) // 9
		{
			if (SinVel[9] == 1)
			{
				SinVel[9] = 0;
				continue;
			}
			SinVel[9] = 1;
		}
		else if (GetAsyncKeyState((int)NUM::ZE) & 0x8000) // 0
		{
			if (SinVel[0] == 1)
			{
				SinVel[0] = 0;
				continue;
			}
			SinVel[0] = 1;
		}
	}
		

}