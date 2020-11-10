#pragma once
#include <vector>
#include <windows.h>
#include "ConsoleController.h"

class BotController
{
private:
	std::vector<COORD> _toAttack;
	COORD _previousAttack;
	COORD _lastGreatAttack;
	Zone _playerZone;

	enum Stage {
		Random,
		FindAround,
		VectorContinue,
	};
	
	
	
	Stage _stage = Stage::Random;
public:
	enum Act {
		Miss,
		Shot,
		Kill
	};

	BotController();
	COORD Attack(Act lastAct);
	COORD RandomAttack();
	COORD FindAroundShot();
	COORD ContinueVectorAttack();
	void ChangeVectorAttack();
	void RemoveCoordFromVector(size_t x, size_t y);
	void RemoveCoordFromVector();
};

