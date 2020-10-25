#pragma once
class Zone
{
public:
	enum Cell {
		IsEmpty,
		IsShip,
		AroundShip
	};
private:
	

	Cell zone[10][10];
		
public:
	void ChangeTo(size_t i, size_t j, Cell cellType);
};

