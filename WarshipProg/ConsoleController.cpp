#include "ConsoleController.h"

typedef Zone::Cell Cell;

COORD ConsoleController::_lastHandlePosition;

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
			switch (playerZone.Get(i, j)) {
			case Cell::IsShip:
				cout << "* ";
				break;
			case Cell::IsDead:
				cout << "X ";
				break;
			case Cell::AroundShip:
				cout << "# ";
				break;
			default:
				cout << "0 ";
				break;
			}
		}
	}

	startPos.X = 30;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			SetPos(startPos.X + i * 2, startPos.Y + j);
			switch (botZone.Get(i, j)) {
			case Cell::IsShip:
				cout << "0 ";
				break;
			case Cell::IsDead:
				cout << "X ";
				break;
			case Cell::AroundShip:
				cout << "# ";
				break;
			default:
				cout << "0 ";
				break;
			}
		}
	}
}

COORD ConsoleController::Handle()
{
	COORD minPos;
	minPos.X = 30;
	minPos.Y = 2;

	COORD maxPos;
	maxPos.X = 48;
	maxPos.Y = 11;

	COORD Pos = _lastHandlePosition;

	SetPos(Pos);
	
	bool check = true;
	while (check) {
		Sleep(5);
		char act = _getch();
		int ch = static_cast<int>(act);
		
		switch (ch) {
		case 13://enter
			check = false;
			break;
		case 75://left
			if(Pos.X != minPos.X)
				Pos.X -= 2;
			break;
		case 77://right
			if (Pos.X != maxPos.X)
				Pos.X += 2;

			break;
		case 80://down
			if (Pos.Y != maxPos.Y)
				Pos.Y += 1;
			break;
		case 72://up
			if (Pos.Y != minPos.Y)
				Pos.Y -= 1;

			break;
		}


		SetPos(Pos);
	}

	COORD choice;
	choice.X = (Pos.X - minPos.X)/2;
	choice.Y = (Pos.Y - minPos.Y);

	_lastHandlePosition = Pos;
	ConsoleController::AttackAnimation(Pos);

	/*SetPos(0, 0);
	std::cout << "ChoiceX: " << choice.X << std::endl;
	std::cout << "ChoiceY: " << choice.Y << std::endl;*/

	return choice;
}

void ConsoleController::AttackAnimation(COORD coord)
{
	using namespace std;

	for (int i = 0; i < 10; i++) {
		SetPos(coord);
		cout << i;
		Sleep(25);
	}
}

void ConsoleController::AttackAnimation(size_t x, size_t y)
{
	using namespace std;

	COORD coord;
	coord.X = x;
	coord.Y = y;

	for (int i = 0; i < 10; i++) {
		SetPos(coord);
		cout << i;
		Sleep(25);
	}
}

void ConsoleController::OutputScore(std::string label, size_t x, size_t y, unsigned int score) {
	using namespace std;

	SetPos(x, y);
	cout << label << ": " << score;
}

void ConsoleController::OutputWinner(std::string winner)
{
	SetPos(2, 15);
	std::cout << winner << " win this game!";
}

void ConsoleController::RevertHandle()
{
	_lastHandlePosition.X = 30;
	_lastHandlePosition.Y = 2;
}


