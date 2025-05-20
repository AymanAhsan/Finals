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
	Pokemon* turtwig = new Pokemon("Turtwig", 5, 20, 20, 10, 5, 5);
	Pokemon* chimchar = new Pokemon("Chimchar", 5, 20, 20, 10, 5, 5);
	Pokemon* piplup = new Pokemon("Piplup", 5, 20, 20, 10, 5, 5);

	// Setup Pokemon data
	turtwig->setupPokemon(turtwig, "pokemons.json", "moves.json" );
	chimchar->setupPokemon(chimchar, "pokemons.json", "moves.json" );
	piplup->setupPokemon(piplup, "pokemons.json", "moves.json" );

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

	

	// Fix battle bug tmrw
}
