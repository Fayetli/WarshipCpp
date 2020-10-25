#include "GameController.h"


GameController::GameController() {
	
}

void GameController::Start() {
	//Creating two zone for player and enemy(bot)
	Zone zone;
	zone.ChangeTo(5, 5, Zone::Cell::IsShip);
	//Randomize ships on zones
	//Game session(player choice -> bot choice)

	Winner winner = Session();

	switch (winner) {
	case Winner::Player:
	{
		//Player win
	}
	case Winner::Bot: {
		//Bot win
	}
	}
}

GameController::Winner GameController::Session() {
	playerZone.ChangeTo(5, 5, Zone::Cell::AroundShip);
	ConsoleController::RenderMap(playerZone, botZone);

	return Winner::Player;


}