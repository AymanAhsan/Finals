#include "Pokemon.h"
#include "Move.h"
#include "type.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "include/nlohmann/json.hpp"
#include <fstream> // For file handling

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

int Pokemon::calculateDamage(Move move, Pokemon& target)
{
	float typeEffectiveness = calculateTypeEffectiveness(move.getType(), target);
	float stab = 1.0f; // Same Type Attack Bonus - 1.5 if move type matches Pokémon type
	// Standard pokemon calculation)
	int baseDamage = (2 * level / 5 + 2) * move.getPower() * attackPower / target.getDefensePower() / 50 + 2;

	return static_cast<int>(baseDamage * typeEffectiveness * stab);
}

float Pokemon::calculateTypeEffectiveness(Type moveType, Pokemon& target)
{
	Type attackType = moveType;
	Type defenderType1 = target.getPrimaryType();
	Type defenderType2 = target.getSecondaryType();

	float effectiveness = 1.0f;

	effectiveness *= getTypeEffectiveness(attackType, defenderType1);
	// Check if the defender has a secondary type
	if (defenderType2 != Type::NONE) {
		effectiveness *= getTypeEffectiveness(attackType, defenderType2);
	}

	return effectiveness;

}

float Pokemon::getTypeEffectiveness(Type attackType, Type defenderType) {
	// Effectiveness chart represented as a 2D array
	// 2.0 = super effective, 1.0 = normal effectiveness, 0.5 = not very effective, 0.0 = no effect

	// Initialize all matchups to 1.0 (normal effectiveness)
	static const float typeChart[18][18] = {
		// NOR  FIR  WAT  ELE  GRA  ICE  FIG  POI  GRO  FLY  PSY  BUG  ROC  GHO  DRA  DAR  STE  FAI
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f}, // NORMAL
		{1.0f, 0.5f, 0.5f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f}, // FIRE
		{1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f}, // WATER
		{1.0f, 1.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f}, // ELECTRIC
		{1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 0.5f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f}, // GRASS
		{1.0f, 0.5f, 0.5f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f}, // ICE
		{2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 0.5f, 0.5f, 2.0f, 0.0f, 1.0f, 2.0f, 2.0f, 0.5f}, // FIGHTING
		{1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 2.0f}, // POISON
		{1.0f, 2.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f}, // GROUND
		{1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f}, // FLYING
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f}, // PSYCHIC
		{1.0f, 0.5f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 2.0f, 0.5f, 0.5f}, // BUG
		{1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f}, // ROCK
		{0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f}, // GHOST
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.0f}, // DRAGON
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f}, // DARK
		{1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.5f, 2.0f}, // STEEL
		{1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 0.5f, 1.0f}  // FAIRY
	};
	// https://pokemondb.net/type - Effectiveness chart
	// I used claude to generate the table aint no way im doing all that lol
	// Return the appropriate effectiveness value from the chart
	return typeChart[static_cast<int>(attackType)][static_cast<int>(defenderType)];
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

void Pokemon::printStatus() const {
	std::cout << "Name: " << name << ", Level: " << level
		<< ", XP: " << currentXP << " / " << xpToNextLevel << "\n";
}
