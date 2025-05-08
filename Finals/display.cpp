#include "display.h"
#include "player.h"
#include <iostream>
#include <string>
#include <conio.h> // https://cplusplus.com/forum/beginner/284909/
// Input reader

using namespace std;

void display::displayMenu() {
	int choice = 1;
	int const total_choices = 2;
	while (true)
	{
		//Clear console
		system("cls"); // https://www.geeksforgeeks.org/clear-console-c-language/
		cout << "Welcome to Pokemon" << endl;
		//Tenary operator, if 1st choice is selected, show arrow
		cout << (choice == 1 ? "-> " : "   ") << "1. Start Game" << endl;
		cout << (choice == 2 ? "-> " : "   ") << "2. End Game" << endl;

		int key = _getch();
		if (key == 72)
		{
			choice--;
			if (choice < 1)
				choice = total_choices;
		}
		else if (key == 80)
		{
			choice++;
			if (choice > total_choices)
				choice = 1;
		}
		else if (key == 13) // Enter key
		{
			if (choice == 1)
			{
				cout << "Starting game..." << endl;
				displayStart();
				break;
			}
			else if (choice == 2)
			{
				cout << "Exiting game..." << endl;
				break; // Exit the loop to end the game
			}
		}
	}
}

void display::displayStart()
{
	system("cls");
	string name;
	player player;
	cout << "Welcome to the world of Pokemon!" << endl;
	cout << "Hello, my name is Professor Maxwell, today marks the first day of your pokemon journey" << endl;
	cout << "First of all, what was your name again?" << endl;
	cin >> name;
	player.setName(name);
	cout << "Right! So it's " << player.getName() << "!" << endl;
	cout << "Are you ready to start your journey?" << endl;
	cout << "Press any key to continue..." << endl;
	_getch();
r	system("cls");
	cout << "You are now in the world of Pokemon!" << endl;
	cout << "First, you need to choose your starter Pokemon!" << endl;
	cout << "Press any key to continue..." << endl;
	_getch();
	system("cls");
	cout << "You have three choices of Pokemon!" << endl;
	cout << "1. Bulbasaur" << endl;
	cout << "2. Charmander" << endl;
	cout << "3. Squirtle" << endl;

}
