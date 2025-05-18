#include "Battle.h"
#include "Pokemon.h"


bool Battle::isPartyDefeated(Character& character) {
    // Check if all Pokemon in the party are defeated
    for (int i = 0; i < character.getPokemonCount(); i++) {
        if (character.getPokemon(i)->isAlive()) {
            return false; // At least one Pokemon is still alive
        }
    }
    return true; // All Pokemon are defeated
}

Pokemon* Battle::getNextAlivePokemon(Character& character) {
    // Find the next available Pokemon that's still alive
    for (int i = 0; i < character.getPokemonCount(); i++) {
        if (character.getPokemon(i)->isAlive()) {
            return character.getPokemon(i);
        }
    }
    return nullptr; // No alive Pokemon found
}

void Battle::battleLoop() {
    bool battleOver = false;

    // Initial Pokemon setup
    playerActivePokemon = getNextAlivePokemon(player);
    enemyActivePokemon = getNextAlivePokemon(enemy);

    cout << "A battle has begun between " << player.getName() << " and " << enemy.getName() << "!" << endl;
    cout << enemy.getName() << " sent out " << enemyActivePokemon->getName() << "!" << endl;
    cout << "Go, " << playerActivePokemon->getName() << "!" << endl;

    // Main battle loop
    while (!battleOver) {
        // Player's turn
        cout << endl << "--------- " << player.getName() << "'s Turn ---------" << endl;
        start(); // Player chooses an action

        // Check if enemy Pokemon fainted
        if (!enemyActivePokemon->isAlive()) {
            cout << enemyActivePokemon->getName() << " fainted!" << endl;

            // Check if all enemy Pokemon are defeated
            if (isPartyDefeated(enemy)) {
                cout << player.getName() << " won the battle!" << endl;
                battleOver = true;
                continue;
            }

            // Enemy sends out next Pokemon
            enemyActivePokemon = getNextAlivePokemon(enemy);
            cout << enemy.getName() << " sent out " << enemyActivePokemon->getName() << "!" << endl;
        }

        // Enemy's turn (only if battle isn't over already)
        if (!battleOver) {
            cout << endl << "--------- " << enemy.getName() << "'s Turn ---------" << endl;
            enemyAttack();

            // Check if player's Pokemon fainted
            if (!playerActivePokemon->isAlive()) {
                cout << playerActivePokemon->getName() << " fainted!" << endl;

                // Check if all player's Pokemon are defeated
                if (isPartyDefeated(player)) {
                    cout << enemy.getName() << " won the battle!" << endl;
                    battleOver = true;
                    continue;
                }

                // Player must choose next Pokemon
                cout << "Choose your next Pokemon:" << endl;
                Switch();
            }
        }
    }

    cout << "Battle ended!" << endl;
}

void Battle::start()
{
    
    int choice;
    cout << "What will " << playerActivePokemon->getName() << " do?" << endl;
    cout << "1 = Attack" << endl;
    cout << "2 = Bag" << endl;
    cout << "3 = Switch Pokemon" << endl;
    cout << "4 = Run Away" << endl;

    cin >> choice;
	switch (choice) {
        case 1:
			cout << "You chose to attack!" << endl;
            Fight();
			break;
        case 2:
			cout << "You chose to use an item!" << endl;
            break;
		case 3:
            cout << "You chose to switch Pokemon!" << endl;
			break;
		case 4:
        cout << "You chose to run away!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
    // Call the enemyAttack function to simulate the enemy's attack
    

}

void Battle::Fight()
{
    int choice;
	cout << "Choose a move:" << endl;
    for (int i = 0; i < playerActivePokemon->getMoveCount(); i++) {
        cout << i + 1 << ": " << playerActivePokemon->getMove(i).getName() << endl;
	}
	cout << "5: Switch Pokemon" << endl;
    cin >> choice;
    if (choice == 5)
    {
        Fight();
    } else
    {
        playerActivePokemon->useMove(choice, *enemyActivePokemon);
    }
}

void Battle::Switch()
{
	cout << "Which Pokemon would you like to switch to?" << endl;
    for (int i = 0; i < player.getPokemonCount(); i++) {
        cout << i + 1 << ": " << player.getPokemon(i)->getName() << endl;
    }
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= player.getPokemonCount()) {
        playerActivePokemon = player.getPokemon(choice - 1);
        cout << "Switched to " << playerActivePokemon->getName() << "!" << endl;
    } else {
        cout << "Invalid choice. Please try again." << endl;
	}
}

void Battle::RunAway()
{
	if (battleType == "wild")
	{
		cout << "You ran away!" << endl;
	} else
	{
		cout << "You can't run away from a trainer battle!" << endl;
	}
}



// Initialize the static type chart
const float Battle::typeChart[18][18] = {
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
    // https://pokemondb.net/type - Effectiveness chart
    // I used claude to generate the table aint no way im doing all that lol
    // Return the appropriate effectiveness value from the chart
};

float Battle::getTypeEffectiveness(Type attackType, Type defenderType) {
    // Return the appropriate effectiveness value from the chart
    return typeChart[static_cast<int>(attackType)][static_cast<int>(defenderType)];
}

float Battle::calculateTypeEffectiveness(Type moveType, Pokemon& target) {
    Type attackType = moveType;
    Type defenderType1 = target.getPrimaryType();
    Type defenderType2 = target.getSecondaryType();

    float effectiveness = 1.0f;

    effectiveness *= getTypeEffectiveness(attackType, defenderType1);
    // Check if the defender has a secondary type
    if (defenderType2 != Type::NONE) {
        effectiveness *= getTypeEffectiveness(attackType, defenderType2);
    }

    return effectiveness;
}

int Battle::calculateDamage(Pokemon& attacker, Move& move, Pokemon& target) {
    float typeEffectiveness = calculateTypeEffectiveness(move.getType(), target);

    // Calculate STAB (Same Type Attack Bonus)
    float stab = 1.0f;
    if (move.getType() == attacker.getPrimaryType() ||
        move.getType() == attacker.getSecondaryType()) {
        stab = 1.5f; // 50% boost when move type matches Pokémon's type
    }

    // Standard Pokémon damage formula
    int baseDamage = (2 * attacker.getLevel() / 5 + 2) * move.getPower() *
        attacker.getAttackPower() / target.getDefensePower() / 50 + 2;

    return static_cast<int>(baseDamage * typeEffectiveness * stab);
}

void Battle::enemyAttack() {
	int seed = time(0);

	// LCG parameters
	const int a = 1664525;
	const int c = 1013904223;
	const long long m = 4294967296;

	seed = (a * seed + c) % m;  // LCG formula
    int moveIndex;
    if (enemyActivePokemon->getMoveCount() < 4){
        moveIndex = seed % enemyActivePokemon->getMoveCount();// Use the last move if less than 4 moves
	} else
	{
        moveIndex = seed % 4;
	}

    enemyActivePokemon->useMove(moveIndex, *playerActivePokemon);
}

