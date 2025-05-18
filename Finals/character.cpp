#include "character.h"
#include <iostream>

using namespace std;

void Character::setName(string name)
{
	this->name = name;

}

string Character::getName()
{
	return name;
}

bool Character::addPokemon(Pokemon* pokemon)
{
	if (pokemonCount < 6)
	{
		pokemonParty[pokemonCount] = pokemon;
		pokemonCount++;
		return true;
	}
	else
	{
		cout << "Pokemon party is full!" << endl;
		return false;
	}
}

Pokemon* Character::getPokemon(int index)
{
	return pokemonParty[index];
}
