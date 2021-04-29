#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>		/* srand, rand */
#include <Windows.h>	/* time */
#include <time.h>
#include <conio.h>
#include "Utilities.h"

using namespace std;


class Field
{
protected:
	string** field;//[12][12];
public:
	Field();
	virtual ~Field();
public:
	void ShowField();		//ShowField
	void operator ++();		//RandomShipGenerator
	void operator ++(int);  //ManuallShipPlacement
private:
	void UnvalidHorizontalPlacement(int& x, int& y, int blocks);
	void UnvalidVerticalPlacement(int& x, int& y, int blocks);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Field::Field()
{
	field = new string* [12];
	for (int i = 0; i < 12; i++)
		field[i] = new string[12];

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			field[i][j] = "~";

	srand(time(NULL));

	//field[3][6]="X";
	//		y  x
}
Field::~Field()
{
	for (int i = 0; i < 12; i++)
		delete[] field[i];
	delete[] field;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//blue id 9, red id 12, white id 15, yellow id 14, green id 10

void Field::ShowField()
{
	cout << ' ';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < 10; i++)
		cout << ' ' << i;
	cout <<' '<<"x axis"<< endl;

	for (int i = 1; i < 11; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << i - 1;

		for (int j = 1; j < 11; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << '|';
			if(field[i][j]=="~")												//vanduo
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			else if (field[i][j] == "#")										//laivo sveikoji dalis
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			else if (field[i][j] == "O")										//nepataikymas
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			else if (field[i][j] == "+")									//pataikimas
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			else if (field[i][j] == "X")										//sunaikinimas
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

			cout << field[i][j];
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << '|' << endl;
	}
	
	cout << "y axis" << endl << endl;

}

void Field::operator++()									
{


	int ships = 1, blocks = 4;
	for (int j = 0; j < 4; j++)
	{
		for (int l = 0; l < ships; l++)
		{
			if (rand() % 2)						//i desine nukreiptas laivas
			{
				int y = rand() % 10 + 1;
				int x = rand() % (11 - blocks) + 1;
				for (int i = x - 1; i < x + blocks + 1; i++)
				{
					if (field[y + 1][i] == "#" || field[y][i] == "#" || field[y - 1][i] == "#")
					{
						y = rand() % 10 + 1;
						x = rand() % (11 - blocks) + 1;
						i = x - 2;
					}
				}

				for (int i = x; i < x + blocks; i++)
				{
					field[y][i] = "#";
				}
			}

			else								//i apacia nukreipia laiva
			{
				int y = rand() % (11 - blocks) + 1;
				int x = rand() % 10 + 1;
				for (int i = y - 1; i < y + blocks + 1; i++)
				{
					if (field[i][x-1] == "#" || field[i][x] == "#" || field[i][x+1] == "#")
					{
						y = rand() % (11 - blocks) + 1;
						x = rand() % 10 + 1;
						i = y - 2;
					}
				}

				for (int i = y; i < y + blocks; i++)
				{
					field[i][x] = "#";
				}
			}
		}

		ships++;
		blocks--;
	}
}

void Field::operator ++(int)
{
	int ships = 1, blocks = 4,placed_ships=0;

	for (int j = 0; j < 4; j++)
	{
		//cout << "Ships generate from left to right or from top to bottom." << endl;
		//cout << "If you want put ship horizontally, it will go rightwards from x y coordinates" << endl;
		//cout << "If you want put ship vertically, it will go downwards from x y coordinates." << endl;
		//cout << "Remember, place ships in a way to not collide them!" << endl;
		
		for (int l = 0; l < ships; l++)
		{
			system("cls");
			ShowField();
			cout << endl;

			cout << placed_ships << '/' << 10 << " ships placed." << endl;
			cout << "Currently placing " << blocks << " blocks size ship." << endl;
			cout << "In order to place ship horizontally, type h/H" << endl;
			cout << "In order to place ship vertically, type v/V" << endl;

				char direction;
				while (true)
				{
					int x, y;
					cin >> direction;
					if (direction == 'h' || direction == 'H')					//horizontal
					{
						cout << "Enter x and y coordinates: ";
						cin >> x >> y;

						UnvalidHorizontalPlacement(x, y, blocks);
						x++;
						y++;

						for (int i = x - 1; i < x + blocks + 1; i++)
						{
							if (field[y + 1][i] == "#" || field[y][i] == "#" || field[y - 1][i] == "#")
							{
								cout << "Ship which you want to place will collide with another ship!" << endl;
								cout << "Enter other x coordinate: " << endl;
								cin >> x >> y;

								UnvalidHorizontalPlacement(x, y, blocks);
								x++;
								y++;

								i = x - 2;
							}
						}

						for (int i = x; i < x + blocks; i++)
						{
							field[y][i] = "#";
						}

						break;
					}

					else if (direction == 'v' || direction == 'V')					//vertical
					{
						cout << "Enter x and y coordinates: ";
						cin >> x >> y;

						UnvalidVerticalPlacement(x, y, blocks);
						x++;
						y++;

						for (int i = y - 1; i < y + blocks + 1; i++)
						{
							if (field[i][x - 1] == "#" || field[i][x] == "#" || field[i][x + 1] == "#")
							{
								cout << "Ship which you want to place will collide with another ship!" << endl;
								cout << "Enter other y coordinate: " << endl;
								cin >> x >> y;

								UnvalidVerticalPlacement(x, y, blocks);
								x++;
								y++;

								i = y - 2;
							}
						}

						for (int i = y; i < y + blocks; i++)
						{
							field[i][x] = "#";
						}
						break;
					}

					else
					{
						cout << "Enter correct direction!" << endl;
					}
				}
				placed_ships++;
		}
		ships++;
		blocks--;
	}

	cout << "Pleas wait few seconds, preparation of match is going on." << endl;
	Sleep(3000);

}


void Field::UnvalidHorizontalPlacement(int& x, int& y, int blocks)
{
	while (true)
	{
		if (x < 0 || x>10 - blocks || y < 0 || y>9 || cin.fail())
		{
			IgnoreLine();

			cout << "Enter valid coordinates!" << endl;
			cin >> x >> y;
		}

		else
			break;
	}
}

void Field::UnvalidVerticalPlacement(int& x, int& y, int blocks)
{
	while (true)
	{
		if (x < 0 || x>9 || y < 0 || y>10 - blocks || cin.fail())
		{
			IgnoreLine();

			cout << "Enter valid coordinates!" << endl;
			cin >> x >> y;
		}

		else
			break;
	}
}
