#pragma once
#include <iostream>
#include <string>
#include "pokemon.h"

using namespace std;
class character
{
private:
	string name;
	pokemon* pokemonParty[6]; // Array of pointers to pokemon objects 
public:
	void setName(string name);
	string getName();
};

