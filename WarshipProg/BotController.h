#pragma once
#include <vector>
#include <windows.h>
class BotController
{
private:
	std::vector<COORD> _toAttack;


	enum Stage {
		Random,
		FindAround,
		VectorContinue,
		ChangeVector
	};
	Stage stage = Stage::Random;
public:
	BotController();
	COORD Attack();
	COORD RandomAttack();
	bool FindAroundShot();
	bool ContinueVectorAttack();
	bool ChangeVectorAttack();
};

