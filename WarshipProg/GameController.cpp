#include "GameController.h"

typedef Zone::Cell Cell;
GameController::GameController() {

}

void GameController::Start() {
	playerZone.RandomGenerate();
	botZone.RandomGenerate();
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
	BotController bot(playerZone);
	ConsoleController::RenderMap(playerZone, botZone);

	unsigned int playerScore = 0;
	unsigned int botScore = 0;
	while (true) {
		while (true) {
			ConsoleController::RenderMap(playerZone, botZone);
			COORD playerChoice = ConsoleController::Handle();
			bool playerShot = Attack(playerChoice, botZone);

			if (playerShot == false)
				break;

			bool isBoomed = botZone.RecursiveCheckShip(playerChoice.X, playerChoice.Y, playerChoice.X, playerChoice.Y);
			if (isBoomed)
				playerScore += botZone.RecursiveDesignateAroundBoommedShip(playerChoice.X, playerChoice.Y, playerChoice.X, playerChoice.Y);

			ConsoleController::OutputScore("You", 30, 13, playerScore);
		}
		//check for player win

		while (true) {
			COORD botChoice = bot.Attack();
			bool botShot = Attack(botChoice, playerZone);
			ConsoleController::RenderMap(playerZone, botZone);

			if (botShot == false)
				break;

			bool isBoomed = playerZone.RecursiveCheckShip(botChoice.X, botChoice.Y, botChoice.X, botChoice.Y);
			if (isBoomed)
			{
				botScore += playerZone.RecursiveDesignateAroundBoommedShip(botChoice.X, botChoice.Y, botChoice.X, botChoice.Y);
				bot.ResetStage();

			}
			else {
				bot.UpStage();

			}
			Sleep(1500);

			ConsoleController::OutputScore("Bot", 2, 13, botScore);
		}
		//check for bot win

	}



	return Winner::Player;


}

bool GameController::Attack(COORD coord, Zone& zone) {
	if (zone.Get(coord.X, coord.Y) == Cell::IsShip)
	{
		zone.ChangeTo(coord.X, coord.Y, Cell::IsDead);
		return true;
	}
	else {
		zone.ChangeTo(coord.X, coord.Y, Cell::AroundShip);
		return false;
	}
}

