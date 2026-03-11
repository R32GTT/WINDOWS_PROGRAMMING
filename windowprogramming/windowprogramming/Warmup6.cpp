#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <queue>
#include <cctype>
#include <algorithm>


class Word
{
public:
	Word(std::string wrd, int spc, bool hs) : _word(wrd), _spCount(spc), _hasSpace(hs), _wdCount(0) { InitWdCount(); }
	~Word() {}

	int GetSpCount() { return _spCount; }
	void SetSpCount(int set) { _spCount = set; }
	void ReduceSpCount() { if (_spCount > 0) _spCount--; } // 공백이 1개 이상이면 1개씩 줄인다
	void IncreaseSpCount() { if (_spCount < 5) _spCount++; } // 공백이 4개 이하면 1개씩 늘린다
	int GetWholewdcnt() { return _spCount + _wdCount; }
	void ReduceWdCount() { if (_wdCount > 0) _wdCount--; }

	bool HasSpace() { return _hasSpace; }

	void InitWdCount() { _wdCount = (_word.size() - _spCount); }
	int GetWdCount() { return _wdCount; }

	std::string GetWordS() { return _word; } // 공백 있이 단어 반환
	std::string GetWord() { return _word.substr(0, _word.size() - _spCount); } // 공백 없이 단어만 반환

	bool operator< (const Word& rhs) { return (this->_wdCount) < (rhs._wdCount); }
	bool operator> (const Word& rhs) { return (this->_wdCount) > (rhs._wdCount); }


public:

	std::string _word;
	int _spCount;
	int _wdCount;
	bool _hasSpace;
};





int CountSpace(int spos, const std::string& str)
{
	int spcnt = 0;
	for (int i = spos; i < str.size(); i++)
	{
		if (str[i] != ' ')
			break;
		spcnt++;
	}
	return spcnt;
}



bool HasSpace(int cnt)
{
	return cnt > 0;
}

int CheckWholeWdCnt(std::vector<Word>& vec)
{
	int temp{};
	for (auto& a : vec)
	{
		temp += a.GetWholewdcnt();
	}
	return temp;
}

bool CheckInputSen(std::string& str, int len) // 입력받은 값 검사해서 bool 값 환원
{
	int spcnt = 0;
	if (len > 40) //39+마침표 해서 40자 넘어가면 반려
	{
		std::cout << "Only 40 letters can be entered at a time(With comma at the end)" << std::endl;
		return false;
	}
	else if (len <= 0)
	{
		std::cout << "Please enter more than one alphabet." << std::endl;
		return false;
	}

	for (auto& a : str) // 글자 하나하나 확인
	{

		if (!isalpha(a) && a != ' ' && a != '.') // 영어가 아니라면 반려
		{
			std::cout << "Please input only English" << std::endl;
			return false;
		}
		else if (a == ' ')
			spcnt++;

	}

	bool spM5 = false;
	for (int i = 0; i < str.size(); i++)
	{
		if (spM5)
		{
			std::cout << "The space between words cannot exceed more than 5!" << std::endl;
			return false;
		}
		int cnt = 0;
		if (str[i] == ' ') // 공백 감지시
		{
			for (int f = i; f < str.size(); f++) //연속된 공백이 몇개인지
			{
				if (cnt > 5)
				{
					spM5 = true;
					break;
				}
				if (str[f] != ' ')
					break;
				cnt++;
			}
		}
	}
	

	if (str.size() == 1) // 한글자만 적었으면 반려
	{
		std::cout << "Please enter more than ONE alphabet!" << std::endl;
		return false;
	}
	if (str[len - 2] == ' ') // 마침표 전에 공백이 있으면 반려
	{
		std::cout << "Please do not enter space before comma." << std::endl;
		return false;
	}
	if (str[len - 1] != '.') // 문장 끝에 마침표 없으면 반려
	{
		std::cout << "Please enter a comma at the end of sentence." << std::endl;
		return false;
	}

	return true; // 그 어느것도 예외 없으면 진행

}


//백터 안에서 공백 줄이고 늘리는 함수 시리즈
void ReduSP(std::vector<Word>& std)
{
	for (auto a = 0; a < std.size(); a++) // 벡터 크기만큼 받아와서
	{
		/*if (std[a].HasSpace() && std[a].GetSpCount() > 0)
		{
			std[a]._word.pop_back();
			std[a].ReduceSpCount();
		}*/
		if (std[a].HasSpace() && std[a].GetWdCount() > 0 || std[a].GetSpCount() >0)
		{
			std[a]._word.pop_back();
			
			if (std[a].GetWdCount() > 0 && std[a].GetSpCount() == 0)
				std[a].ReduceWdCount();
			if (std[a].GetSpCount() > 0)
					std[a].ReduceSpCount();
		}
	}

}

