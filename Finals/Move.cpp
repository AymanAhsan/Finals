#include "Move.h"
#include "type.h"
#include <fstream>
#include <iostream>
#include "include/nlohmann/json.hpp"

Move* Move::loadMoveFromJson(const std::string& moveName, const std::string& jsonFilePath) {
    static nlohmann::json moveData; // Cache to avoid repeated file reads
    static bool isLoaded = false;

    // Load the JSON file if not already loaded
    if (!isLoaded) {
        try {
            std::ifstream file(jsonFilePath);
            if (!file.is_open()) {
                std::cerr << "Could not open move file: " << jsonFilePath << std::endl;
                return nullptr;
            }
            file >> moveData;
            isLoaded = true;
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing moves JSON: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // Check if the move exists in our data
    if (!moveData.contains(moveName)) {
        std::cerr << "Move " << moveName << " not found in moves data" << std::endl;
        return nullptr;
    }

    // Get move data
    const auto& move = moveData[moveName];

    // Extract move properties
    Type moveType = stringToType(move["type"]);
    int power = move["power"];
    int accuracy = move["accuracy"];
    int pp = move["pp"];

    // Create and return a new Move
    return new Move(moveName, moveType, power, accuracy, pp);
}