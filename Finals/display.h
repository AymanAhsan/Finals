#pragma once
#include <iostream>
#include <string>
#include "player.h"
#include "character.h"
class Display
{
public:
	void displayMenu(Player& player, Character& rival);
	void displayStart(Player& player, Character& rival);
	void displayPlayerMenu(Player& player);
	void displayParty(Player& player);
	void displayBattle(Player& player);
	void displayUtil(Player& player);
};

