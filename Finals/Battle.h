#pragma once
#include "Pokemon.h"
#include "character.h"
#include "player.h"

class Battle
{
private:
	Player& player;
	Character& enemy;
	Pokemon* playerActivePokemon; // Use pointers instead of references
	Pokemon* enemyActivePokemon;  // so they can be updated during battle
	string battleType;
	string battleOutcome;
	static const float typeChart[18][18];
public:
	//Constructor
	Battle(Player& player, Character& enemy) : player(player), enemy(enemy) {
		playerActivePokemon = player.getPokemon(0); // Gets first pokemon
		enemyActivePokemon = enemy.getPokemon(0); 
	}

	/// Function to simulate a battle between two Pokemon
	void start();
	void Fight();
	void Bag();
	bool Potions();
	bool Pokeballs();
	void Switch();
	void RunAway();
	void enemyAttack();
	bool isPartyDefeated(Character& character);
	Pokemon* getNextAlivePokemon(Character& character);
	bool battleLoop();

	static int calculateDamage(Pokemon& attacker, Move& move, Pokemon& target);
	static float calculateTypeEffectiveness(Type moveType, Pokemon& target);
	static float getTypeEffectiveness(Type attackType, Type defenderType);
};

