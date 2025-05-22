#include "display.h"
#include "player.h"
#include <iostream>
#include <string>
#include <conio.h> // https://cplusplus.com/forum/beginner/284909/
// Input reader
#include "pokemon.h"
#include <functional>

#include "Battle.h"
#include "include/nlohmann/json.hpp"
using namespace std;

// Choice handler function
int handleKeyInput(int& choice, int totalChoices, const std::function<void(int)>& renderChoices) {
	while (true) {
		int key = _getch();
		if (key == 72) { // Up arrow
			choice--;
			if (choice < 1)
				choice = totalChoices;

			renderChoices(choice);
		}
		else if (key == 80) { // Down arrow
			choice++;
			if (choice > totalChoices)
				choice = 1;
			renderChoices(choice);
		}
		else if (key == 13) { // Enter key
			return choice;
			
		}
	}
}

void Display::displayMenu(Player& player, Character& rival) {
	int choice = 1;
	const int totalChoices = 2;

	// Define the render function
	auto renderMenu = [](int currentChoice) {
		system("cls");
		cout << "                                  ,'\n";
		cout << "    _.----.        ____         ,'  _\\   ___    ___     ____\n";
		cout << "_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n";
		cout << "\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n";
		cout << " \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n";
		cout << "   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n";
		cout << "    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n";
		cout << "     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n";
		cout << "      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n";
		cout << "       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n";
		cout << "        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n";
		cout << "                                `'                            '-._|\n";
		cout << endl << endl << endl << endl;
		cout << "Welcome to Pokemon" << endl;
		//Ternary operator to check if the current choice is selected
		cout << (currentChoice == 1 ? "-> " : "   ") << "1. Start Game" << endl;
		cout << (currentChoice == 2 ? "-> " : "   ") << "2. End Game" << endl;
		};

	// Render the initial menu state
	renderMenu(choice);

	// Handle key input and menu navigation
	int result = handleKeyInput(choice, totalChoices, renderMenu);

	if (result == 1) {
		displayStart(player, rival);
	}
	else if (result == 2) {
		cout << "You have selected End Game" << endl;
		_getch();
		exit(0);
	}
}

