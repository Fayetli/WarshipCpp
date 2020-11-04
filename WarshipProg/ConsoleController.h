#pragma once
#include "Zone.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

static class ConsoleController
{
	static COORD _lastHandlePosition;
public:
	static void SetPos(int x, int y);
	static void SetPos(COORD coord);
	static void RenderMap(const Zone& playerZone, const Zone& botZone);
	static COORD Handle();
	static void AttackAnimation(COORD coord);
	static void AttackAnimation(size_t x, size_t y);
	static void OutputScore(std::string label, size_t x, size_t y, unsigned int score);
	static void OutputWinner(std::string winner);
	static void RevertHandle();
};

