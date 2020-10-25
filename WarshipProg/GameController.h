#pragma once
#include "Zone.h"
#include "ConsoleController.h"

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

	
};

