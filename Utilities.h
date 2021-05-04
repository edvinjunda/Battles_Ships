#pragma once
#include <iostream>
#include <conio.h>
#include "Constants.h"

using namespace std;

//funkcija trinanti ivesta reiksme su cin jeigu atsitiktu taip kad i int kazkas irasytu stringa
void IgnoreLine()
{
	cin.clear(); // clear input buffer to restore cin to a usable state
	cin.ignore(INT_MAX, '\n'); // ignore last input
}

//funkcija netinkamu koordinaciu ivedimo patikrinimui
void UnvalidCoordinates(int& x, int& y)
{
	while (true)
	{
		if (x < 0 || x>9 || y < 0 || y>9 || cin.fail())
		{
			IgnoreLine();

			cout << valid_coordinates;
			cin >> x >> y;
		}

		else
			break;
	}
}


