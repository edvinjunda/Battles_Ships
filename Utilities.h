#pragma once
#include <iostream>
#include <conio.h>
#include "Constants.h"

using namespace std;

void IgnoreLine()
{
	cin.clear(); // clear input buffer to restore cin to a usable state
	cin.ignore(INT_MAX, '\n'); // ignore last input
}

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


