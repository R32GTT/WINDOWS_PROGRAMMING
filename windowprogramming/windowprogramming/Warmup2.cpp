#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <unordered_map>
#include <Windows.h>

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
	int x;
	int y;
};

SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attribute_color)

int MainVec[ARR_SIZE][ARR_SIZE];

int main()
{

}