#pragma once
#include "Zone.h"
#include <iostream>
#include <windows.h>

static class ConsoleController
{

public:
	static void SetPos(int x, int y);
	static void SetPos(COORD coord);
	static void RenderMap(const Zone& playerZone, const Zone& botZone);
};

