// kursinis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
////
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <typeinfo>
#include <limits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include "Entity.h"
#include "Field.h"

int main()
{
	/*Entity* entities[2];
	entities[0] = new Player;
	entities[1] = new Bot;

	entities[0]->RandomField();
	entities[0]->ShowField();
	cout << endl;
	entities[1]->RandomField();
	entities[1]->ShowField();


	delete[] entities;*/

	//entities[0]->Shoot(entities[1]->GiveField());

	Player laukas1;
	Bot field;

	laukas1.RandomField();
	laukas1.ShowField();
	cout << endl;
	field.RandomField();
	field.ShowField();
	while (true)
	{
	int x, y;
	laukas1.Shoot(x, y);
	field.GetShot(x, y);

	
		system("cls");
		laukas1.ShowField();
		cout << endl;
		field.ShowField();
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
