#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <unordered_map>
/*
3개의 영화관을 가지고 있는 멀티플렉스의 좌석 예약 시스템을 구현해본다.각 영화관의 좌석은 10x10 좌석을 가지
고 있다.이때 2차원 배열과 구조체를 사용한다.
• 3개의 영화관 정보를 저장하고 사용한다.이때 3개의 영화관은 배열을 사용해도 괜찮다.
• 3개 영화관에 대한 영화 제목과 상영 시간을 미리 저장해 둔다.
• 영화 제목은 영문자 문자열로 정한다.
• 상영 시간은 한 영화관에 대하여 3개의 상영시간을 정한다.시간 포맷은 본인이 결정한다.
• 각각의 영화관 정보는 :
• 영화관 번호 : 숫자(1~3) ㅇ
• 영화 제목 : 문자열(10자 이내의 문자열) ㅇ
• 상영 시간 : 문자열 또는 숫자(예, 1100 1400 1700) ㅇ
• 좌석 상태 : 공석 또는 예약 번호를 저장(10x10 크기의 좌석) ㅇ
• 다음의 명령어를 실행한다.
• d : 3개 영화관의 정보를 출력한다. (영화관 번호, 영화 제목, 상영시간) 완
• p x : x번 영화관의 모든 상영 시간에 대한 좌석 상태를 출력한다.이때, 영화 제목도 같이 출력한다. 완
• “p 영화제목” 명령어도 가능하게 구현한다. 완
• 빈 좌석과 예약된 좌석을 구분해서 출력한다. 완
• 예약된 좌석에는 예약번호를 출력한다. 완
• r : 영화를 예약한다. 완
• 영화관 번호 또는 제목을 묻고, 상영 시간과 좌석(m, n)을 묻고 해당 좌석을 예약한다. ㅇ
• 예약을 하면 해당 좌석에 예약 번호(2자리 숫자)를 배당한다. ㅇ
• 예약 후, 예약 내용을 출력한다.출력 포맷은 다음 페이지의 예를 참고한다. ㅇ
• c : 예약을 취소한다. 완
• 예약 번호를 확인하고 해당 좌석을 취소한다.취소 후 취소한 예약 정보를 출력한다.출력 포맷은 다음 페이지의 예를 참고한다. ㅇ
• h : 모든 영화관의 모든 상영 시간의 예약된 좌석의 비율을 출력한다. 완
• q : 프로그램 종료'
*/

using Matrix = std::vector<std::vector<int>>;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(1, 99);

class ResTable;

std::unordered_map<int, ResTable> Resmap;


class Cinema
{
public:
	Cinema(int id, std::string name, std::vector<std::string>time) : _cinemaId(id), _movieName(name), _screenTime(time) 
	{
		if (name.size() > 10) { return; } 
		_seatL.push_back(Matrix{});
		_seatL.push_back(Matrix{});
		_seatL.push_back(Matrix{});
		initMatrix(_seatL);
	}
	
	void initMatrix(std::vector<Matrix>& st)
	{
		for (auto& a : st)
		{
			for (int i = 0; i < 10; i++)
			{
				a.push_back(std::vector<int> {});
				for (int f = 0; f < 10; f++)
				{
					a[i].push_back(0);
				}
			}
		}
	}


public:
	int _cinemaId;
	std::string _movieName;
	std::vector<std::string> _screenTime;
	std::vector<Matrix> _seatL;
};

class ResTable
{
public:
	ResTable(int rid,int rtm,int rsx,int rsy,int rsn) :_rmovid(rid), _rtime(rtm), _rsx(rsx), _rsy(rsy), _resnum(rsn) {}
public:
	int _rmovid;
	int _rtime;
	int _rsx;
	int _rsy;
	int _resnum;
};

void PrintCneinfo(std::vector<Cinema>& abs) //영화관의 정보를 출력한다. (영화관 번호, 영화 제목, 상영시간)
{
	for (auto& a : abs)
	{
		std::cout << a._cinemaId << ' ' << a._movieName << ' ';
		for (auto& b : a._screenTime)
			std::cout << b << ' ' ;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void PrintCineStInfo(std::vector<Cinema>& abs, int id) // x번 영화관의 모든 상영 시간에 대한 좌석 상태를 출력
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << abs[id - 1]._movieName << ' ' << abs[id - 1]._screenTime[i] << ':' << std::endl;
		auto& a = abs[id - 1]._seatL;
		for (int f = 0; f < 10; f++)
		{
			std::cout << "\t";
			for (int c = 0; c < 10; c++)
			{
				if (a[i][f][c] == 0)
				{
					std::cout << "-- ";
				}
				else
					std::cout << a[i][f][c] << ' ';
			}
			std::cout << std::endl;
		}
		
	}
}

