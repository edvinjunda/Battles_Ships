#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;


class Field
{
protected:
	string field[10][10];
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
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			field[i][j] = "~";
}
Field::~Field(){}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Field::HorizontalShipPutting(int& a, int& b, int korpusai)
{
	while (true)
	{
		int i;
		for (i = a; i < a + korpusai; i++)
		{
			if (field[b][i + 1] == "#" ||
				field[b][i - 1] == "#" ||
				field[b + 1][i + 1] == "#" ||
				field[b + 1][i - 1] == "#" ||
				field[b - 1][i + 1] == "#" ||
				field[b - 1][i - 1] == "#")
			{
				b = rand() % 10;
				a = rand() % 6;
				break;
			}
		}
		//cout << i << endl;
		if (i == a + korpusai)
			break;
	}
}

void Field::VerticalShipPutting(int& a, int& b, int korpusai)
{
	while (true)
	{
		int i;
		for (i = b; i < b + korpusai; i++)
		{
			if (field[i + 1][a] == "#" ||
				field[i - 1][a] == "#" ||
				field[i + 1][a + 1] == "#" ||
				field[i + 1][a - 1] == "#" ||
				field[i - 1][a + 1] == "#" ||
				field[i - 1][a - 1] == "#")
			{
				b = rand() % 6;
				a = rand() % 10;
				break;
			}
		}
		//cout << i << endl;
		if (i == b + korpusai)
			break;
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

	for (int i = 0; i < 10; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << i;
		for (int j = 0; j < 10; j++)
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

	//4 korpusu laivas
	if (rand() % 2)						//i kaire nukreipia laiva
	{
		int y = rand() % 10;
		int x = rand() % 6;

		for (int i = x; i < x+4; i++)
			field[y][i] = "#";
	}
	else								//i apacia nukreipia laiva
	{
		int y = rand() % 6;
		int x = rand() % 10;

		for (int i = y; i < y+4; i++)
			field[i][x] = "#";
	}

	//3 korpusu laivas
	for (int l = 0; l < 2; l++)
	{
		if (rand() % 2)						//i kaire nukreiptas laivas
		{
			int y = rand() % 10;
			int x = rand() % 6;

			HorizontalShipPutting(x, y, 3);

			for (int i = x; i < x + 3; i++)
				field[y][i] = "#";
		}
		else								//i apacia nukreipia laiva
		{
			int y = rand() % 6;
			int x = rand() % 10;

			VerticalShipPutting(x, y, 3);

			for (int i = y; i < y + 3; i++)
				field[i][x] = "#";
		}
	}
	

}