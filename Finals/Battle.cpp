#include "Battle.h"

#include <conio.h>

#include "Pokemon.h"


bool Battle::isPartyDefeated(Character& character) {
    // Check if all Pokemon in the party are defeated
    for (int i = 0; i < character.getPokemonCount(); i++) {
        if (character.getPokemon(i) != nullptr && character.getPokemon(i)->isAlive()) {
            return false;
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

bool Battle::battleLoop() {
    bool battleOver = false;
    bool playerWon = false;
    playerRan = false;

    // Initial Pokemon setup
    playerActivePokemon = getNextAlivePokemon(player);
    enemyActivePokemon = getNextAlivePokemon(enemy);

    cout << "A battle has begun between " << player.getName() << " and " << enemy.getName() << "!" << endl;
    cout << enemy.getName() << " sent out " << enemyActivePokemon->getName() << "!" << endl;
    cout << "Go, " << playerActivePokemon->getName() << "!" << endl;

    // Main battle loop
    while (!battleOver) {
        // Player's turn
        bool actionTaken = start(); // Player chooses an action

        if (playerRan)
        {
            battleOver = true;
        	playerWon = false;
            continue;
        }

        // Check if enemy Pokemon fainted
        if (!enemyActivePokemon->isAlive()) {
            cout << enemyActivePokemon->getName() << " fainted!" << endl;
			playerActivePokemon->gainXP(enemyActivePokemon->getLevel() * 10); // Gain experience for defeating an enemy Pokemon

            // Check if all enemy Pokemon are defeated
            if (isPartyDefeated(enemy)) {
                cout << player.getName() << " won the battle!" << endl;
                battleOver = true;
				playerWon = true;
                continue;
            }

            // Enemy sends out next Pokemon
            enemyActivePokemon = getNextAlivePokemon(enemy);
            cout << enemy.getName() << " sent out " << enemyActivePokemon->getName() << "!" << endl;
        }

        // Enemy's turn (only if battle isn't over already)
        if (!battleOver && actionTaken) {
            cout << endl << "--------- " << enemy.getName() << "'s Turn ---------" << endl;
            enemyAttack();

            // Check if player's Pokemon fainted
            if (!playerActivePokemon->isAlive()) {
                cout << playerActivePokemon->getName() << " fainted!" << endl;

                // Check if all player's Pokemon are defeated
                if (isPartyDefeated(player)) {
                    cout << enemy.getName() << " won the battle!" << endl;
                    battleOver = true;
                    playerWon = false;
                    continue;
                }

                // Player must choose next Pokemon
                cout << "Choose your next Pokemon:" << endl;
                Switch();
            }
        }
    }

    cout << "Battle ended!" << endl;
	return playerWon; // Return whether the player won or not
}

bool Battle::start()
{
    
    int choice;
	cout << endl << "--------- " << player.getName() << "'s Turn ---------" << endl;
	cout << playerActivePokemon->getName() << " HP: " << playerActivePokemon->getHealth() << "/" << playerActivePokemon->getMaxHealth() << endl;
	cout << enemyActivePokemon->getName() << " HP: " << enemyActivePokemon->getHealth() << "/" << enemyActivePokemon->getMaxHealth() << endl;
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
            return true;
        case 2:
			cout << "You chose to use an item!" << endl;
            return Bag();
            break;
		case 3:
            cout << "You chose to switch Pokemon!" << endl;
            Switch();
			break;
		case 4:
        cout << "You chose to run away!" << endl;
			if (RunAway())
			{
				playerRan = true;
			}
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            return start(); 
    }
    // Call the enemyAttack function to simulate the enemy's attack
    

}

void Battle::Fight() {
    int choice;
    cout << "Choose a move:" << endl;
    for (int i = 0; i < playerActivePokemon->getMoveCount(); i++) {
        cout << i + 1 << ": " << playerActivePokemon->getMove(i).getName() << endl;
    }
    cout << "5: Switch Pokemon" << endl;
    cin >> choice;
    if (choice == 5) {
        Fight();
    }
    else if (choice >= 1 && choice <= playerActivePokemon->getMoveCount()) {
        playerActivePokemon->useMove(choice - 1, *enemyActivePokemon);
    }
    else {
        cout << "Invalid move choice! Please try again." << endl;
        Fight();
    }
}

bool Battle::Switch()
{
    cout << "Which Pokemon would you like to switch to?" << endl;
    for (int i = 0; i < player.getPokemonCount(); i++) {
        cout << i + 1 << ": " << player.getPokemon(i)->getName() << endl;
    }
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= player.getPokemonCount()) {
		// Check if the chosen Pokemon is alive
        if (!player.getPokemon(choice - 1)->isAlive()) {
            cout << "This Pokemon is fainted, please choose another one." << endl;
            Switch();
            return false; // Return to the switch menu
		}
        // Check same pokemon
        if (player.getPokemon(choice - 1)->getName() == playerActivePokemon->getName())
        {
            cout << "cannot switch to the same pokemon";
            return false;
        } else
        {
            playerActivePokemon = player.getPokemon(choice - 1);
            cout << "Switched to " << playerActivePokemon->getName() << "!" << endl;
            return true;
        }
        
    }
    else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

bool Battle::RunAway()
{
    if (battleType == "wild" || battleType == "Wild")
    {
        cout << "You ran away!" << endl;
        _getch();
        return true;
    }
    else
    {
        cout << "You can't run away from a trainer battle!" << endl;
		_getch();
		return false;
    }
}



bool Battle::Bag() {
    bool itemUsed = false;
    while (!itemUsed) {
        int choice;
        cout << "1 = Potions" << endl;
        cout << "2 = Pokeballs" << endl;
        cout << "3 = Back" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            itemUsed = Potions();
            break;
        case 2:
            itemUsed = Pokeballs();
            break;
        case 3:
            return false;
        default:
            cout << "Invalid Input" << endl;
            break;
        }

        if (itemUsed) {
            return true; // Item was used, end turn
        }
    }
}

bool Battle::Potions() {
    while (true) {
        int elixers = player.getElixers();
        int fullHeals = player.getFullHeals();
        cout << "Elixers: " << elixers << "   ";
        cout << "Full Heals: " << fullHeals << endl << endl;
        cout << "Which potion will you use?" << endl;
        cout << "1 = Elixer" << endl;
        cout << "2 = Full Heal" << endl;
        cout << "3 = Back" << endl;
        int choosePotion;
        cin >> choosePotion;

        if (choosePotion == 1) {
            cout << "You have chosen an Elixer" << endl;
            player.useElixers(playerActivePokemon);
            _getch();
            return true; // Item was used, end turn
        }
        else if (choosePotion == 2) {
            if (fullHeals > 0) {
                cout << "You have chosen a Full heal";
                playerActivePokemon->restoreHealth(playerActivePokemon->getMaxHealth());
                player.useFullHeals();
                _getch();
                return true; // Item was used, end turn
            }
            else {
                cout << "You dont have enough of this item, please choose another option." << endl;
                _getch();
            }
        }
        else if (choosePotion == 3) {
            return false; // Return to bag menu
        }
        else {
            cout << "Invalid input" << endl;
            _getch();
        }
    }
}

bool Battle::Pokeballs() {
    while (true) { // Loop instead of recursion
        cout << "Pokeballs: " << player.getPokeballs() << endl;
        cout << "Masterballs: " << player.getMasterballs() << endl << endl;
        cout << "Which pokeball will you use?" << endl;
        cout << "1 = Pokeball" << endl;
        cout << "2 = Masterball" << endl;
        cout << "3 = Back" << endl;

        int chooseball;
        cin >> chooseball;

        if (chooseball == 1) {
            if (player.getPokeballs() > 0) {
                cout << "You have chosen a Pokeball" << endl;
                player.usePokeballs();
                _getch();
                return true; // Pokeball was used
            }
            else {
                cout << "You don't have enough of this item, please choose another option." << endl;
                _getch();
            }
        }
        else if (chooseball == 2) {
            if (player.getMasterballs() > 0) {
                cout << "You have chosen a Masterball" << endl;
                player.useMasterballs();
                _getch();
                return true; // Masterball was used
            }
            else {
                cout << "You don't have enough of this item, please choose another option." << endl;
                _getch();
            }
        }
        else if (chooseball == 3) {
            return false; // Return to bag menu
        }
        else {
            cout << "Invalid input. Please try again." << endl;
            _getch();
        }
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
	moveIndex = seed % enemyActivePokemon->getMoveCount();// Use the last move if less than 4 moves
	

    if (moveIndex >= 0 && moveIndex < enemyActivePokemon->getMoveCount()) {
        enemyActivePokemon->useMove(moveIndex, *playerActivePokemon);
    } else
    {
		cout << "Indexing went wrong: " << moveIndex << endl;
        enemyActivePokemon->useMove(0, *playerActivePokemon);
    }

}

