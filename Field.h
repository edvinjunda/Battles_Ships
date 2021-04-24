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
private:
	void HorizontalShipPutting(int& a, int& b, int korpusai);
	void VerticalShipPutting(int& a, int& b, int korpusai);
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
void Field::HorizontalShipPutting(int& a, int& b, int korpusai)
{
		for (int i = a-1; i < a + korpusai+1; i++)
		{
			if (field[b][i + 1] == "#" ||
				field[b][i - 1] == "#" ||
				field[b + 1][i] == "#" ||
				field[b - 1][i] == "#" ||
				field[b + 1][i + 1] == "#" || 
				field[b + 1][i - 1] == "#" ||
				field[b - 1][i + 1] == "#" ||
				field[b - 1][i - 1] == "#")
			{
				b = rand() % 10 + 1;
				a = rand() % (10 - korpusai+1) + 1;
				i = a;
			}
			cout << b-1 << ' ' << i-1 <<' '<<'H'<< endl;
		}
}

void Field::VerticalShipPutting(int& a, int& b, int korpusai)
{

		for (int i = b; i < b + korpusai; i++)
		{
			if (field[i + 1][a] == "#" ||
				field[i - 1][a] == "#" ||
				field[i][a + 1] == "#" ||
				field[i][a - 1] == "#" ||
				field[i + 1][a + 1] == "#" ||
				field[i + 1][a - 1] == "#" ||
				field[i - 1][a + 1] == "#" ||
				field[i - 1][a - 1] == "#")
			{
				b = rand() % (10 - korpusai+1) + 1;
				a = rand() % 10 + 1;
				i = b;
			}
		}
}

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
	for (int j = 0; j < 3; j++)
	{
		for (int l = 0; l < ships; l++)
		{
			
			//if (rand() % 2)						//i kaire nukreiptas laivas
			//{
				int y = rand() % 10 + 1;
				int x = rand() % (10-blocks+1) + 1;

				HorizontalShipPutting(x, y, blocks);

				for (int i = x; i < x + blocks; i++)
				{
					field[y][i] = "#";
				}
			//}
			/*else								//i apacia nukreipia laiva
			{
				int y = rand() % (10 - blocks + 1) + 1;
				int x = rand() % 10 + 1;

				VerticalShipPutting(x, y, blocks);

				for (int i = y; i < y + blocks; i++)
				{
					field[i][x] = "#"; 
				}
			}*/
		}
		ships++;
		blocks--;
	}
	/*for (int l = 0; l < ships; l++)
	{
		int y = rand() % 10 + 1;
		int x = rand() % 10 + 1;

		HorizontalShipPutting(x, y, blocks);
		
		field[y][x] = "#";
	}*/


}