#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;


class Field
{
protected:
	string laukas[10][10];
public:
	Field();
	virtual ~Field();
public:
	void ShowLaukas();

};

Field::Field()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			laukas[i][j] = "~";
}
Field::~Field(){}

//blue id 9, red id 12, white id 15, yellow id 14, green id 10

void Field::ShowLaukas()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < 10; i++)
		cout <<' '<< i;
	cout << endl;

	for (int i = 0; i < 10; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << i;
		for (int j = 0; j < 10; j++)
		{
			cout << '|';
			//if(laukas[i][j]=="~")												//vanduo
				
			if(laukas[i][j] == "#")										//laivo sveikoji dalis
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			else if(laukas[i][j] == "")										//nepataikymas, alt 176
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			else if(laukas[i][j] == "")									//pataikimas, alt 177
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			else if(laukas[i][j] == "")										//sunaikinimas, alt 178
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

			cout << laukas[i][j];

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout<< '|';
		}

		for (int j = 0; j < 10; j++)
		{
			
			cout << '|' << laukas[i][j] << '|';
		}
		cout << endl;
	}
}