//백터 안에서 공백 늘리기
void AddSP(std::vector<Word>& std)
{
	for (auto a = 0; a < std.size(); a++) // 벡터 크기만큼 받아와서
	{
		if (std[a].HasSpace() && std[a].GetSpCount() < 5)
		{
			std[a]._word.push_back(' ');
			std[a].IncreaseSpCount();
		}
	}
}

//대/소문자 전환
void ExcAlpha(std::vector<Word>& vec, char in1)
{

	for (int i = 0; i < vec.size(); i++)
	{
		for (auto& a : vec[i]._word)
		{
			if (in1 == a || in1 - 32 == a)
				a = a == in1 ? toupper(a) : tolower(a);
		}
	}
}

// 알파벳 순서대로 갯수 세기
void AlphaOrdcnt(std::vector<Word>& vec)
{
	int alcnt[52]{ 0, };
	for (int i = 0; i < vec.size(); i++)
	{
		for (const auto& a : vec[i]._word)
		{
			if (islower(a))
			{
				alcnt[a - 'a']++;
			}
			else if (isupper(a))
			{
				char c = a;

				char b = c - 'A';
				alcnt[(c - 'A') + 26]++;
			}
		}
	}
	for (int i = 0; i < 26; i++)
		if (alcnt[i])
			std::cout << (char)(i + 'a') << alcnt[i];
	for (int i = 26; i < 52; i++)
		if (alcnt[i])
			std::cout << (char)(i + 'A' - 26) << alcnt[i];
	std::cout << '.' << std::endl;
}

void PrintVec1(std::vector<Word>& vec) // 백터에서 워드 값 출력
{
	for (auto a = 0; a < vec.size(); a++)
	{
		std::cout << vec[a]._word;
	}
	std::cout << std::endl;
}


void PrintVec(std::vector<Word>& vec) // 백터에서 워드 값 출력 40자 제한
{
	if (CheckWholeWdCnt(vec) > 40)
	{
		int cnt = 1;
		for (auto& a : vec)
		{
			for (auto& b : a._word)
			{
				if (cnt == 40)
				{
					std::cout << '.' << std::endl;
					return;
				}
				std::cout << b;
				cnt++;
			}

		}

	}
	else
		PrintVec1(vec);
}

void AscendingAlpha(std::vector<Word>& vec) // 글자 길이 순서대로 단어 정렬
{
	std::vector<Word> temp = vec;
	temp[temp.size() - 1]._word.pop_back();
	temp[temp.size() - 1]._wdCount -= 1;

	std::sort(temp.begin(), temp.end());

	for (auto a = 0; a < temp.size(); a++)
	{
		if (a != temp.size() - 1)
			std::cout << temp[a].GetWord() << " ";
		else
			std::cout << temp[a].GetWord() << '.';

	}
	std::cout << std::endl;
}
std::string bChar;
std::vector<Word> sVInputs;

// 단어들로 잘게 쪼개서 벡터에 저장한후 저장된 순서대로 재조합 해서 보여줌
// 공백까지 포함해서 한 단어로 취급할 예정



