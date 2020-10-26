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
	const Zone* _playerZone;

	enum Stage {
		Random,
		FindAround,
		VectorContinue,
		ChangeVector
	};
	Stage stage = Stage::Random;
public:
	BotController(const Zone& playerZone);
	COORD Attack();
	COORD RandomAttack();
	COORD FindAroundShot();
	bool ContinueVectorAttack();
	bool ChangeVectorAttack();
	void RemoveCoordFromVector(size_t x, size_t y);
	void UpStage();
	void ResetStage();
};

