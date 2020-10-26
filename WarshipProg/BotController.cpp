#include "BotController.h"
//ref _playerZone to local
BotController::BotController(const Zone& playerZone)
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			COORD temp;
			temp.X = i;
			temp.Y = j;
			_toAttack.push_back(temp);
		}
	}
    _playerZone = &playerZone;
}
#include <string>
COORD BotController::Attack()
{
	COORD coord;
    coord.X = 0;
    coord.Y = 0;
	switch (stage) {
	case Stage::Random:
		coord = RandomAttack();
		break;
	case Stage::FindAround:
        coord = FindAroundShot();
		break;
	case Stage::VectorContinue:
		ContinueVectorAttack();
		break;
	case Stage::ChangeVector:
		ChangeVectorAttack();
		break;
	}
    std::cout << (int)stage << std::endl;;
	return coord;
}

COORD BotController::RandomAttack()
{
	int randIndex = rand() % _toAttack.size();
	COORD attackCoord = _toAttack[randIndex];
	ConsoleController::AttackAnimation(attackCoord.X*2 + 2, attackCoord.Y + 2);
	_toAttack.erase(_toAttack.begin() + randIndex);
    _previousAttack.X = attackCoord.X;
    _previousAttack.Y = attackCoord.Y;
    _lastGreatAttack.X = attackCoord.X;
    _lastGreatAttack.Y = attackCoord.Y;

	return attackCoord;
}

COORD BotController::FindAroundShot()
{

    COORD newCoord;
    newCoord.X = _lastGreatAttack.X;
    newCoord.Y = _lastGreatAttack.Y;
    if (newCoord.X != 9 && _playerZone->Get(newCoord.X, newCoord.Y) != Zone::Cell::AroundShip)
    {
        newCoord.X += 1;
    }
    else if (newCoord.X != 0 && _playerZone->Get(newCoord.X - 1, newCoord.Y) != Zone::Cell::AroundShip)
    {
        newCoord.X -= 1;
    }
    else if (newCoord.Y != 9 && _playerZone->Get(newCoord.X, newCoord.Y + 1) != Zone::Cell::AroundShip)
    {
        newCoord.Y += 1;
    }
    else if (newCoord.Y != 0 && _playerZone->Get(newCoord.X, newCoord.Y - 1) != Zone::Cell::AroundShip)
    {
        newCoord.Y -= 1;
    }

    std::cout << newCoord.X << "  " << newCoord.Y << std::endl;
    RemoveCoordFromVector(newCoord.X, newCoord.Y);
    _previousAttack.X = newCoord.X;
    _previousAttack.Y = newCoord.Y;
    return newCoord;
    
 //   if (zone[nc.x, nc.y] == 1)//друге влучення
 //   {
 //       RemoveCoordFromVector(nc.x, nc.y);
 //       //попав
 //       GameObject.Find("FriendZone").gameObject.GetComponent<FriendZoneScript>().SetZone(nc.x, nc.y, 2);
 //       //GameObject.Find("FriendZone").gameObject.transform.GetChild(nc.x * 10 + nc.y).gameObject.GetComponent<Image>().sprite = DeadShipTexture;
 //       GameObject.Find("FriendZone").gameObject.transform.GetChild(nc.x * 10 + nc.y).gameObject.GetComponent<Animator>().SetBool("isDead", true);

 //       if (GameObject.Find("CheckFriendShipByBot").gameObject.GetComponent<CheckFriendShipByBotScript>().Checking(nc.x, nc.y) == false)
 //       {
 //           //не вбив
 //           previousAttack.x = nc.x;
 //           previousAttack.y = nc.y;
 //           Invoke("ContinueVectorAttack", 1);
 //           return;
 //       }
 //       else
 //       {
 //           //вбив
 //           continueAttack = 0;
 //           Invoke("ItterationFirstAttack", 1);
 //           return;
 //       }


 //   }
 //   else if (zone[nc.x, nc.y] == 0)
 //   {
 //       RemoveCoordFromVector(nc.x, nc.y);
 //       GameObject.Find("FriendZone").gameObject.GetComponent<FriendZoneScript>().SetZone(nc.x, nc.y, 3);
 //       //GameObject.Find("FriendZone").gameObject.transform.GetChild(nc.x * 10 + nc.y).gameObject.GetComponent<Image>().sprite = AroundShipTexture;
 //       GameObject.Find("FriendZone").gameObject.transform.GetChild(nc.x * 10 + nc.y).gameObject.GetComponent<Animator>().SetBool("isNone", true);
 //       //без другого влучення
 //       continueAttack = 1;
 //       DoCanUseTrue();
 //       return;
 //   }
	//return false;
}

bool BotController::ContinueVectorAttack()
{
	return false;
}

bool BotController::ChangeVectorAttack()
{
	return false;
}

void BotController::RemoveCoordFromVector(size_t x, size_t y)
{
    for (size_t i = 0; i < _toAttack.size(); i++) {
        if (_toAttack[i].X == x && _toAttack[i].Y == y)
            _toAttack.erase(_toAttack.begin() + i);
    }
}

void BotController::UpStage() {
    switch (stage) {
    case Stage::Random:
        stage = Stage::FindAround;
        break;
    case Stage::FindAround:
        stage = Stage::Random;//////////////////
        break;
    case Stage::VectorContinue:
        stage = Stage::ChangeVector;
        break;
    }
}

void BotController::ResetStage() {
    stage = Stage::Random;
}
