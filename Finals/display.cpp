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

void Display::displayParty(Player& player){
	Pokemon* chosenPokemon;
	for (int i = 0; i < player.getPokemonCount(); i++) {
		cout << i + 1 << ": " << player.getPokemon(i)->getName() << endl;
	}
	int choice;
	cin >> choice;
	if (choice > 0 && choice <= player.getPokemonCount()) {
		int pokemonChoices = 0;
		chosenPokemon = player.getPokemon(choice - 1);
		cout << "Selected " << chosenPokemon->getName() << "!" << endl;
		cout << " HP: " << chosenPokemon->getHealth() << "/" << chosenPokemon->getMaxHealth() << endl;
		cout << "What would you like to do to " << chosenPokemon->getName() << "!" << endl;
		cout << "1. Heal pokemon" << endl;
		if(pokemonChoices == 1){
			chosenPokemon->restoreHealth(chosenPokemon->getMaxHealth());
			chosenPokemon->restoreMoves();
			cout << "Pokemon healed!" << endl;
			displayParty(player);
		}
	}
	else {
		cout << "Invalid choice. Please try again." << endl;
	}
}

void Display::displayPlayerMenu(Player& player){
	cout << "Menu" << endl;
	int choices = 0;
	cout << "1. Party" << endl;
	cout << "2. Battles" << endl;
	cout << "3. Bag" << endl;
	cout << "4. Shop" << endl;

	cin >> choices;

	switch (choices) {
	case 1:
		// Handle Party option
		cout << "Party selected" << endl;
		// Add your party functionality here
		displayParty(player);
		break;

	case 2:
		// Handle Battles option
		cout << "Battles selected" << endl;
		int chooseBattle;
		cout << "1. Wild Pokemon" << endl;
		cout << "2. Back" << endl;
		cin >> chooseBattle;
		if (chooseBattle == 1) {

		}
		if (chooseBattle == 2) {
			return displayPlayerMenu();
		}
		else {
			cout << "Invalid Input, try again." << endl;
			return;
		}

		// Add your battles functionality here
		break;

	case 3:
		// Handle Bag option
		cout << "Bag selected" << endl;
		cout << "Pokeballs: " << player.getPokeballs() << endl;
		cout << "Masterballs: " << player.getMasterballs() << endl;
		cout << "Elixers: " << player.getElixers() << endl;
		cout << "Full Heals: " << player.getFullHeals() << endl;
		cout << "Enter 1 to go back" << endl;
		int exitBag;
		cin >> exitBag;
		if (exitBag == 1) {
			return displayPlayerMenu();
		}
		else {
			cout << "Invalid Input, try again." << endl;
			return;
		}
		// Add your bag functionality here
		break;

	case 4:
		// Handle Shop option
		int choice;
		cout << "Shop selected" << endl;
		cout << "What would you like to purchase" << endl;
		cout << "1. Potions: 10 Coins" << endl;
		cout << "2. Pokeballs: 10 coins" << endl;
		if(choice == 1){
			int amt;
			cout << "How many Pokeballs would you like to purchase" << endl;
			cin >> amt;
			if(player.getPokecoins() >= amt * 10){
				player.addPokeballs(amt);
				cout << "Purchased " << amt << " of Pokeballs" << endl;
			} else {
				cout << "Not enough pokecoins" << endl;
			}
		} 
		if(choice == 2){
			int amt;
			cout << "How many potions would you like to purchase" << endl;
			cin >> amt;
			if (player.getPokecoins() >= amt * 10) {
				player.addPotions(amt);
				cout << "Purchased " << amt << " of Potions" << endl;
			}
			else {
				cout << "Not enough pokecoins" << endl;
			}
		}
		break;

	default:
		cout << "Invalid choice. Please select 1-4." << endl;
		break;
	}
	
}