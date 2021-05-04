#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>		/* srand, rand */
#include <Windows.h>	/* time */
#include <time.h>
#include <conio.h>
#include "Utilities.h"
#include "Constants.h"

using namespace std;

//klase musio laukui generuoti, laivams randomiskai ir rankiniu budu isdestyti ir atvaizduoti lauka
class Field
{
protected:
	string** field;//[12][12];		//masyvas musio laukui saugoti
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
//konstruktorius dinaminyje atmintyje musio lauko sukurimui
Field::Field()
{
	field = new string * [12];
	for (int i = 0; i < 12; i++)
		field[i] = new string[12];

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			field[i][j] = "~";

	srand(time(NULL));
}
//destruktorius dinamines atminties atlaisvinimui
Field::~Field()
{
	for (int i = 0; i < 12; i++)
		delete[] field[i];
	delete[] field;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//blue id 9, red id 12, white id 15, yellow id 14, green id 10

//metodas musio lauku atvaizdavimui
void Field::ShowField()
{
	cout << "   ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < 10; i++)
		cout << ' ' << i;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << ' ' << "x axis" << endl;


	for (int i = 1; i < 11; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "  " << i - 1;

		for (int j = 1; j < 11; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << '|';
			if (field[i][j] == "~")												//vanduo
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

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "  y axis" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

}

//metodas randomiskam laivu isdestymui
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
					if (field[i][x - 1] == "#" || field[i][x] == "#" || field[i][x + 1] == "#")
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

//metodas rankiniam laivu isdestymui
void Field::operator ++(int)
{
	int ships = 1, blocks = 4, placed_ships = 0;

	for (int j = 0; j < 4; j++)
	{
		for (int l = 0; l < ships; l++)
		{
			system("cls");
			ShowField();
			cout << endl;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "  " << placed_ships;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			cout << '/';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << 10;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			cout << " ships placed." << endl;


			cout << "  Currently placing ";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << blocks;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			cout << " blocks size ship." << endl;


			cout << "  In order to place ship horizontally, type h / H" << endl;
			cout << "  In order to place ship vertically, type v / V" << endl;

			char direction;
			while (true)
			{
				int x, y;
				//cin >> direction;
				direction = _getch();
				if (direction == 'h' || direction == 'H')					//horizontal
				{
					cout << x_y_coordinates;
					cin >> x >> y;

					UnvalidHorizontalPlacement(x, y, blocks);
					x++;
					y++;

					for (int i = x - 1; i < x + blocks + 1; i++)
					{
						if (field[y + 1][i] == "#" || field[y][i] == "#" || field[y - 1][i] == "#")
						{
							cout << ship_collision << endl;
							cout << other_coordinates << endl;
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
					cout << x_y_coordinates;
					cin >> x >> y;

					UnvalidVerticalPlacement(x, y, blocks);
					x++;
					y++;

					for (int i = y - 1; i < y + blocks + 1; i++)
					{
						if (field[i][x - 1] == "#" || field[i][x] == "#" || field[i][x + 1] == "#")
						{
							cout << ship_collision << endl;
							cout << other_coordinates << endl;
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
					cout << "  Enter correct direction!" << endl;
				}
			}
			placed_ships++;
		}
		ships++;
		blocks--;
	}

	cout << "  Pleas wait few seconds, preparation of match is going on." << endl;
	Sleep(3000);

}

//privatus metodas patikrinti ar ivesti duomenys yra tinkami ir ar yra imanoma isdestyti laiva horizontaliai
void Field::UnvalidHorizontalPlacement(int& x, int& y, int blocks)
{
	while (true)
	{
		if (x < 0 || x>10 - blocks || y < 0 || y>9 || cin.fail())
		{
			IgnoreLine();

			cout << valid_coordinates;
			cin >> x >> y;
		}
		else
			break;
	}
}

//privatus metodas patikrinti ar ivesti duomenys yra tinkami ir ar yra imanoma isdestyti laiva horizontaliai
void Field::UnvalidVerticalPlacement(int& x, int& y, int blocks)
{
	while (true)
	{
		if (x < 0 || x>9 || y < 0 || y>10 - blocks || cin.fail())
		{
			IgnoreLine();

			cout << valid_coordinates;
			cin >> x >> y;
		}
		else
			break;
	}
}



