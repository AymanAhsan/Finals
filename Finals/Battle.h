#pragma once
#include "Pokemon.h"
class Battle
{
private:
	static const float typeChart[18][18];
public:
	static int calculateDamage(Pokemon& attacker, Move& move, Pokemon& target);
	static float calculateTypeEffectiveness(Type moveType, Pokemon& target);
	static float getTypeEffectiveness(Type attackType, Type defenderType);
};

