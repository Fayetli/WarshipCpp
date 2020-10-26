#include "BotController.h"

BotController::BotController()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			COORD temp;
			temp.X = i;
			temp.Y = j;
			_toAttack.push_back(temp);
		}
	}
}

COORD BotController::Attack()
{
	COORD coord;
	switch (stage) {
	case Stage::Random:
		coord = RandomAttack();
		break;
	case Stage::FindAround:
		FindAroundShot();
		break;
	case Stage::VectorContinue:
		ContinueVectorAttack();
		break;
	case Stage::ChangeVector:
		ChangeVectorAttack();
		break;
	}
	return coord;
}

COORD BotController::RandomAttack()
{
	int randIndex = rand() % _toAttack.size();
	COORD attackCoord = _toAttack[randIndex];
	_toAttack.erase(_toAttack.begin() + randIndex);

	return attackCoord;
}

bool BotController::FindAroundShot()
{
	return false;
}

bool BotController::ContinueVectorAttack()
{
	return false;
}

bool BotController::ChangeVectorAttack()
{
	return false;
}
