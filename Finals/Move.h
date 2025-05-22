// move.h
#pragma once
#include <iostream>
#include <string>
#include "type.h"



using namespace std;


class Move {
private:
    string name;
    Type type;
    int power;
    int accuracy;
    int pp;
    int maxPP;
    string description;

public:
    Move(string name, Type type, int power, int accuracy, int pp)
        : name(name), type(type), power(power), accuracy(accuracy), pp(pp), maxPP(pp) {
    }

    // Getters
    string getName() const { return name; }
	Type getType() const { return type; }
    int getPower() const { return power; }
    int getAccuracy() const { return accuracy; }
    int getPP() const { return pp; }
    int getMaxPP() const { return maxPP; }
    void decreasePP() { pp--; }
    string getDescription() const { return description; }
    static Move* loadMoveFromJson(const std::string& moveName, const std::string& jsonFilePath);

    // Setters
    void setPP(int newPP)
    {
		if (newPP > maxPP) {
			pp = maxPP;
		}
		else {
			pp = newPP;
		}
    }

    // Use move
    bool use() {
        if (pp > 0) {
            pp--;
            return true;
        }
        return false; // Out of PP
    }

    // Restore PP
    void restorePP(int amount = -1) {
        pp = maxPP;
    }
};