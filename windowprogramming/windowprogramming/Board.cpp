#include "Board.h"
#include "Object.h"
#include "Coord.h"

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution uidx(0, 16);
std::uniform_int_distribution uidy(0, 15);




void PrintTile(int element)
{
	switch (element)
	{
	case 0:
		std::cout << ' ';
		break;
	case 1:
		std::cout << '%';
		break;
	case 2:
		std::cout << '*';
		break;
	case 3:
		std::cout << '#';
		break;
	case 4:
		std::cout << '@';
		break;
	}
}




//std::vector<std::shared_ptr<class Object>> objects;
//std::vector<class Coord> SpawnGrid;
//std::vector<Coord> SpawnGridDelta;
int _board[ARR_SIZE][ARR_SIZE]{};

	void Board::Init()
	{
		if(!isInit)
		{
			Coord TEMP;
			for (int i = 0; i < ARR_SIZE - 3; i++)
			{
				for (int f = 0; f < ARR_SIZE - 3; f++)
				{

					SpawnGrid.push_back(TEMP(f, i));
				}
			}
			for (int i = 0; i < ARR_SIZE; i++)
			{
				for (int f = 0; f < ARR_SIZE; f++)
				{
					_board[i][f] = 0;

				}
			}
			return;
		}
		else
		{
			Coord TEMP;
			SpawnGrid.clear();
			for (int i = 0; i < ARR_SIZE - 3; i++)
			{
				for (int f = 0; f < ARR_SIZE - 3; f++)
				{

					SpawnGrid.push_back(TEMP(f, i));
				}
			}
			for (int i = 0; i < ARR_SIZE; i++)
			{
				for (int f = 0; f < ARR_SIZE; f++)
				{
					_board[i][f] = 0;

				}
			}
			return;
		}


	}

	void Board::Render()
	{
		system("cls");
		for (int i = 0; i < ARR_SIZE; i++)
		{
			for (int f = 0; f < ARR_SIZE; f++)
			{
				PrintTile(_board[i][f]);
			}
			std::cout << std::endl;
		}
	}

	void Board::SpawnObject()
	{
		int x = uidx(gen);
		int y = uidy(gen);
		Coord pos(x, y);

		// 3X4 장애물
		for (int i = y; i < y + 4; i++)
		{
			for (int f = x; f < x + 3; f++)
			{
				Coord Temp(f, i);
				_board[i][f] = 1;
				auto iterator = std::remove(SpawnGrid.begin(), SpawnGrid.end(), Temp);
				if (iterator != SpawnGrid.end())
					SpawnGrid.erase(iterator);// 생성 가능한 위치 모은 vector에서 현 pos값 삭제
			}
		}
		int tempX = 0;
		int tempY = 0;
		// 4x4 만들기 전 범위 삭제
		Coord boundBoxStart1(pos.X+2,pos.Y+3);
		tempY = (boundBoxStart1.Y - 7 > 0) ? (boundBoxStart1.Y - 7 > 0) : 0;
		tempX = (boundBoxStart1.X - 7 > 0) ? (boundBoxStart1.X - 7 > 0) : 0;

		for (int i = 0; i < 15; i++)
		{
				Coord Temp(16, i);
				auto iterator = std::remove(SpawnGrid.begin(), SpawnGrid.end(), Temp);
				if (iterator != SpawnGrid.end())
					SpawnGrid.erase(iterator);// 생성 가능한 위치 모은 vector에서 현 pos값 삭제
		}

		for (int i = boundBoxStart1.Y; i > tempY; i--)
		{
			for (int f = boundBoxStart1.X; f>tempX; f--)
			{
				Coord Temp(f, i);
				auto iterator = std::remove(SpawnGrid.begin(), SpawnGrid.end(), Temp);
				if (iterator != SpawnGrid.end())
					SpawnGrid.erase(iterator);// 생성 가능한 위치 모은 vector에서 현 pos값 삭제
			}
		}



		std::shuffle(SpawnGrid.begin(), SpawnGrid.end(), gen);

		pos = SpawnGrid.back();
		SpawnGrid.pop_back();

		// 4x4
		for (int i = pos.Y; i < pos.Y + 4; i++)
		{
			for (int f = pos.X; f < pos.X + 4; f++)
			{
				Coord Temp(f, i);
				_board[i][f] = 1;
				auto iterator = std::remove(SpawnGrid.begin(), SpawnGrid.end(), Temp);
				if (iterator != SpawnGrid.end())
					SpawnGrid.erase(iterator);// 생성 가능한 위치 모은 vector에서 현 pos값 삭제
			}
		}

		boundBoxStart1(pos.X + 3, pos.Y + 3);
		tempY = (boundBoxStart1.Y - 6 > 0) ? (boundBoxStart1.Y - 6 > 0) : 0;
		tempX = (boundBoxStart1.X - 8 > 0) ? (boundBoxStart1.X - 8 > 0) : 0;

		//for (int i = boundBoxStart1.Y; i > tempY; i--)
		//{
		//	Coord Temp(16, i);
		//	auto iterator = std::remove(SpawnGrid.begin(), SpawnGrid.end(), Temp);
		//	if (iterator != SpawnGrid.end())
		//		SpawnGrid.erase(iterator);// 생성 가능한 위치 모은 vector에서 현 pos값 삭제
		//}

		for (int i = boundBoxStart1.Y; i > tempY; i--)
		{
			for (int f = boundBoxStart1.X; f > tempX; f--)
			{
				Coord Temp(f, i);
				auto iterator = std::remove(SpawnGrid.begin(), SpawnGrid.end(), Temp);
				if (iterator != SpawnGrid.end())
					SpawnGrid.erase(iterator);// 생성 가능한 위치 모은 vector에서 현 pos값 삭제
			}
		}

		std::shuffle(SpawnGrid.begin(), SpawnGrid.end(), gen);

		pos = SpawnGrid.back();
		SpawnGrid.pop_back();


		for (int i = pos.Y; i < pos.Y + 2; i++)
		{
			for (int f = pos.X; f < pos.X + 5; f++)
			{
				Coord Temp(f, i);
				_board[i][f] = 1;
				auto iterator = std::remove(SpawnGrid.begin(), SpawnGrid.end(), Temp);
				if (iterator != SpawnGrid.end())
					SpawnGrid.erase(iterator);// 생성 가능한 위치 모은 vector에서 현 pos값 삭제
			}
		}
	}

	void Board::SpawnItem()
	{
		std::uniform_int_distribution uidR(0, 20);
		

		int itemcount = 10;
		int i = 0;
		int x = uidR(rd);
		int y = uidR(rd);

		while (i < itemcount)
		{
			if (_board[y][x] == 0)
			{
				_board[y][x] = 2;
				Item item = Item(x, y,i);
				objects.push_back(item);
				x = uidR(rd);
				y = uidR(rd);
				i++;
			}
			x = uidR(rd);
			y = uidR(rd);
		}
	}

	void Board::SpawnPlayer()
	{
		std::uniform_int_distribution uidR(0, 20);


		int playercount = 2;
		int i = 0;
		int cnt = 0;
		int x = uidR(rd);
		int y = uidR(rd);

		while (i < playercount)
		{
			if (_board[y][x] == 0)
			{
				_board[y][x] = 3 + cnt;
				if (cnt == 0)
				{
					player1 = Player{ Coord(x, y), 0 };
				}
				else
				{
					player2 = Player{ Coord(x, y), 0 };
				}
				x = uidR(rd);
				y = uidR(rd);
				i++;
				cnt++;
			}
			x = uidR(rd);
			y = uidR(rd);
		}
	}

	void Board::PrintPlayerPoints()
	{
		std::cout << "Player1 Point : " << player1._itemcount << " Player2 Point : " << player2._itemcount << std::endl;
	}

	bool Board::CanGo(int dir) // 0L 1U, 2R, 3D
	{
		switch (dir)
		{
		case 0:
			if (_board[player1._pos.Y][player1._pos.X-1] != 0 || player1._pos.X - 1 == 0 || player1._pos.X - 1 == 2)
				return false;
			return true;
			break;
		case 1:
			if (_board[player1._pos.Y-1][player1._pos.X] != 0 || player1._pos.Y - 1 == 0 || player1._pos.Y - 1 == 2)
				return false;
			return true;
			break;
		case 2:
			if (_board[player1._pos.Y][player1._pos.X+1] != 0 || player1._pos.X + 1 == 0 || player1._pos.X + 1 == 2)
				return false;
			return true;
			break;
		case 3:
			if (_board[player1._pos.Y - 1][player1._pos.X] != 0 || player1._pos.Y + 1 == 0 || player1._pos.Y + 1 == 2)
				return false;
			return true;
			break;
		default:
			break;
		}
	}



	//for (int i = 0; i < 4; i++)
	//{
	//	if (CanGo(i) && i == 0)
	//	{
	//		_board[player1._pos.Y][player1._pos.X] = 0;
	//		player1._pos.X -= 1;
	//		_board[player1._pos.Y][player1._pos.X] = 3;
	//	}
	//	else if (CanGo(i) && i == 1)
	//	{
	//		_board[player1._pos.Y][player1._pos.X] = 0;
	//		player1._pos.Y -= 1;
	//		_board[player1._pos.Y][player1._pos.X] = 3;
	//	}
	//	else if (CanGo(i) && i == 2)
	//	{
	//		_board[player1._pos.Y][player1._pos.X] = 0;
	//		player1._pos.X += 1;
	//		_board[player1._pos.Y][player1._pos.X] = 3;
	//	}
	//	else if (CanGo(i) && i == 3)
	//	{
	//		_board[player1._pos.Y][player1._pos.X] = 0;
	//		player1._pos.Y += 1;
	//		_board[player1._pos.Y][player1._pos.X] = 3;
	//	}
	//}


	void Board::P1left()	
	{
		if (player1._pos.X - 1 < 0 && (_board[player1._pos.Y][19] == 0 || _board[player1._pos.Y][19] == 2))
		{
			if (_board[player1._pos.Y][19] == 2)
			{
				player1._itemcount++;
				auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(19,player1._pos.Y),0));
				if (iterator != objects.end())
					objects.erase(iterator);
				_board[player1._pos.Y][player1._pos.X] = 0; //현재 위치 삭제
				player1._pos.X = 19; // 이동
				_board[player1._pos.Y][player1._pos.X] = 0; // 아이템 삭제
				for (int i = 0; i < 4; i++)
				{
					if (CanGo(i) && i == 0)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.X -= 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 1)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.Y -= 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (i == 2) // 온길 돌아가기 때문
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.X = 0;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 3)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.Y += 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
				}
				//_board[player1._pos.Y][player1._pos.X] = 0; // 필요 없음. 이미 위에서 다 확인하고 이동함.
				//player1._pos.X = 19;
				//_board[player1._pos.Y][19] = 3;
			}
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.X = 19;
			_board[player1._pos.Y][19] = 3;
			return;
			
		}
		if (_board[player1._pos.Y][player1._pos.X - 1] == 0)
		{
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.X -= 1;
			_board[player1._pos.Y][player1._pos.X] = 3;
			return;
		}
		if (_board[player1._pos.Y][player1._pos.X - 1] == 2)
		{
			player1._itemcount++;
			auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player1._pos.X - 1, player1._pos.Y), 0));
			if (iterator != objects.end())
				objects.erase(iterator);
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.X -= 1;
			_board[player1._pos.Y][player1._pos.X] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (CanGo(i) && i == 0)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.X -= 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 1)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.Y -= 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 2)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.X += 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 3)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.Y += 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
			}
		}
			
	}
	void Board::P1RIght()	
	{
		if (player1._pos.X + 1 > 19 && (_board[player1._pos.Y][0] == 0 || _board[player1._pos.Y][0] == 2))
		{
			if (_board[player1._pos.Y][0] == 2)
			{
				player1._itemcount++;
				auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(0, player1._pos.Y), 0));
				if (iterator != objects.end())
					objects.erase(iterator);
				_board[player1._pos.Y][player1._pos.X] = 0;
				player1._pos.X = 0;
				_board[player1._pos.Y][player1._pos.X] = 0;
				for (int i = 0; i < 4; i++)
				{
					if ( i == 0)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.X = 19;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 1) // TODO
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.Y -= 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 2)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.X += 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 3)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.Y += 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
				}
				/*_board[player1._pos.Y][player1._pos.X] = 0;
				player1._pos.X = 0;
				_board[player1._pos.Y][0] = 3;*/
			}
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.X = 0;
			_board[player1._pos.Y][player1._pos.X] = 3;
			return;

		}
		if (_board[player1._pos.Y][player1._pos.X + 1] == 0)
		{
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.X += 1;
			_board[player1._pos.Y][player1._pos.X] = 3;
			return;
		}
		if (_board[player1._pos.Y][player1._pos.X + 1] == 2)
		{
			player1._itemcount++;
			auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player1._pos.X + 1, player1._pos.Y), 0));
			if (iterator != objects.end())
				objects.erase(iterator);
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.X += 1;
			_board[player1._pos.Y][player1._pos.X] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (CanGo(i) && i == 0)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.X -= 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 1)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.Y -= 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 2)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.X += 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 3)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.Y += 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
			}
		}
	}	
	void Board::P1Up()		
	{
		if (player1._pos.Y - 1 < 0 && (_board[19][player1._pos.X] == 0 || _board[19][player1._pos.X] == 2))
		{
			if (_board[19][player1._pos.X] == 2)
			{
				player1._itemcount++;
				auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player1._pos.X, 19), 0));
				if (iterator != objects.end())
					objects.erase(iterator);
				_board[player1._pos.Y][player1._pos.X] = 0;
				player1._pos.Y = 19;
				_board[19][player1._pos.X] = 0;
				for (int i = 0; i < 4; i++)
				{
					if (CanGo(i) && i == 0)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.X -= 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 1) //TODO
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.Y -= 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (i == 2)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.X += 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 3)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.Y = 0;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
				}
				/*_board[player1._pos.Y][player1._pos.X] = 0;
				player1._pos.Y = 0;
				_board[playe][0] = 3;*/
			}
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.Y = 19;
			_board[player1._pos.Y][player1._pos.X] = 3;
			return;

		}
		if (_board[player1._pos.Y-1][player1._pos.X] == 0)
		{
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.Y -= 1;
			_board[player1._pos.Y][player1._pos.X] = 3;
			return;
		}
		if (_board[player1._pos.Y-1][player1._pos.X] == 2)
		{
			player1._itemcount++;
			auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player1._pos.X, player1._pos.Y - 1), 0));
			if (iterator != objects.end())
				objects.erase(iterator);
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.Y -= 1;
			_board[player1._pos.Y][player1._pos.X] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (CanGo(i) && i == 0)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.X -= 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 1)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.Y -= 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 2)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.X += 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (i == 3)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.Y += 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
			}
		}
	}
	void Board::P1Down()	
	{
		if (player1._pos.Y + 1 > 19 && (_board[0][player1._pos.X] == 0 || _board[0][player1._pos.X] == 2))
		{
			if (_board[0][player1._pos.X] == 2)
			{
				player1._itemcount++;
				auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player1._pos.X, 0), 0));
				if (iterator != objects.end())
					objects.erase(iterator);
				_board[player1._pos.Y][player1._pos.X] = 0;
				player1._pos.Y = 0;
				_board[0][player1._pos.X] = 0;
				for (int i = 0; i < 4; i++)
				{
					if (CanGo(i) && i == 0)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.X -= 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (i == 1) //TODO
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.Y = 19;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 2)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.X += 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
					else if (CanGo(i) && i == 3)
					{
						_board[player1._pos.Y][player1._pos.X] = 1;
						player1._pos.Y += 1;
						_board[player1._pos.Y][player1._pos.X] = 3;
						return;
					}
				}
				/*_board[player1._pos.Y][player1._pos.X] = 0;
				player1._pos.Y = 0;
				_board[playe][0] = 3;*/
			}
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.Y = 0;
			_board[player1._pos.Y][player1._pos.X] = 3;
			return;

		}
		if (_board[player1._pos.Y+1][player1._pos.X] == 0)
		{
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.Y += 1;
			_board[player1._pos.Y][player1._pos.X] = 3;
			return;
		}
		if (_board[player1._pos.Y+1][player1._pos.X] == 2)
		{
			player1._itemcount++;
			auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player1._pos.X, player1._pos.Y+1), 0));
			if (iterator != objects.end())
				objects.erase(iterator);
			_board[player1._pos.Y][player1._pos.X] = 0;
			player1._pos.Y += 1;
			_board[player1._pos.Y][player1._pos.X] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (CanGo(i) && i == 0)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.X -= 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 1)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.Y -= 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 2)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.X += 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
				else if (CanGo(i) && i == 3)
				{
					_board[player1._pos.Y][player1._pos.X] = 1;
					player1._pos.Y += 1;
					_board[player1._pos.Y][player1._pos.X] = 3;
					return;
				}
			}
		}
	}

	void Board::P2left()	
	{
		if (player2._pos.X - 1 < 0 && (_board[player2._pos.Y][19] == 0 || _board[player2._pos.Y][19] == 2))
		{
			if (_board[player2._pos.Y][19] == 2)
			{
				player2._itemcount++;
				auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(19, player2._pos.Y), 0));
				if (iterator != objects.end())
					objects.erase(iterator);
				_board[player2._pos.Y][player2._pos.X] = 0; //현재 위치 삭제
				player2._pos.X = 19; // 이동
				_board[player2._pos.Y][player2._pos.X] = 0; // 아이템 삭제
				for (int i = 0; i < 4; i++)
				{
					if (CanGo(i) && i == 0)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.X -= 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 1)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.Y -= 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (i == 2) // 온길 돌아가기 때문
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.X = 0;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 3)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.Y += 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
				}
				//_board[player2._pos.Y][player2._pos.X] = 0; // 필요 없음. 이미 위에서 다 확인하고 이동함.
				//player2._pos.X = 19;
				//_board[player2._pos.Y][19] = 3;
			}
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.X = 19;
			_board[player2._pos.Y][19] = 4;
			return;

		}
		if (_board[player2._pos.Y][player2._pos.X - 1] == 0)
		{
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.X -= 1;
			_board[player2._pos.Y][player2._pos.X] = 4;
			return;
		}
		if (_board[player2._pos.Y][player2._pos.X - 1] == 2)
		{
			player2._itemcount++;
			auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player2._pos.X - 1, player2._pos.Y), 0));
			if (iterator != objects.end())
				objects.erase(iterator);
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.X -= 1;
			_board[player2._pos.Y][player2._pos.X] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (CanGo(i) && i == 0)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.X -= 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 1)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.Y -= 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 2)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.X += 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 3)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.Y += 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
			}
		}
	}
	void Board::P2RIght()	
	{
		if (player2._pos.X + 1 > 19 && (_board[player2._pos.Y][0] == 0 || _board[player2._pos.Y][0] == 2))
		{
			if (_board[player2._pos.Y][0] == 2)
			{
				player2._itemcount++;
				auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(0, player2._pos.Y), 0));
				if (iterator != objects.end())
					objects.erase(iterator);
				_board[player2._pos.Y][player2._pos.X] = 0;
				player2._pos.X = 0;
				_board[player2._pos.Y][player2._pos.X] = 0;
				for (int i = 0; i < 4; i++)
				{
					if (i == 0)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.X = 19;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 1) // TODO
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.Y -= 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 2)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.X += 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 3)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.Y += 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
				}
				/*_board[player2._pos.Y][player2._pos.X] = 0;
				player2._pos.X = 0;
				_board[player2._pos.Y][0] = 3;*/
			}
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.X = 0;
			_board[player2._pos.Y][player2._pos.X] = 4;
			return;

		}
		if (_board[player2._pos.Y][player2._pos.X + 1] == 0)
		{
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.X += 1;
			_board[player2._pos.Y][player2._pos.X] = 4;
			return;
		}
		if (_board[player2._pos.Y][player2._pos.X + 1] == 2)
		{
			player2._itemcount++;
			auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player2._pos.X + 1, player2._pos.Y), 0));
			if (iterator != objects.end())
				objects.erase(iterator);
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.X += 1;
			_board[player2._pos.Y][player2._pos.X] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (CanGo(i) && i == 0)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.X -= 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 1)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.Y -= 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 2)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.X += 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 3)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.Y += 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
			}
		}
	}
	void Board::P2Up()		
	{
		if (player2._pos.Y - 1 < 0 && (_board[19][player2._pos.X] == 0 || _board[19][player2._pos.X] == 2))
		{
			if (_board[19][player2._pos.X] == 2)
			{
				player2._itemcount++;
				auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player2._pos.X, 19), 0));
				if (iterator != objects.end())
					objects.erase(iterator);
				_board[player2._pos.Y][player2._pos.X] = 0;
				player2._pos.Y = 19;
				_board[19][player2._pos.X] = 0;
				for (int i = 0; i < 4; i++)
				{
					if (CanGo(i) && i == 0)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.X -= 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 1) //TODO
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.Y -= 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (i == 2)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.X += 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 3)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.Y = 0;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
				}
				/*_board[player2._pos.Y][player2._pos.X] = 0;
				player2._pos.Y = 0;
				_board[playe][0] = 3;*/
			}
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.Y = 19;
			_board[player2._pos.Y][player2._pos.X] = 4;
			return;

		}
		if (_board[player2._pos.Y - 1][player2._pos.X] == 0)
		{
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.Y -= 1;
			_board[player2._pos.Y][player2._pos.X] = 4;
			return;
		}
		if (_board[player2._pos.Y - 1][player2._pos.X] == 2)
		{
			player2._itemcount++;
			auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player2._pos.X, player2._pos.Y - 1), 0));
			if (iterator != objects.end())
				objects.erase(iterator);
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.Y -= 1;
			_board[player2._pos.Y][player2._pos.X] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (CanGo(i) && i == 0)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.X -= 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 1)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.Y -= 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 2)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.X += 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (i == 3)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.Y += 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
			}
		}
	}
	void Board::P2Down()	
	{
		if (player2._pos.Y + 1 > 19 && (_board[0][player2._pos.X] == 0 || _board[0][player2._pos.X] == 2))
		{
			if (_board[0][player2._pos.X] == 2)
			{
				player2._itemcount++;
				auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player2._pos.X, 0), 0));
				if (iterator != objects.end())
					objects.erase(iterator);
				_board[player2._pos.Y][player2._pos.X] = 0;
				player2._pos.Y = 0;
				_board[0][player2._pos.X] = 0;
				for (int i = 0; i < 4; i++)
				{
					if (CanGo(i) && i == 0)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.X -= 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (i == 1) //TODO
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.Y = 19;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 2)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.X += 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
					else if (CanGo(i) && i == 3)
					{
						_board[player2._pos.Y][player2._pos.X] = 1;
						player2._pos.Y += 1;
						_board[player2._pos.Y][player2._pos.X] = 4;
						return;
					}
				}
				/*_board[player2._pos.Y][player2._pos.X] = 0;
				player2._pos.Y = 0;
				_board[playe][0] = 3;*/
			}
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.Y = 0;
			_board[player2._pos.Y][player2._pos.X] = 4;
			return;

		}
		if (_board[player2._pos.Y + 1][player2._pos.X] == 0)
		{
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.Y += 1;
			_board[player2._pos.Y][player2._pos.X] = 4;
			return;
		}
		if (_board[player2._pos.Y + 1][player2._pos.X] == 2)
		{
			player2._itemcount++;
			auto iterator = std::remove(objects.begin(), objects.end(), Item(Coord(player2._pos.X, player2._pos.Y + 1), 0));
			if (iterator != objects.end())
				objects.erase(iterator);
			_board[player2._pos.Y][player2._pos.X] = 0;
			player2._pos.Y += 1;
			_board[player2._pos.Y][player2._pos.X] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (CanGo(i) && i == 0)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.X -= 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 1)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.Y -= 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 2)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.X += 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
				else if (CanGo(i) && i == 3)
				{
					_board[player2._pos.Y][player2._pos.X] = 1;
					player2._pos.Y += 1;
					_board[player2._pos.Y][player2._pos.X] = 4;
					return;
				}
			}
		}
	}

	bool Board::HasEnded()
	{
		if (player1._itemcount + player2._itemcount == 10)
		{
			return true;
		}
		return false;
	}


	void Board::CheckForWinner()
	{
		if (player1._itemcount > player2._itemcount)
		{
			std::cout << "Player1 : " << player1._itemcount << " > Player2 :" << player2._itemcount << " Player 1 wins!" << std::endl;
		}
		else if (player1._itemcount < player2._itemcount)
		{
			std::cout << "Player2:" << player2._itemcount << " > Player1 : " << player1._itemcount << "Player 2 wins!" << std::endl;
		}
		else
		{
			std::cout << "DRAW!" << std::endl;
		}
	}

	
