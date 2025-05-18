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
	void Switch();
	void RunAway();
	void enemyAttack();

	static int calculateDamage(Pokemon& attacker, Move& move, Pokemon& target);
	static float calculateTypeEffectiveness(Type moveType, Pokemon& target);
	static float getTypeEffectiveness(Type attackType, Type defenderType);
};

