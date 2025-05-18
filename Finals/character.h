#pragma once
#include <iostream>
#include <string>
#include "pokemon.h"

using namespace std;
class Character
{
private:
	string name;
	Pokemon* pokemonParty[6]; // Array of pointers to pokemon objects
	int pokemonCount;
public:
	Character() : pokemonCount(0)
	{
		for (int i = 0; i < 6; i++)
		{
			pokemonParty[i] = nullptr; // Initialize all pointers to nullptr
		}
	} // Default constructor to initialize pokemonCount and pokemonParty
	Pokemon* getPokemon(int index);
	bool addPokemon(Pokemon* pokemon); // Method to add a Pokemon to the party
	void setName(string name);
	string getName();
};