void Display::displayStart(Player& player, Character& rival)
{
	system("cls");
	string name;
	cout << "Welcome to the world of Pokemon!" << endl;
	cout << "Hello, my name is Professor Maxwell, today marks the first day of your pokemon journey" << endl;
	cout << "First of all, what was your name again?" << endl;
	cin >> name;
	player.setName(name);
	cout << "Right! So it's " << player.getName() << "!" << endl;
	cout << "Are you ready to start your journey?" << endl;
	cout << "Press any key to continue..." << endl;
	_getch();
	 system("cls");
	cout << "You are now in the world of Pokemon!" << endl;
	cout << "First, you need to choose your starter Pokemon!" << endl;
	cout << "Press any key to continue..." << endl;
	_getch();
	system("cls");

	// Create starter Pokemon
// Change this part in displayStart function
// Create starter Pokemon with minimal initialization - stats will be set by setupPokemon
	Pokemon* turtwig = new Pokemon("Turtwig", 5);
	Pokemon* chimchar = new Pokemon("Chimchar", 5);
	Pokemon* piplup = new Pokemon("Piplup", 5);

	// Setup Pokemon data - this will load types, moves, and scale stats based on level
	turtwig->setupPokemon(turtwig, "pokemons.json", "moves.json");
	chimchar->setupPokemon(chimchar, "pokemons.json", "moves.json");
	piplup->setupPokemon(piplup, "pokemons.json", "moves.json");

	Pokemon* playerStarter = nullptr;
	Pokemon* rivalStarter = nullptr;
	Pokemon* notChose = nullptr;
	int choice = 1;
	int const total_choices = 3;
	auto renderChoices = [](int currentChoice)
		{
			system("cls");
			cout << "Choose your starter Pokemon!" << endl;
			cout << (currentChoice == 1 ? "-> " : "   ") << "1. Turtwig" << endl;
			cout << (currentChoice == 2 ? "-> " : "   ") << "2. Chimchar" << endl;
			cout << (currentChoice == 3 ? "-> " : "   ") << "3. Piplup" << endl;
		};
	
	renderChoices(choice);
	int key = handleKeyInput(choice, total_choices, renderChoices);

	if (key == 1)
	{
		cout << "You have selected Turtwig!" << endl;
		playerStarter = turtwig;
		rivalStarter = chimchar;
		notChose = piplup;
	}
	else if (key == 2)
	{
		cout << "You have selected Chimchar!" << endl;
		playerStarter = chimchar;
		rivalStarter = piplup;
		notChose = turtwig;
	}
	else if (key == 3)
	{
		cout << "You have selected Piplup!" << endl;
		playerStarter = piplup;
		rivalStarter = turtwig;
		notChose = chimchar;
	}
	else {
		cout << "Invalid choice, please try again." << endl;
	}

	//Removes the unused object from memory
	if (notChose != nullptr)
	{
		delete notChose;
		notChose = nullptr;
	}

	player.addPokemon(playerStarter);
	rival.addPokemon(rivalStarter);
	
	cout << "This is your friend " << rival.getName() << "!" << endl;
	_getch();
	cout << rival.getName() << ": Who is this guy" << endl;
	_getch();
	cout << "Professor Maxwell: This is " << player.getName() << ", your new friend!" << endl;
	_getch();
	cout << rival.getName() << ": This kid is not getting anywhere" << endl;
	_getch();
	cout << "Lets battle and see who is the really best" << endl;
	_getch();

	Battle rivalBattle(player, rival);
	// Determines if you win the rival battle or not
	if (rivalBattle.battleLoop() == true)
	{
		cout << "Looks like you've won this time, " << player.getName() << endl;
		_getch();
		cout << "But don't get too cocky" << endl;
	}  else
	{
		cout << "I've won as always" << endl;
		_getch();
	}

	cout << "Professor Maxwell: You have to train your Pokemon to be the best!" << endl;
	_getch();
	cout << "Professor Maxwell: You can now go out and explore the world!" << endl;
	_getch();
	cout << "Take some pokemons and potions with you!" << endl;
	_getch();
	player.addElixers(10);
	cout << "You have received 10 elixers!" << endl;
	_getch();
	player.addPokeballs(10);
	cout << "You have received 10 pokeballs!" << endl;

	cout << "Go out and catch some wild Pokemon!" << endl;
	
	displayPlayerMenu(player);
	// Fix battle bug tmrw
}

