#include "ConsoleController.h"


void ConsoleController::SetPos(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void ConsoleController::SetPos(COORD coord) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void ConsoleController::RenderMap(const Zone& playerZone, const Zone& botZone) {
	using namespace std;

	COORD startPos;
	startPos.X = 2;
	startPos.Y = 2;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			SetPos(startPos.X + i*2, startPos.Y + j);
			cout << "* ";
		}
	}

	startPos.X = 30;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			SetPos(startPos.X + i * 2, startPos.Y + j);
			cout << "* ";
		}
	}
}


