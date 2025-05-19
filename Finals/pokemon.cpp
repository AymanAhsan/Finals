#include "Pokemon.h"
#include "Move.h"
#include "type.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "include/nlohmann/json.hpp"
#include <fstream> // For file handling

#include "Battle.h"

using namespace std;

void Pokemon::learnMove(Move* move) {
	if (moves.size() < 4) {
		moves.push_back(move);
	}
	else {
		char choice;
		cout << "Cannot learn more than 4 moves!" << endl;
		cout << "Would you like to replace a move (y/n)" << endl;
		cin >> choice;
		while (true) {
			if (choice == 'y' || choice == 'Y')
			{
				cout << "Choose a move to replace:" << endl;
				for (int i = 0; i < moves.size(); i++)
				{
					cout << i + 1 << ". " << moves[i]->getName() << endl;
				}
				int moveIndex;
				cin >> moveIndex;
				if (moveIndex > 0 && moveIndex <= moves.size())
				{
					delete moves[moveIndex - 1]; // Delete the old move
					moves[moveIndex - 1] = move; // Replace with the new move
					cout << "Move replaced!" << endl;
					_getch();
					break;
				}
				else
				{
					cout << "Invalid choice!" << endl;
				}
			}
		}
	}
}


void Pokemon::setupPokemon(Pokemon* pokemon, const std::string& pokemonFilePath, const std::string& movesJsonPath)
{
	try {
		// Read the JSON file
		std::ifstream file(pokemonFilePath);
		if (!file.is_open()) {
			std::cerr << "Could not open file: " << pokemonFilePath << std::endl;
			return;
		}

		// Parse the JSON
		nlohmann::json pokemonData;
		file >> pokemonData;

		// Get the pokemon's data by name  
		std::string name = pokemon->getName();
		if (!pokemonData.contains(name)) {
			std::cerr << "Pokemon " << name << " not found in JSON data" << std::endl;
			return;
		}

		auto& data = pokemonData[name];

		// Set the Pokemon's type
		if (data.contains("primaryType")) {
			std::cout << "Type: " << data["primaryType"] << std::endl;
			pokemon->setPrimaryType(stringToType(data["primaryType"]));
		}

		if (data.contains("secondaryType")) {
			pokemon->setSecondaryType(stringToType(data["secondaryType"]));
		}

		// Add the Pokemon's default moves
		if (data.contains("levelMoves")) {
			for (const auto& levelMove : data["levelMoves"]) {
				int requiredLevel = levelMove["level"];
				if (level >= requiredLevel) {  // Only if Pokémon's level is high enough
					std::string moveName = levelMove["move"];
					Move* newMove = Move::loadMoveFromJson(moveName, movesJsonPath);
					if (newMove) {
						pokemon->learnMove(newMove);
					}
				}
			}
		}

	}
	catch (const std::exception& e) {
		std::cerr << "Error parsing JSON: " << e.what() << std::endl;
	}
}
// Formula to calculate XP required for the next level
int Pokemon::calculateXPForLevel(int lvl) {
	// XP formula: 50 * level^2
	return static_cast<int>(50 * std::pow(lvl, 2));
}

void Pokemon::gainXP(int amount) {
	std::cout << name << " gained " << amount << " XP!\n";
	currentXP += amount;

	// Level up if enough XP
	while (currentXP >= xpToNextLevel) {
		levelUp();
	}

	std::cout << name << " is now at " << currentXP << " / " << xpToNextLevel << " XP.\n";
}

void Pokemon::levelUp() {
	currentXP -= xpToNextLevel;
	level++;
	std::cout << name << " leveled up! Now at level " << level << "!\n";
	xpToNextLevel = calculateXPForLevel(level + 1);
	// Optionally: increase stats here
}

bool Pokemon::useMove(int index, Pokemon& target)
{
	Move* move = moves[index];

	if (move->getPP() <= 0) {
		std::cout << name << " doesn't have enough PP to use " << move->getName() << "!" << std::endl;
		return false;
	}

	cout << name << " used " << move->getName() << "!" << endl;

	int damage = Battle::calculateDamage(*this, *move,target);
	target.takeDamage(damage);
	
	float effectiveness = Battle::calculateTypeEffectiveness(move->getType(), target);
	if (effectiveness > 1.0f) {
		std::cout << "It's super effective!" << std::endl;
	}
	else if (effectiveness < 1.0f && effectiveness > 0) {
		std::cout << "It's not very effective..." << std::endl;
	}
	else if (effectiveness == 0) {
		std::cout << "It had no effect..." << std::endl;
	}

	cout << target.getName() << " took " << damage << " damage!" << endl;

	move->use();
}

