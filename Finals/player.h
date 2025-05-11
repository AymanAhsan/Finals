#pragma once
#include <iostream>
#include <string>
#include "character.h"
#include "pokemon.h"
using namespace std;


// Player class inherits from character class
// Player represents You, character represents NPCs
// Player class has additional attributes and methods specific to the player
class Player : public Character
{
private:
	int pokecoins;
	int badges;
public:
	Player() : pokecoins(0), badges(0) {} // Constructor to initialize pokecoins and badges
	void setPokecoins(int coins) { pokecoins = coins; } // Setter for pokecoins
	int getPokecoins() { return pokecoins; } // Getter for pokecoins
	void setBadges(int b) { badges = b; } // Setter for badges
	int getBadges() { return badges; } // Getter for badges
};

