#pragma once
#include "Zone.h"
#include "ConsoleController.h"
#include "BotController.h"

 class GameController
{
private:
	 Zone playerZone;
	 Zone botZone;
public:
	 void Start();
	GameController();
private:
	enum Winner {
		Player, Bot
	};

	Winner Session();
	bool Attack(COORD coord, Zone& zone);
	
};

