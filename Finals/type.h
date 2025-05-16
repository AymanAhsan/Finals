#pragma once

// Type.h
#pragma once
#include <string>

enum class Type {
    NORMAL, FIRE, WATER, GRASS, ELECTRIC,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON,
    DARK, STEEL, FAIRY, NONE // NONE for moves or Pokémon without a specific type
};

// Helper function to convert Type to string
inline Type stringToType(const std::string& str) {
    if (str == "Normal") return Type::NORMAL;
    if (str == "Fire") return Type::FIRE;
    if (str == "Water") return Type::WATER;
    if (str == "Grass") return Type::GRASS;
    if (str == "Electric") return Type::ELECTRIC;
    if (str == "Ice") return Type::ICE;
    if (str == "Fighting") return Type::FIGHTING;
    if (str == "Poison") return Type::POISON;
    if (str == "Ground") return Type::GROUND;
    if (str == "Flying") return Type::FLYING;
    if (str == "Psychic") return Type::PSYCHIC;
    if (str == "Bug") return Type::BUG;
    if (str == "Rock") return Type::ROCK;
    if (str == "Ghost") return Type::GHOST;
    if (str == "Dragon") return Type::DRAGON;
    if (str == "Dark") return Type::DARK;
    if (str == "Steel") return Type::STEEL;
    if (str == "Fairy") return Type::FAIRY;
    return Type::NONE;
}
