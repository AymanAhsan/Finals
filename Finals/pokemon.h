#pragma once
#include <iostream>
#include <string>
using namespace std;

class pokemon
{
private:
	string name;
	int level;
	int health;
	int maxHealth;
	int attackPower;
	int defensePower;
	int speed;
public:
	pokemon(string name, int level, int health, int maxHealth, int attackPower, int defensePower, int speed)
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
};

