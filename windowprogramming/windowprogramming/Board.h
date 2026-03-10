#pragma once
#define ARR_SIZE 20
#include <vector>
#include <memory>
#include "Coord.h"
#include "Object.h"

class Player
{
public:
	Player() {}
	Player(Coord pos, int icnt) : _pos(pos), _itemcount(icnt) {}

	
public:
	Coord _pos;
	int _itemcount;

};


class Board
{
public:
	Board() {};
	~Board() {};

	void Init();
	

	void Render();


	void SpawnObject();

	void SpawnItem();
	void SpawnPlayer();

	void PrintPlayerPoints();

	bool CanGo(int dir);

	void P1left();
	void P1RIght();
	void P1Up();
	void P1Down();

	void P2left();
	void P2RIght();
	void P2Up();
	void P2Down(); 

	bool HasEnded();

	void CheckForWinner();

private:
	std::vector<Item> objects;
	std::vector<class Coord> SpawnGrid;
	std::vector<Coord> SpawnGridDelta;
	int _board[ARR_SIZE][ARR_SIZE]{};

	bool isInit = false;

	Player player1;
	Player player2;

};

