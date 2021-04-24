#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>

using namespace std;


class Field
{
protected:
	string field[12][12];
public:
	Field();
	virtual ~Field();
public:
	void ShowField();
	void RandomField();


};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Field::Field()
{
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			field[i][j] = "~";

	//field[3][6]="X";
	//		y  x
}
Field::~Field(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//blue id 9, red id 12, white id 15, yellow id 14, green id 10

void Field::ShowField()
{
	cout << ' ';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < 10; i++)
		cout << ' ' << i;
	cout << endl;

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
}

void Field::RandomField()
{
	srand(time(NULL));

	int ships = 1, blocks = 4;
	for (int j = 0; j < 4; j++)
	{
		for (int l = 0; l < ships; l++)
		{
			if (rand() % 2)						//i kaire nukreiptas laivas
			{
				int y = rand() % 10 + 1;
				int x = rand() % (10 - blocks + 1) + 1;
				for (int i = x - 1; i < x + blocks + 1; i++)
				{
					if (field[y + 1][i] == "#" || field[y][i] == "#" || field[y - 1][i] == "#")
					{
						y = rand() % 10 + 1;
						x = rand() % (10 - blocks + 1) + 1;
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
				int y = rand() % (10 - blocks + 1) + 1;
				int x = rand() % 10 + 1;
				for (int i = y - 1; i < y + blocks + 1; i++)
				{
					if (field[i][x-1] == "#" || field[i][x] == "#" || field[i][x+1] == "#")
					{
						y = rand() % (10 - blocks + 1) + 1;
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