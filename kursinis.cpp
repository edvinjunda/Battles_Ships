// kursinis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
////
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Entity.h"
#include "Field.h"
#include "Utilities.h"
#include "UI.h"

int main()
{
	UI* ui[2];
	ui[0] = new Menu;
	ui[1] = new Files;

	Menu* menu = dynamic_cast<Menu*>(ui[0]);
	Files* file = dynamic_cast<Files*>(ui[1]);
	while (true)
	{
		system("cls");

		Player player;
		Bot bot, visible_bot_field;

		ui[0]->Visualize();

		char option;
		option = _getch();

		try
		{
			switch (option)
			{
			case '1':
				menu->Choose(bot,player);
				menu->Play(bot,visible_bot_field,player);
				break;
			case '2':
				file->GameGuide();
				break;
			case '3':
				ui[1]->Visualize();
				break;
			case '4':
				exit(0);
				break;
			case 27:
				exit(0);
				break;
			default:
				cout << "  Uncorrect choice!" << endl;
				Sleep(1000);
				system("cls");
				break;
			}
		}
		catch (const char* error)
		{
			cout << error << endl;
			cout << "  ";
			system("pause");
		}
	}
	


		//Sleep(2000);cin.fail()
	/*int x, y;
	bool one_more=0;
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

			while(x < 1 || x>10 || y < 1 || y>10)
			{
				cout << "Choose coordinates between 0 and 9!" << endl;
				player.Shoot(x, y);
				UnvalidCoordinates(x, y);
				x++;
				y++;
				break;
			}
			while(bot.RepeatedShot(x, y))
			{
				player.Shoot(x, y);
				UnvalidCoordinates(x, y);
				x++;
				y++;
				break;
			}

			bot.GetShot(x, y, visible_bot_field, one_more);
			if (bot.GetShipPoints()==0)
			{
				break;
			}
		} while (one_more);

		if (bot.GetShipPoints() == 0)
		{
			cout << "You won!" << endl;
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
		while (player.RepeatedShot(x,y,bot))
		{
			//cout << bot.GetHitValue() <<" hit value"<< endl;
			bot.Shoot(x, y);
		}

		player.GetShot(x, y, bot, one_more);
		Sleep(1000);
		if (player.GetShipPoints()==0)
		{
			break;
		}
		} while (one_more);

		if (player.GetShipPoints() == 0)
		{
			cout << "You lost!" << endl;
			break;
		}
		
	}*/

	return 0;
}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
