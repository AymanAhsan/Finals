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
	bool playerRan = false;
	static const float typeChart[18][18];
public:
	//Constructor
	Battle(Player& player, Character& enemy, string battleType = "trainer")
		: player(player), enemy(enemy), battleType(battleType) {
		playerActivePokemon = player.getPokemon(0);
		enemyActivePokemon = enemy.getPokemon(0);
	}

	/// Function to simulate a battle between two Pokemon
	bool start();
	void Fight();
	bool Bag();
	bool Potions();
	bool Pokeballs();
	bool Switch();
	bool RunAway();
	void enemyAttack();
	bool isPartyDefeated(Character& character);
	Pokemon* getNextAlivePokemon(Character& character);
	bool battleLoop();

	static int calculateDamage(Pokemon& attacker, Move& move, Pokemon& target);
	static float calculateTypeEffectiveness(Type moveType, Pokemon& target);
	static float getTypeEffectiveness(Type attackType, Type defenderType);
};

