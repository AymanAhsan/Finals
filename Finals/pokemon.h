#pragma once
#include <iostream>
#include <string>
#include "Move.h"
#include "type.h"
#include <vector>
#include "include/nlohmann/json.hpp"
using namespace std;

class Pokemon
{
private:
	string name;
	int level;
	int health;
	int maxHealth;
	int attackPower;
	int defensePower;
	int speed;
	vector<Move*> moves; // Vector to hold moves
	Type primaryType;
	Type secondaryType;
	int currentXP;
	int xpToNextLevel;
public:
	Pokemon(string name, int level)
		: name(name), level(level), health(10), maxHealth(10),
		attackPower(5), defensePower(5), speed(5),
		primaryType(Type::NONE), secondaryType(Type::NONE) {
		currentXP = 0;
		xpToNextLevel = calculateXPForLevel(level + 1);
	}
	string getName() { return name; }
	int getLevel() { return level; }
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	int getAttackPower() { return attackPower; }
	int getDefensePower() { return defensePower; }
	int getMoveCount() { return moves.size(); } // Get the number of moves
	int getSpeed() { return speed; }
	Move getMove(int index) { return *moves[index]; }
	void setName(string name) { this->name = name; }
	void setLevel(int level) { this->level = level; }
	void setHealth(int health) { this->health = health; }
	void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
	void setAttackPower(int attackPower) { this->attackPower = attackPower; }
	void setDefensePower(int defensePower) { this->defensePower = defensePower; }
	void setSpeed(int speed) { this->speed = speed; }
	void setPrimaryType(Type type) { primaryType = type; }
	void setSecondaryType(Type type) { secondaryType = type; }
	Type getPrimaryType() { return primaryType; }
	Type getSecondaryType() { return secondaryType; }
	void learnMove(Move* move);
	bool isAlive() { return health > 0; } // Check if the Pokemon is alive
	bool useMove(int index, Pokemon& target);
	void takeDamage(int damage) {
		health -= damage;
		if (health < 0) {
			health = 0; // Ensure health doesn't go below 0
		}
	}
	void restoreHealth(int amount) {
		health += amount;
		if (health > maxHealth) {
			health = maxHealth; // Ensure health doesn't exceed maxHealth
		}
	}

	void restoreMoves(){
		for(auto moves: moves){
			moves->restorePP();
		}
	}

	void setupPokemon(Pokemon* pokemon, const std::string& pokemonFilePath, const std::string& movesJsonPath);
	int calculateXPForLevel(int lvl);
	void gainXP(int amount);
	void levelUp();
	void printStatus();
};

