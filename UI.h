#pragma once

#include <string>
#include <stdlib.h>
#include <fstream>
#include <typeinfo>
#include <limits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Field.h"
#include "Entity.h"
#include "Utilities.h"

using namespace std;

class UI
{
public:
	UI(){}
	~UI(){}
public:
	virtual void Visualize()=0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//blue id 9, red id 12, white id 15, yellow id 14, green id 10
class Menu : UI
{
public:
	void Visualize();
	void Play();
};

void Menu::Visualize()
{
	cout << "1.";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << " Play" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "2. ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout<<"Game rules" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "3. ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "History" << endl;
	//int i;
	//i = getch();

}


class History : UI
{
public:
	void Visualize();

};