Pokemon* Display::createWildPokemon(Player& player) {
	// Get the player's active Pokemon level
	int playerLevel = player.getPokemon(0)->getLevel();

	// Define different tiers of Pokemon based on appropriate level ranges
	vector<string> tier1Pokemon = { "Caterpie", "Metapod", "Magikarp", "Ralts" };             // Level 1-15
	vector<string> tier2Pokemon = { "Butterfree", "Kirlia", "Fletchinder" };                  // Level 16-30
	vector<string> tier3Pokemon = { "Gyarados" };                                             // Level 31+

	// Choose the appropriate tier based on player level
	vector<string> availablePokemon;
	if (playerLevel < 16) {
		availablePokemon = tier1Pokemon;
	}
	else if (playerLevel < 31) {
		// At mid levels, can encounter both tier 1 and tier 2
		availablePokemon = tier1Pokemon;
		availablePokemon.insert(availablePokemon.end(), tier2Pokemon.begin(), tier2Pokemon.end());
	}
	else {
		// At high levels, can encounter all tiers
		availablePokemon = tier1Pokemon;
		availablePokemon.insert(availablePokemon.end(), tier2Pokemon.begin(), tier2Pokemon.end());
		availablePokemon.insert(availablePokemon.end(), tier3Pokemon.begin(), tier3Pokemon.end());
	}

	// Generate random index for Pokemon selection
	srand(static_cast<unsigned int>(time(nullptr)));
	int pokemonIndex = rand() % availablePokemon.size();

	// Generate wild Pokemon level (between 70% and 130% of player's level)
	int minLevel = max(1, static_cast<int>(playerLevel * 0.7));
	int maxLevel = max(2, static_cast<int>(playerLevel * 1.3));
	int wildLevel = minLevel + (rand() % (maxLevel - minLevel + 1));

	// Enforce minimum levels for certain evolutions
	string chosenPokemon = availablePokemon[pokemonIndex];
	if (chosenPokemon == "Metapod" && wildLevel < 7) wildLevel = 7;
	if (chosenPokemon == "Butterfree" && wildLevel < 10) wildLevel = 10;
	if (chosenPokemon == "Kirlia" && wildLevel < 20) wildLevel = 20;
	if (chosenPokemon == "Fletchinder" && wildLevel < 17) wildLevel = 17;
	if (chosenPokemon == "Gyarados" && wildLevel < 20) wildLevel = 20;

	// Create the wild Pokemon
	Pokemon* wildPokemon = new Pokemon(chosenPokemon, wildLevel);
	wildPokemon->setupPokemon(wildPokemon, "pokemons.json", "moves.json");

	return wildPokemon;
}
void Display::displayParty(Player& player) {
	system("cls");
	cout << "Your Pokemon:" << endl << endl;

	// Track valid Pokemon count for menu options
	int validPokemonCount = 0;
	for (int i = 0; i < player.getPokemonCount(); i++) {  // Loop through max party size (6)
		Pokemon* pokemon = player.getPokemon(i);
		cout << validPokemonCount + 1 << ": " << pokemon->getName() << " (Lvl "<< pokemon->getLevel() << ")" << endl;
	}

	if (validPokemonCount < 0) {
		cout << "You have no Pokemon in your party!" << endl;
		_getch();
		return;
	}

	cout << "\nSelect a Pokemon (or 0 to go back): ";
	int choice;
	cin >> choice;

	if (choice == 0) {
		return; // Go back to main menu
	}
	else if (choice > 0) {
		// Find the Pokemon that corresponds to the choice number
		Pokemon* chosenPokemon = nullptr;

		// https://www.geeksforgeeks.org/exception-handling-c/
		while (true) {
			try
			{
				chosenPokemon = player.getPokemon(choice - 1);
				break;
			}
			catch (exception e)
			{
				cout << "Invalid choice. Please try again." << endl;
			}
		}

		system("cls");
		cout << "Selected " << chosenPokemon->getName() << "!" << endl;
		cout << "HP: " << chosenPokemon->getHealth() << "/" << chosenPokemon->getMaxHealth() << endl << endl;
		cout << "What would you like to do with " << chosenPokemon->getName() << "?" << endl;
		cout << "1. Heal pokemon" << endl;
		cout << "2. Back" << endl;

		int pokemonChoice;
		cin >> pokemonChoice;

		if (pokemonChoice == 1) {
			chosenPokemon->restoreHealth(chosenPokemon->getMaxHealth());
			chosenPokemon->restoreMoves();
			cout << "Pokemon healed!" << endl;
			_getch();
		}
	}
	else {
		cout << "Invalid choice. Please try again." << endl;
		_getch();
	}
}
void Display::displayPlayerMenu(Player& player) {
	bool exitGame = false;

	while (!exitGame) {
		system("cls"); // Clear screen for better UI
		cout << "=== Pokemon Menu ===" << endl;
		cout << "1. Party" << endl;
		cout << "2. Battles" << endl;
		cout << "3. Bag" << endl;
		cout << "4. Shop" << endl;
		cout << "5. Exit Game" << endl;

		int choices = 0;
		cin >> choices;

		switch (choices) {
		case 1: {
			// Handle Party option
			system("cls");
			cout << "Party selected" << endl;
			displayParty(player);
			break;
		}

		case 2: {
			// Wild battle implementation
			system("cls");
			cout << "Battles selected" << endl;
			int chooseBattle;
			cout << "1. Wild Pokemon" << endl;
			cout << "2. Back" << endl;
			cin >> chooseBattle;
			if (chooseBattle == 1) {
				// Create a wild Pokemon
				Pokemon* wildPokemon = createWildPokemon(player);

				// Create a temporary character to hold the wild Pokemon
				Character wildTrainer;
				wildTrainer.setName(wildPokemon->getName());
				wildTrainer.addPokemon(wildPokemon);

 				cout << "A wild " << wildPokemon->getName() << " (Level " << wildPokemon->getLevel() << ") appeared!" << endl;
				_getch();

				// Create and start the battle
				Battle wildBattle(player, wildTrainer, "wild");
				bool playerWon = wildBattle.battleLoop();

				if (playerWon) {
					cout << "You defeated the wild " << wildPokemon->getName() << "!" << endl;
					// Give player some rewards
					player.setPokecoins(player.getPokecoins() + wildPokemon->getLevel() * 5);
					cout << "You earned " << wildPokemon->getLevel() * 5 << " Pokecoins!" << endl;
				}
				else {
					cout << "You were defeated by the wild " << wildPokemon->getName() << "!" << endl;
					cout << "You rush back to the nearest Pokemon Center..." << endl;
					// Heal all player Pokemon
					for (int i = 0; i < player.getPokemonCount(); i++) {
						player.getPokemon(i)->restoreHealth(player.getPokemon(i)->getMaxHealth());
						player.getPokemon(i)->restoreMoves();
					}
					displayPlayerMenu(player);
				}
				_getch();
			}
			break;
		}

		case 3: {
			// Handle Bag option
			system("cls");
			cout << "Bag selected" << endl;
			cout << "Pokeballs: " << player.getPokeballs() << endl;
			cout << "Masterballs: " << player.getMasterballs() << endl;
			cout << "Elixers: " << player.getElixers() << endl;
			cout << "Full Heals: " << player.getFullHeals() << endl;
			cout << "Pokecoins: " << player.getPokecoins() << endl;
			cout << "\nPress any key to continue..." << endl;
			_getch();
			break;
		}

		case 4: {
			// Handle Shop option
			system("cls");
			cout << "Shop selected" << endl;
			cout << "Your Pokecoins: " << player.getPokecoins() << endl << endl;
			cout << "What would you like to purchase" << endl;
			cout << "1. Pokeballs: 10 Coins" << endl;
			cout << "2. Potions: 10 coins" << endl;
			cout << "3. Back" << endl;

			int choice = 0;
			cin >> choice;

			if (choice == 1) {
				int amt;
				cout << "How many Pokeballs would you like to purchase" << endl;
				cin >> amt;
				if (player.getPokecoins() >= amt * 10) {
					player.addPokeballs(amt);
					player.setPokecoins(player.getPokecoins() - amt * 10);
					cout << "Purchased " << amt << " of Pokeballs" << endl;
				}
				else {
					cout << "Not enough pokecoins" << endl;
				}
				_getch();
			}
			else if (choice == 2) {
				int amt;
				cout << "How many potions would you like to purchase" << endl;
				cin >> amt;
				if (player.getPokecoins() >= amt * 10) {
					player.addPotions(amt);
					player.setPokecoins(player.getPokecoins() - amt * 10);
					cout << "Purchased " << amt << " of Potions" << endl;
				}
				else {
					cout << "Not enough pokecoins" << endl;
				}
				_getch();
			}
			break;
		}

		case 5: {
			// Exit game option
			cout << "Thanks for playing!" << endl;
			_getch();
			exitGame = true;
			break;
		}

		default:
			cout << "Invalid choice. Please select 1-5." << endl;
			_getch();
			break;
		}
	}
}