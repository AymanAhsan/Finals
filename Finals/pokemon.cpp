#include "Pokemon.h"
#include "Move.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 

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

int Pokemon::calculateDamage(int damage, Pokemon& target)
{
	float typeEffectiveness = calculateTypeEffectiveness(move.getType(), target);
	float stab = 1.0f; // Same Type Attack Bonus - 1.5 if move type matches Pokémon type

	int baseDamage = (2 * level / 5 + 2) * move.getPower() * attackPower / target.getDefensePower() / 50 + 2;

	return static_cast<int>(baseDamage * typeEffectiveness * stab);
}

float Pokemon::calculateTypeEffectiveness(Type moveType, Pokemon& target)
{
	Type attackType = static_cast<Type>(moveType);
	Type defenderType1 = target.getPrimaryType();
	Type defenderType2 = target.getSecondaryType();

	float effectiveness = 1.0f;

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