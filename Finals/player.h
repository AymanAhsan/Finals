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
	void useElixers(Pokemon* pokemon){ // Method to use elixers
		if (Elixers > 0) {
			Elixers--;
			pokemon->restoreHealth(30);
			cout << "You used an elixer!" << endl;
		}
		else {
			cout << "You have no elixers!" << endl;
		}
	}
	void useFullHeals(){ // Method to use full heals
		if (FullHeals > 0) {
			FullHeals--;
			cout << "You used a full heal!" << endl;
		}
		else {
			cout << "You have no full heals!" << endl;
		}
	}
	void useFullRecoveries(){ // Method to use full recoveries
		if (FullRecoveries > 0) {
			FullRecoveries--;
			cout << "You used a full recovery!" << endl;
		}
		else {
			cout << "You have no full recoveries!" << endl;
		}
	}
	void usePokeballs(){ // Method to use pokeballs
		if (Pokeballs > 0) {
			Pokeballs--;
			cout << "You used a pokeball!" << endl;
		}
		else {
			cout << "You have no pokeballs!" << endl;
		}
	}
	void useMasterballs(){ // Method to use masterballs
		if (Masterballs > 0) {
			Masterballs--;
			cout << "You used a masterball!" << endl;
		}
		else {
			cout << "You have no masterballs!" << endl;
		}
	}
};