int FindCineByMN(std::vector<Cinema>& abs, std::string str) // 영화 이름으로 상영관 찾기
{
	for (auto& a : abs)
		if (a._movieName == str)
			return a._cinemaId;			//찾으면 영화관ID 리턴

	return 0;							//못찾았으면 0 리턴
}

int FindTime(std::vector<Cinema>& abs, std::string str,int id) // 영화 시간 찾기
{
	
	for (int i = 0; i < 3; i++)
	{
		if (abs[id-1]._screenTime[i] == str)
			return i;											// 맞는 인덱스값 반환
	}
	return 4;													// 없으면 4 반환
}

bool IsNumberST(const std::string& s) // 순수 숫자로만 이루어져 있다면 T 아니면 F
{
	if(!s.empty())
	{
		for (auto& ch : s) {
			if (!isdigit(ch)) {
				
				return false;
			}
		}

		return true;
	}
}

bool CheckResnum(int rn) //예약한 번호가 이미 있는지
{
	if (Resmap.find(rn) != Resmap.end()) // 원소가 있다면
		return true;
	else
		return false;
}

std::string GetMovieNameById(std::vector<Cinema>& abs, int cid) // id로 영화 이름 알아내기
{
	if (cid < 4 && cid>0)
	{
		for (auto& a : abs)
		{
			if (a._cinemaId == cid)
				return a._movieName;
		}
	}
	else
	{
		std::cout << "What have you done....";
	}
}

void ReserveSt(std::vector<Cinema>& abs, int cid, int stime, std::pair<int, int> stxy, int resnum) // 좌석 예약
{
	abs[cid - 1]._seatL[stime][stxy.second-1][stxy.first-1] = resnum;
}

void CancelSt(std::vector<Cinema>& abs, int cid, int stime, std::pair<int, int> stxy) // 좌석 취소
{
	abs[cid - 1]._seatL[stime][stxy.second-1][stxy.first-1] = 0;
}

enum class AllErrors
{
INVALID_ID,
INVALID_NAME,
INVALID_TIME,
INVALID_COORDS,
INVALID_RNUM,
};

bool CheckForErrors(std::string in,AllErrors err,std::vector<Cinema> abs)
{
	int cid;
	if (err == AllErrors::INVALID_ID)
	{
		int id = std::stol(in);
		if (id > 3 || id < 1)
			std::cout << "Invalid number! Please use value between 1~3!" << std::endl;
	}
	else if (err == AllErrors::INVALID_NAME)
	{
		cid = FindCineByMN(abs, in);
		if(cid == 0);
			std::cout << "Invalid movie name! Please Check for any typos!" << std::endl;
	
	}
	else if (err == AllErrors::INVALID_TIME)
	{
		int stime;
		if (IsNumberST(in)) // 숫자 확인
		{
			stime = FindTime(abs, in, cid);	//시간 인덱스값
			if (stime == 4)						//잘못된 값이면
			{
				std::cout << "Invaild Time!" << std::endl;
			}
		}
		else if (!IsNumberST(in))				//숫자가 아니라면
			std::cout << "Invaild Input! Please only enter Time in numeric!" << std::endl;
	}
	else if (err == AllErrors::INVALID_COORDS)
	{

	}
	else if (err == AllErrors::INVALID_RNUM)
	{

	}
}

