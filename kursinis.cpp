// kursinis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
////
#include <string>
#include <stdlib.h>
#include <fstream>
#include <typeinfo>
#include <limits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include "Entity.h"
#include "Field.h"

int main()
{

	Player player;
	Bot bot,visible_bot_field;

	while (true)
	{
		cout << "If you want place ships manually, enter m/M" << endl;
		cout << "If you want place ships randomly, enter r/R" << endl;
		char choice;
		cin >> choice;
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


	//Sleep(2000);cin.fail()

	while (true)
	{
		system("cls");
		visible_bot_field.ShowField();
		player.ShowField();

		int x, y;
		player.Shoot(x, y);
		if (x < 1 || x>10 || y < 1 || y>10)
		{
			cout << "Choose coordinates between 0 and 9!" << endl;
			Sleep(2000);
			continue;
		}
		if (bot.RepeatedShot(x, y))
		{
			Sleep(3000);
			continue;
		}
		bot.GetShot(x, y,visible_bot_field);

	
		
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
