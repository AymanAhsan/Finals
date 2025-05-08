#pragma once
#include <iostream>
#include <string>
#include "character.h"
using namespace std;


// Player class inherits from character class
// Player represents You, character represents NPCs
// Player class has additional attributes and methods specific to the player
class player : public character
{
private:
	int pokecoins;
};

