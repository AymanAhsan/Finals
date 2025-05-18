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
	int Elixers;
	int FullHeals;
	int FullRecoveries;
	int Pokeballs;
	int Masterballs;
public:
	Player() : pokecoins(0), badges(0) {} // Constructor to initialize pokecoins and badges
	void setPokecoins(int coins) { pokecoins = coins; } // Setter for pokecoins
	int getPokecoins() { return pokecoins; } // Getter for pokecoins
	void setBadges(int b) { badges = b; } // Setter for badges
	int getBadges() { return badges; } // Getter for badges
	int addPotions(int amount);
	int addElixers(int amount); // Method to add elixers
	int addFullHeals(int amount); // Method to add full heals
	int addFullRecoveries(int amount); // Method to add full recoveries
	int addPokeballs(int amount); // Method to add pokeballs
	int addMasterballs(int amount); // Method to add masterballs
	int getElixers() { return Elixers; } // Getter for elixers
	int getFullHeals() { return FullHeals; } // Getter for full heals
	int getFullRecoveries() { return FullRecoveries; } // Getter for full recoveries
	int getPokeballs() { return Pokeballs; } // Getter for pokeballs
	int getMasterballs() { return Masterballs; } // Getter for masterballs
};

