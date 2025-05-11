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
inline std::string typeToString(Type type) {
    switch (type) {
    case Type::NORMAL: return "Normal";
    case Type::FIRE: return "Fire";
    case Type::WATER: return "Water";
    case Type::GRASS: return "Grass";
    case Type::ELECTRIC: return "Electric";
    case Type::ICE: return "Ice";
    case Type::FIGHTING: return "Fighting";
    case Type::POISON: return "Poison";
    case Type::GROUND: return "Ground";
    case Type::FLYING: return "Flying";
    case Type::PSYCHIC: return "Psychic";
    case Type::BUG: return "Bug";
    case Type::ROCK: return "Rock";
    case Type::GHOST: return "Ghost";
    case Type::DRAGON: return "Dragon";
    case Type::DARK: return "Dark";
    case Type::STEEL: return "Steel";
    case Type::FAIRY: return "Fairy";
    case Type::NONE: return "None";
    default: return "Unknown";
    }
}