void Reserve(std::vector<Cinema>& abs) // 영화 예약
{
	std::string in2;

	int cid{};	//영화관(영화)
	int stime{};	//시간
	int stx;	//좌석x
	int sty;	//좌석y
	int resnum;	//예약번호

	std::cout << "Which Movie?(Movie name OR Cinema number) : ";
	do
	{
		std::getline(std::cin, in2);
	}
	while (CheckForErrors(in2, AllErrors::INVALID_ID, abs) || CheckForErrors(in2, AllErrors::INVALID_NAME, abs));
		
	if (IsNumberST(in2))					// 숫자(영화관)
			cid = std::stol(in2);
	else if (!IsNumberST(in2))				// 영화 이름
		cid = FindCineByMN(abs, in2);		// 이름으로 번호 찾기

	std::cout << "What Time? : ";
	do
	{
		std::getline(std::cin, in2);
	} while (CheckForErrors(in2, AllErrors::INVALID_TIME, abs));
	stime = FindTime(abs, in2, cid);	//시간 인덱스값
		
	
	while (true)
	{
		std::cout << "Seat you want : ";
		std::cin >> stx >> sty;
		if (!(isdigit(stx) || isdigit(sty)) || ((stx > 10) || (stx < 1) || (sty > 10) || (sty < 1))) break;
		std::cout << "Invaild Input! Please only enter coords in numeric and in range of 1~10!" << std::endl;
	}

	do
	{
		resnum = dis(rd);
			
	} while (CheckResnum(resnum));
	Resmap.emplace(std::make_pair(resnum, ResTable(cid, stime, stx, sty, resnum)));

	ReserveSt(abs, cid, stime, std::make_pair(stx, sty), resnum);
	
	std::cout << "Reservation:" << "\n" << "\t" << "Movie name: " << GetMovieNameById(abs, cid)
		<< "\n" << "\t" << "Time: " << abs[cid - 1]._screenTime[stime]
		<< "\n" << "\t" << "Seat number: " << '(' << stx << ", " << sty << ')'
		<< "\n" << "\t" << "Your reservation number is " << resnum << ". Thank you for your reservation!" << std::endl;

		


	
}

void Cancel(std::vector<Cinema>& abs)
{
	int in2;
	std::cout << "Enter the reservation number : ";
	std::cin >> in2;

	if(Resmap.contains(in2));
	int id = (Resmap.find(in2))->second._rmovid;
	int stime = (Resmap.find(in2))->second._rtime;
	int stx = (Resmap.find(in2))->second._rsx;
	int sty = (Resmap.find(in2))->second._rsy;

	
	std::cout << "Your reservation information is: " 
		<< "\n" << "\t" << "Movie name: " << GetMovieNameById(abs,id)
		<< "\n" << "\t" << "Time: " << abs[id - 1]._screenTime[stime]
		<< "\n" << "\t" << "Seat number: " << '(' << stx << ", " << sty << ')'
		<< "\n" << "\t" << "Reservation is cancelled. Please, come again!" << std::endl;
	Resmap.erase(in2);
	CancelSt(abs, id, stime, std::make_pair(stx, sty));
}


void ResPerc(std::vector<Cinema>& abs) // 모든 영화관의 예약률 확인 및 출력
{
	int cnt = 0;
	for (auto& a : abs)
	{
		std::cout << a._cinemaId << ' ' << a._movieName << ' ';
		int tcnt = 0;
		int wcnt = 0;

		for (auto& b : a._screenTime)
		{
			wcnt = 0;
			std::cout << b << ' ';
			for (int f = 0; f < 10; f++)
			{
				for (int g = 0; g < 10; g++)
				{
					if (a._seatL[tcnt][f][g] != 0)
						wcnt += 1;
				}
			}
			tcnt++;
			std::cout << (wcnt*100)/100 << '%' << ' ';
		}
			std::cout << std::endl;
	}
	std::cout << std::endl;

}



int main()
{
	
	std::vector<Cinema> absoluteCinema;
	std::vector<std::string> timetable1{ "1100","1400","1700" };
	std::vector<std::string> timetable2{ "1300","1500","1700" };
	std::vector<std::string> timetable3{ "1000","1200","1400" };

	absoluteCinema.push_back(Cinema(1,"Hathaway",timetable1));
	absoluteCinema.push_back(Cinema(2,"F1",timetable2));
	absoluteCinema.push_back(Cinema(3, "John Wick", timetable3));

	

	PrintCneinfo(absoluteCinema);
	std::string in1;


	

	/*Reserve(absoluteCinema);

	PrintCineStInfo(absoluteCinema, 2);

	Cancel(absoluteCinema);

	PrintCineStInfo(absoluteCinema, 2);*/

	//ResPerc(absoluteCinema);

	while (true)
	{
		std::cout << "Command : "; std::getline(std::cin, in1); 

		if (in1.size() == 1)
		{

			if(in1[0] == 'd')
			{

			}
			else if (in1[0] == 'r')
			{

			}
			else if (in1[0] == 'c')
			{

			}
			else if (in1[0] == 'h')
			{
			}
			else if ((in1[0] == 'q'))
			{
				return;
			}

		}
		
		else // 2칸 이상이면 
		{
			if (in1[0] == 'p')
			{

			}
		}
	}



}
