#pragma once
#include <iostream>
#include <string>
#include "display.h"
#include "player.h"
#include "character.h"

using namespace std;
class Game
{
private:
	Display dispaly;
	Player player;
	Character rival;
public:
	Game() : rival()
	{
		rival.setName("Barry");
	}

	void startGame()
	{
		dispaly.displayMenu(player, rival);
	}

	Character& getRival() { return rival; }
};

