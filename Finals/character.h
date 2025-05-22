#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "pokemon.h"

using namespace std;
class Character
{
private:
	string name;
	vector<Pokemon*> pokemonParty;
	int pokemonCount;
public:
	Character() : pokemonCount(0)
	{
	} // Default constructor to initialize pokemonCount and pokemonParty
	Pokemon* getPokemon(int index);
	bool addPokemon(Pokemon* pokemon); // Method to add a Pokemon to the party
	void setName(string name);
	string getName();
	int getPokemonCount() { return pokemonParty.size(); }

};

