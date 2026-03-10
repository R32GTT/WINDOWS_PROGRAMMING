#pragma once
class Coord
{
public:
	Coord() {}
	Coord(int x, int y) : X(x), Y(y) {}

	Coord operator=(Coord rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		return *this;
	}

	Coord operator()(int x, int y)
	{
		X = x;
		Y = y;
		return *this;
	}

	bool operator==(Coord rhs)
	{
		return (X == rhs.X) && (Y == rhs.Y);
	}

public:
	int X;
	int Y;
};
