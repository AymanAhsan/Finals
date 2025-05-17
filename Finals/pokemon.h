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
	vector<Move*> moves;
	Type primaryType;
	Type secondaryType;
	int currentXP;
	int xpToNextLevel;
public:
	Pokemon(string name, int level, int health, int maxHealth, int attackPower, int defensePower, int speed)
		: name(name), level(level), health(health), maxHealth(maxHealth), attackPower(attackPower), defensePower(defensePower), speed(speed) {
	}
	string getName() { return name; }
	int getLevel() { return level; }
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	int getAttackPower() { return attackPower; }
	int getDefensePower() { return defensePower; }
	int getSpeed() { return speed; }
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
	int calculateDamage(Move move, Pokemon& target);
	float getTypeEffectiveness(Type attackType, Type defenderType);
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
	float calculateTypeEffectiveness(Type moveType, Pokemon& target);

	void setupPokemon(Pokemon* pokemon, const std::string& pokemonFilePath, const std::string& movesJsonPath);
	int calculateXPForLevel(int lvl);
	void gainXP(int amount);
	void levelUp();
	void printStatus();
};

