#pragma once
#include <cstdlib>

class Zone
{
public:
	enum Cell {
		IsEmpty,
		IsShip,
		IsDead,
		AroundShip
	};
private:
	

	Cell zone[10][10];
		
public:
	void ChangeTo(size_t i, size_t j, Cell cellType);
	Cell Get(size_t i, size_t j) const;
	void RandomGenerate();
};

