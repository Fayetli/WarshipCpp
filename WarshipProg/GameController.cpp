#include "GameController.h"

typedef Zone::Cell Cell;
GameController::GameController() {

}

void GameController::Start() {
	//Creating two zone for player and enemy(bot)
	playerZone.RandomGenerate();
	botZone.RandomGenerate();
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
	BotController bot;
	ConsoleController::RenderMap(playerZone, botZone);

	while (true) {
		while (true) {
			COORD playerChoice = ConsoleController::Handle();
			bool playerShot = Attack(playerChoice, botZone);
			ConsoleController::RenderMap(playerZone, botZone);
			if (playerShot == false)
				break;;
			//CheckForKill
		}
		

		while (true) {
			COORD botChoice = bot.Attack();
			bool botShot = Attack(botChoice, playerZone);
			ConsoleController::RenderMap(playerZone, botZone);

			if (botShot == false)
				break;
			//CheckForKill
			Sleep(1500);
		}


	}



	return Winner::Player;


}

bool GameController::Attack(COORD coord, Zone& zone) {
	Cell cell = zone.Get(coord.X, coord.Y);
	if (cell == Cell::IsShip)
	{
		zone.ChangeTo(coord.X, coord.Y, Cell::IsDead);
		return true;
	}
	else {
		zone.ChangeTo(coord.X, coord.Y, Cell::AroundShip);
		return false;
	}
}