int main()
{
	do
	{
		std::cout << "Enter the sentence : ";
		std::getline(std::cin, bChar);
		if (bChar.size() == 1)
		{

			continue;
		}
	} while (!CheckInputSen(bChar, bChar.size()));

	bChar = bChar.substr(0, 40); // 40자 이상이면 다 잘라냄



	int wrdcnt = 0;

	//공백까지 포함해서 단어 저장
	for (int i = 0; i < bChar.size(); i++)
	{

		int cnt = 0;
		if (bChar[i] == ' ') // 공백 감지시
		{
			for (int f = i; f < bChar.size(); f++) //연속된 공백이 몇개인지
			{
				if (bChar[f] != ' ')
					break;
				cnt++;
			}

			//sVInputs.push_back( new Word( bChar.substr(i-wrdcnt, wrdcnt + cnt)),cnt, HasSpace(cnt)); //현 위치에서 글자수만큼 뺀 지점 = 단어 시작 위치, 단어수+공백수만큼 저장 
			sVInputs.push_back(Word(bChar.substr(i - wrdcnt, wrdcnt + cnt), cnt, HasSpace(cnt)));

			wrdcnt = 0; // 글자수 리셋
			i += cnt; // 복귀하고 공백 수만큼 포인터 건너뜀
			cnt = 0;
		}
		wrdcnt++; // 글자수 저장
		if (i == bChar.size() - 1)
		{
			//sVInputs.push_back( new std::string(bChar.substr(i - (wrdcnt-1), wrdcnt)));
			for (int f = i; f < bChar.size(); f++) //연속된 공백이 몇개인지
			{
				if (bChar[f] != ' ')
					break;
				cnt++;
			}
			sVInputs.push_back(Word(bChar.substr(i - (wrdcnt - 1), wrdcnt), cnt, HasSpace(cnt)));
			cnt = 0;
			break;
		}
	}



	std::string in1;
	bool in3mode{ false };
	bool in4mode{ false };

	while (true)
	{
		std::cout << "Command : "; std::getline(std::cin, in1);
		if (in1.size() == 1)
		{

			if ((in3mode && in1[0] != '3') || (in4mode && in1[0] != '4'))
			{
				std::cout << "Invalid command! Only enter 3 or 4 when in command 3 or 4 mode!" << std::endl;
			}
			else if (in1[0] >= 'a' && in1[0] <= 'z') // 대소문자 변환
			{
				ExcAlpha(sVInputs, in1[0]);
				PrintVec(sVInputs);
			}
			else if (in1[0] == '1') // 공백 줄이기
			{
				//문자열 보관해둔 백터
				ReduSP(sVInputs);
				PrintVec(sVInputs);
			}
			else if (in1[0] == '2')// 공백 늘리기
			{
				AddSP(sVInputs);
				PrintVec(sVInputs);

			}
			else if (in1[0] == '3')//알파벳 순서대로 갯수 정리
			{
				if (in3mode && in1[0] == '3')
				{
					PrintVec(sVInputs);
					in3mode = false;
					continue;
				}

				AlphaOrdcnt(sVInputs);
				in3mode = true;

			}
			else if (in1[0] == '4')//단어 길이별로 오름차순 정렬하여 보여주기
			{
				if (in4mode && in1[0] == '4')
				{
					PrintVec(sVInputs);
					in4mode = false;
					continue;
				}

				AscendingAlpha(sVInputs);
				in4mode = true;
			}
			
			else if (in1[0] == '0') // 프로그램 종료
			{
				break;
			}

		}
		else // 2칸 이상이면 
		{
			if (in1[0] == '5')
			{

				size_t blankIdx{ in1.find_first_of(' ') };
				if (blankIdx == in1.npos) //
				{
					//return 0;
				}
				std::string parsedCommand{ in1.substr(0,blankIdx) };
				in1 = in1.substr(blankIdx + 1, in1.size() - blankIdx - 1);
				bool checkdigit = false;
				for (auto& a : in1)
				{
					if (!isdigit(a))
					{
						checkdigit = true;
						break;
					}

				}
				if (checkdigit)
				{
					std::cout << "INCORRECT SYNTAX" << std::endl;
					continue;
				}
				int i30 = std::stoi(in1);
				if (i30 < 1 || i30>40)
				{
					std::cout << "INVALID RANGE 1~40" << std::endl;
					continue;
				}
				/*std::string MERGE;
				for (auto& a : sVInputs)
				{
					MERGE.append(a.GetWordS());
				}*/

				std::string SUBSTRING = bChar;

				SUBSTRING = SUBSTRING.substr(0, i30);
				sVInputs.clear();
				wrdcnt = 0;
				for (int i = 0; i < SUBSTRING.size(); i++)
				{

					int cnt = 0;
					if (SUBSTRING[i] == ' ') // 공백 감지시
					{
						for (int f = i; f <(SUBSTRING.size()); f++) //연속된 공백이 몇개인지
						{
							if (SUBSTRING[f] != ' ')
								break;
							cnt++;
						}

						//sVInputs.push_back( new Word((SUBSTRING.substr(i-wrdcnt, wrdcnt + cnt)),cnt, HasSpace(cnt)); //현 위치에서 글자수만큼 뺀 지점 = 단어 시작 위치, 단어수+공백수만큼 저장 
						sVInputs.push_back(Word(SUBSTRING.substr(i - wrdcnt, wrdcnt + cnt), cnt, HasSpace(cnt)));

						wrdcnt = 0; // 글자수 리셋
						i += cnt; // 복귀하고 공백 수만큼 포인터 건너뜀
						cnt = 0;
					}
					wrdcnt++; // 글자수 저장
					if (i ==(SUBSTRING.size() - 1))
					{
						//sVInputs.push_back( new std::string(SUBSTRING.substr(i - (wrdcnt-1), wrdcnt)));
						for (int f = i; f <(SUBSTRING.size()); f++) //연속된 공백이 몇개인지
						{
							if (SUBSTRING[f] != ' ')
								break;
							cnt++;
						}
						sVInputs.push_back(Word(SUBSTRING.substr(i - (wrdcnt - 1), wrdcnt), cnt, HasSpace(cnt)));
						cnt = 0;
						break;
					}
					
				}
				sVInputs.back()._word.push_back('.');
			}
			else
			{
				std::cout << "Please Enter only ONE alphabet OR number at a time!" << std::endl;
			}
		}
	}
}
