#pragma once

#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Field.h"
#include "Entity.h"
#include "Utilities.h"
#include "Constants.h"

using namespace std;

class UI
{
public:
	UI(){}
	virtual ~UI(){}
public:
	virtual void Visualize()=0;
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//blue id 9, red id 12, white id 15, yellow id 14, green id 10
class Menu : public UI
{
public:
	void Visualize();
	void Choose(Bot& bot, Player& player);
	void Play(Bot& bot, Bot& visible_bot_field, Player& player);
};

void Menu::Visualize()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "  ##############" << endl;
	cout << "  #SHIP BATTLES#" << endl;
	cout << "  ##############" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	cout <<"  1. ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "Play" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	cout <<"  2. ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout<<"Game guide" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout <<"  3. ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "History" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "  To exit press ESC or enter 4" << endl; //28 simboliai

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

}

void Menu::Choose(Bot& bot, Player& player)
{
	system("cls");
	while (true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "  ################" << endl;
		cout << "  #SHIP PLACEMENT#" << endl;
		cout << "  ################" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		cout << ship_placement;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "manually"; 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<", enter m / M" << endl;

		cout << ship_placement;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "randomly";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << ", enter r / R" << endl;


		char choice;
		choice = _getch();
		if (choice == 'm' || choice == 'M')
		{
			player++;
			system("cls");
			break;
		}
		else if (choice == 'r' || choice == 'R')
		{
			++player;
			system("cls");
			break;
		}
		else
		{
			system("cls");
			cout << "  Enter valid letter!" << endl;
		}
	}
	++bot;
}

void Menu::Play(Bot& bot, Bot& visible_bot_field, Player& player)
{
	int x, y;
	bool one_more = 0;

	while (true)
	{
		do
		{
			system("cls");
			visible_bot_field.ShowField();
			player.ShowField();

			player.Shoot(x, y);
			UnvalidCoordinates(x, y);
			x++;
			y++;

			while (x < 1 || x>10 || y < 1 || y>10)
			{
				cout << "  Choose coordinates between 0 and 9!" << endl;
				player.Shoot(x, y);
				UnvalidCoordinates(x, y);
				x++;
				y++;
				break;
			}
			while (bot.RepeatedShot(x, y))
			{
				player.Shoot(x, y);
				UnvalidCoordinates(x, y);
				x++;
				y++;
				break;
			}

			bot.GetShot(x, y, visible_bot_field, one_more);
			if (bot.GetShipPoints() == 0)
			{
				break;
			}
		} while (one_more);

		if (bot.GetShipPoints() == 0)
		{
			cout << won << endl;
			cout << player_ship_points << player.GetShipPoints() << endl;
			cout << enemy_ship_points << bot.GetShipPoints() << endl;

			ofstream history(history_file, ios::app);

			history << won << endl;
			history << player_ship_points << player.GetShipPoints() << endl;
			history << enemy_ship_points << bot.GetShipPoints() << endl;

			history.close();

			break;
		}


		do
		{
			system("cls");
			visible_bot_field.ShowField();
			player.ShowField();

			cout << "  Now it's enemy's turn to shoot!" << endl;
			Sleep(2000);
			bot.Shoot(x, y);
			//cout << bot.GetHitValue() << " hit value" << endl;
			while (player.RepeatedShot(x, y, bot))
			{
				//cout << bot.GetHitValue() <<" hit value"<< endl;
				bot.Shoot(x, y);
			}

			player.GetShot(x, y, bot, one_more);
			Sleep(1000);
			if (player.GetShipPoints() == 0)
			{
				break;
			}
		} while (one_more);

		if (player.GetShipPoints() == 0)
		{
			cout << lost << endl;
			cout << player_ship_points << player.GetShipPoints() << endl;
			cout << enemy_ship_points << bot.GetShipPoints() << endl;

			ofstream history(history_file, ios::app);
			
			history << lost << endl;
			history << player_ship_points << player.GetShipPoints() << endl;
			history << enemy_ship_points << bot.GetShipPoints() << endl;

			history.close();

			break;
		}
	}


	cout << endl;
	cout << back_to_menu << endl;
	cout << "  To exit the game press Esc" << endl;

	char choice;
	choice = _getch();

	if (choice == 27)
	{
		exit(0);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Files : public UI
{
public:
	void Visualize();
	void GameGuide();

};

void Files::Visualize()
{
	ifstream history(history_file);

	string line;

	system("cls");

	if (history.good() == false)
	{
		throw "  History file doesn't exist!";
	}
	else
	{
		while (getline(history, line))
		{
			cout << line << endl;
		}
	}

	history.close();

	cout << endl;
	cout << endl;
	cout << "  To delete history press r / R" << endl;
	cout << back_to_menu << endl;
	
	char choice;
	choice = _getch();
	if(choice =='r' || choice == 'R')
	{
		cout << "  To confirm press r / R once more" << endl;
		cout << back_to_menu << endl;
		choice = _getch();

		if (choice == 'r' || choice == 'R')
		{
			ofstream delete_hist("History.txt");

			delete_hist << "";

			delete_hist.close();
		}
	}
}

void Files::GameGuide() 
{
	ifstream game_guide("Game Guide.txt");

	string line;

	system("cls");

	if (game_guide.good() == false)
	{
		throw "  Game guide file doesn't exist!";
	}
	else
	{
		while (getline(game_guide, line))
		{
			cout << line << endl;
		}
	}

	game_guide.close();

	cout << endl;
	cout << back_to_menu << endl;

	char choice;
	choice = _getch();
}