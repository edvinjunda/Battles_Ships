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

void Field::ShowLaukas()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << '|' << laukas[i][j] << '|';
		cout << endl;
	}
}