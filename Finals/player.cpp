#include "player.h"
#include "pokemon.h"
#include <iostream>
#include <string>


#include "player.h"

int Player::addPotions(int amount) {
    FullHeals += amount;
    return FullHeals;
}

int Player::addElixers(int amount) {
    Elixers += amount;
    return Elixers;
}

int Player::addFullHeals(int amount) {
    FullHeals += amount;
    return FullHeals;
}

int Player::addFullRecoveries(int amount) {
    FullRecoveries += amount;
    return FullRecoveries;
}

int Player::addPokeballs(int amount) {
    Pokeballs += amount;
    return Pokeballs;
}

int Player::addMasterballs(int amount) {
    Masterballs += amount;
    return Masterballs;
}