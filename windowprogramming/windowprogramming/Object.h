#pragma once
#include "Coord.h"





class Object
{
public:
	Object() {}
	Object(const Object &) {}
	virtual ~Object() {}

};



class Item
{
public:
	Item(Coord pos,int id) : _pos(pos), id(id)  {} 
	Item(int x, int y, int id) : id(id) { _pos(x, y); }

	bool operator==(Item rhs)
	{
		return (_pos.X == rhs._pos.X) && (_pos.Y == rhs._pos.Y);
	}
	
public:
	Coord _pos;
	int id;

};

