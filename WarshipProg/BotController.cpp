#include "BotController.h"
//ref _playerZone to local
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
#include <string>
COORD BotController::Attack(Act lastAct = Act::Miss)
{
	switch (lastAct) {
	case Act::Miss:
		switch (_stage) {
		case Stage::VectorContinue:
			ChangeVectorAttack();
			break;
		}
		_playerZone.ChangeTo(_previousAttack.X, _previousAttack.Y, Zone::Cell::AroundShip);
		//Write to local player zone
		break;
	case Act::Shot:
		switch (_stage) {
		case Stage::Random:
			_stage = Stage::FindAround;
			break;
		case Stage::FindAround:
			_stage = Stage::VectorContinue;
		}
		_playerZone.ChangeTo(_previousAttack.X, _previousAttack.Y, Zone::Cell::IsDead);;
		//Write to local player zone
		break;
	case Act::Kill:
		_stage = Stage::Random;
		_playerZone.ChangeTo(_previousAttack.X, _previousAttack.Y, Zone::Cell::IsDead);
		_playerZone.RecursiveDesignateAroundBoommedShip(_previousAttack.X, _previousAttack.Y, _previousAttack.X, _previousAttack.Y);
		RemoveCoordFromVector();
		//Write to local player zone
		break;
	}



	COORD coord;
	coord.X = 0;
	coord.Y = 0;

	switch (_stage) {
	case Stage::Random:
		coord = RandomAttack();
		break;
	case Stage::FindAround:
		coord = FindAroundShot();
		break;
	case Stage::VectorContinue:
		coord = ContinueVectorAttack();
		break;
	}
	return coord;
}

COORD BotController::RandomAttack()
{
	int randIndex = rand() % _toAttack.size();
	COORD currentAttack = _toAttack[randIndex];
	ConsoleController::AttackAnimation(currentAttack.X * 2 + 2, currentAttack.Y + 2);
	_toAttack.erase(_toAttack.begin() + randIndex);
	_previousAttack.X = currentAttack.X;
	_previousAttack.Y = currentAttack.Y;
	_lastGreatAttack.X = currentAttack.X;
	_lastGreatAttack.Y = currentAttack.Y;
	RemoveCoordFromVector(currentAttack.X, currentAttack.Y);

	return currentAttack;
}

COORD BotController::FindAroundShot()
{

	COORD currentCoord;
	currentCoord.X = _lastGreatAttack.X;
	currentCoord.Y = _lastGreatAttack.Y;
	if (currentCoord.X != 9 && _playerZone.Get(currentCoord.X + 1, currentCoord.Y) != Zone::Cell::AroundShip)
	{
		currentCoord.X += 1;
	}
	else if (currentCoord.X != 0 && _playerZone.Get(currentCoord.X - 1, currentCoord.Y) != Zone::Cell::AroundShip)
	{
		currentCoord.X -= 1;
	}
	else if (currentCoord.Y != 9 && _playerZone.Get(currentCoord.X, currentCoord.Y + 1) != Zone::Cell::AroundShip)
	{
		currentCoord.Y += 1;
	}
	else if (currentCoord.Y != 0 && _playerZone.Get(currentCoord.X, currentCoord.Y - 1) != Zone::Cell::AroundShip)
	{
		currentCoord.Y -= 1;
	}

	RemoveCoordFromVector(currentCoord.X, currentCoord.Y);
	_previousAttack.X = currentCoord.X;
	_previousAttack.Y = currentCoord.Y;
	return currentCoord;
}

COORD BotController::ContinueVectorAttack()
{
	bool horizontal = (_lastGreatAttack.X == _previousAttack.X);

	COORD currentAttack;
	if (horizontal)
	{
		if (_previousAttack.Y > _lastGreatAttack.Y)
		{
			if (_previousAttack.Y + 1 > 9 || _playerZone.Get(_previousAttack.X, _previousAttack.Y + 1) == Zone::Cell::AroundShip)
			{
				ChangeVectorAttack();
				return ContinueVectorAttack();
			}
			else
			{
				if (_playerZone.Get(_previousAttack.X, _previousAttack.Y + 1) == Zone::Cell::IsDead) {
					_lastGreatAttack = _previousAttack;
					_previousAttack.Y += 1;
				}
				currentAttack.X = _previousAttack.X;
				currentAttack.Y = _previousAttack.Y + 1;
			}
		}
		else if (_previousAttack.Y < _lastGreatAttack.Y)
		{
			if (_previousAttack.Y - 1 < 0 || _playerZone.Get(_previousAttack.X, _previousAttack.Y - 1) == Zone::Cell::AroundShip)
			{
				ChangeVectorAttack();
				return ContinueVectorAttack();
			}
			else
			{
				if (_playerZone.Get(_previousAttack.X, _previousAttack.Y - 1) == Zone::Cell::IsDead) {
					_lastGreatAttack = _previousAttack;
					_previousAttack.Y -= 1;
				}
				currentAttack.X = _previousAttack.X;
				currentAttack.Y = _previousAttack.Y - 1;
			}
		}
	}
	else
	{
		if (_previousAttack.X > _lastGreatAttack.X)
		{
			if (_previousAttack.X + 1 > 9 || _playerZone.Get(_previousAttack.X + 1, _previousAttack.Y) == Zone::Cell::AroundShip)
			{
				ChangeVectorAttack();
				return ContinueVectorAttack();
			}
			else
			{
				if (_playerZone.Get(_previousAttack.X + 1, _previousAttack.Y) == Zone::Cell::IsDead) {
					_lastGreatAttack = _previousAttack;
					_previousAttack.X += 1;
				}
				currentAttack.X = _previousAttack.X + 1;
				currentAttack.Y = _previousAttack.Y;
			}
		}
		else if (_previousAttack.X < _lastGreatAttack.X || _playerZone.Get(_previousAttack.X - 1, _previousAttack.Y) == Zone::Cell::AroundShip)
		{
			if (_previousAttack.X - 1 < 0)
			{
				ChangeVectorAttack();
				return ContinueVectorAttack();
			}
			else
			{
				if (_playerZone.Get(_previousAttack.X - 1, _previousAttack.Y) == Zone::Cell::IsDead) {
					_lastGreatAttack = _previousAttack;
					_previousAttack.X -= 1;
				}
				currentAttack.X = _previousAttack.X - 1;
				currentAttack.Y = _previousAttack.Y;
			}
		}
	}
	_lastGreatAttack = _previousAttack;
	_previousAttack = currentAttack;
	RemoveCoordFromVector(currentAttack.X, currentAttack.Y);
	return currentAttack;
}

void BotController::ChangeVectorAttack()
{
	COORD temp = _previousAttack;
	_previousAttack = _lastGreatAttack;
	_lastGreatAttack = temp;
}

void BotController::RemoveCoordFromVector(size_t x, size_t y)
{
	for (size_t i = 0; i < _toAttack.size(); i++) {
		if (_toAttack[i].X == x && _toAttack[i].Y == y)
			_toAttack.erase(_toAttack.begin() + i);
	}
}

void BotController::RemoveCoordFromVector()
{

	for (size_t i = 0; i < _toAttack.size(); i++) {
		Zone::Cell current = _playerZone.Get(_toAttack[i].X, _toAttack[i].Y);
		if (current == Zone::Cell::AroundShip || current == Zone::Cell::IsDead) {
			_toAttack.erase(_toAttack.begin() + i--);
		}
	}

}
