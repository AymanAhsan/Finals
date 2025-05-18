#include <iostream>
#include "Battle.h"
#include "game.h"




int main() {
	Player me;
	Character rival;
	Pokemon* turtwig = new Pokemon("Turtwig", 5, 20, 20, 10, 5, 5);
	Pokemon* chimchar = new Pokemon("Chimchar", 5, 20, 20, 10, 5, 5);


	turtwig->setupPokemon(turtwig, "pokemons.json", "moves.json");
	chimchar->setupPokemon(chimchar, "pokemons.json", "moves.json");
	me.addPokemon(turtwig);
	rival.addPokemon(chimchar);

	Battle battle(me, rival);

	battle.battleLoop();

	return 0;

}