#pragma once
#include <iostream>
#include <string>
#include "display.h"
#include "player.h"

using namespace std;
class Game
{
private:
	Display dispaly;
	Player player;
public:
	void startGame()
	{
		dispaly.displayMenu(player);
	}
	
};

