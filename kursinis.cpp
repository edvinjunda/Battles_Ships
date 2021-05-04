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
	while (true)								//begalinis ciklas zaidimo procesui leisti
	{
		system("cls");

		Player player;
		Bot bot, visible_bot_field;

		ui[0]->Visualize();

		char option;				//kintamasis pasirinkimo irasymui
		option = _getch();

		try
		{
			switch (option)			//swtichas metodams paleisti
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
		catch (const char* error)		//isimtys kuri suveikia, kai nera istorijos arba zaidimo gido txt failo
		{
			cout << error << endl;
			cout << "  ";
			system("pause");
		}
	}

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
