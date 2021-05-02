#pragma once

#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <typeinfo>
#include <limits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Field.h"
#include "Entity.h"
#include "Utilities.h"

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
	cout << setw(16) << "##############" << endl;
	cout << setw(16) << "#SHIP BATTLES#" << endl;
	cout << setw(16) << "##############" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	cout << setw(5) << "1. ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "Play" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	cout << setw(5) << "2. ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout<<"Game guide" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << setw(5) << "3. ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "History" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << setw(30) <<"To exit press ESC or enter 4" << endl; //28 simboliai

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

}

void Menu::Choose(Bot& bot, Player& player)
{
	while (true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << setw(18) << "################" << endl;
		cout << setw(18) << "#SHIP PLACEMENT#" << endl;
		cout << setw(18) << "################" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		cout << "If you want place ships ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "manually"; 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<", enter m / M" << endl;

		cout << "If you want place ships ";
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
			cout << "Enter valid letter!" << endl;
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
				cout << "Choose coordinates between 0 and 9!" << endl;
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
			cout << "  You won!" << endl;
			ofstream history("History.txt", ios::app);

			history << "  You won!" << endl;
			history << "  Your ship points:	   " << player.GetShipPoints() << endl;
			history << "  Enemy's ship points: " << bot.GetShipPoints() << endl;

			history.close();

			break;
		}


		do
		{
			system("cls");
			visible_bot_field.ShowField();
			player.ShowField();

			cout << "Now it's enemy's turn to shoot!" << endl;
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
			cout << "  You lost!" << endl;
			ofstream history("History.txt", ios::app);
			
			history << "  You lost!" << endl;
			history << "  Your ship points:	   " << player.GetShipPoints() << endl;
			history << "  Enemy's ship points: " << bot.GetShipPoints() << endl;

			history.close();

			break;
		}
	}


	cout << endl;
	cout << "To get back to the menu press any key" << endl;
	cout << "To exit the game press Esc" << endl;

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
	ifstream history("History.txt");

	string line;

	system("cls");

	if (history.good() == false)
	{
		cout << "  History file 'History.txt' doesn't exist!" << endl;
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
	cout << "  To exit history press any other key" << endl;
	
	char choice;
	choice = _getch();
	if(choice =='r' || choice == 'R')
	{
		ofstream delete_hist("History.txt");

		delete_hist << ' ';

		delete_hist.close();
	}
}

void Files::GameGuide() 
{
	ifstream game_guide("Game Guide.txt");

	string line;

	system("cls");

	if (game_guide.good() == false)
	{
		cout << "  Game guide file 'Game Guide.txt' doesn't exist!" << endl;
	}
	else
	{
		while (getline(game_guide, line))
		{
			cout << line << endl;
		}
	}

	game_guide.close();

	cout << "To exit game guide press any key" << endl;

	char choice;
	choice = _getch();
}