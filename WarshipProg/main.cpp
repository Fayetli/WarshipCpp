#include "GameController.h"
#include <ctime>








int main() {
	//srand(time(NULL));
	ConsoleController::RevertHandle();
	GameController controller;
	controller.Start();


}