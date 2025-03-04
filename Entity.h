﻿#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <conio.h>
#include "Field.h"
#include "Constants.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bazine ir isvestine klase Entity, kuri paveldi Field klase
class Entity : public Field
{
protected:
	int ship_points;	//taskai, kurie atspindi kiek yra like nepataikytu bloku
public:
	Entity();
	virtual ~Entity(); 
public:
	virtual void Shoot(int& x, int& y)=0;	//grynai virtuali funkcija saudimui
	int GetShipPoints();					
	virtual void GetShot(int x, int y);
};

//konstruktorius, kuris nustato numatytus zaidejo ir boto taskus
Entity::Entity() : ship_points(20){}
Entity::~Entity(){}

//metodas kuris paduoda taskus
int Entity::GetShipPoints()
{
	return ship_points;
}

//virtualus metodas skirtas suviams gauti
void Entity::GetShot(int x, int y)
{
	if(field[y][x]=="#")
		field[y][x] = "+";
	else
	{
		field[y][x] = "O";
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//isvestine, boto Bot klase, kuri paveldi bazine Entity klase
class Bot : public Entity
{
private:
	int a, b, hit, checker;
	char direction;
public:
	Bot();
	~Bot();
public:
	void Shoot(int& x, int& y);
	void SetHitValue(int h);
	void SetAB(int x, int y);
	void SetShootingDirection(char d);
	int GetHitValue();
	char GetShootingDirection();
	void GetShot(int x, int y, Bot &clone, bool& one_more);
	bool RepeatedShot(int x, int y);
	void ReverseDirection(int x, int y);
};

Bot::Bot() : a(0), b(0), hit(0), checker(0), direction('o') {}// x ir y koordinaciu alterntyvos, saudimo rezimo kintamasis, saudimo vietos nustatymo kintamasis, saudimo krypties kintamasis
Bot::~Bot() {}

//metodas boto saudimui
void Bot::Shoot(int& x, int& y)
{
	while (true)
	{
		if (hit == 1)	
		{
			checker = 0;
			int shot = 0;
			
			while (true)
			{
				shot = rand() % 4;
				if (shot == 0 && b != 1)
				{
					break;
				}
				else if (shot == 1 && a != 10)
				{
					break;
				}
				else if (shot == 2 && b != 10)
				{
					break;
				}
				else if(shot == 3 && a!=1)
				{
					break;
				}
			}

			switch (shot)
			{
			case 0:
				y = b - 1;
				x = a;
				direction='u';
				break;
			case 1:
				y = b;
				x = a + 1;
				direction = 'r';
				break;
			case 2:
				y = b + 1;
				x = a;
				direction = 'd';
				break;
			case 3:
				y = b;
				x = a - 1;
				direction = 'l';
				break;
			default:
				direction = 'o';
				throw "  Enemy's ships are defective";
				break;
			}
			break;
		}

		else if (hit == 2)		
		{
			checker = 0;
			hit = 1;
			continue;
		}
		else if (hit == 3)		
		{
			checker = 0;
				if (direction == 'u' && b == 1)
				{
					hit=4;
					direction='d';
					continue;
				}
				else if (direction == 'r' && a == 10)
				{
					hit = 4;
					direction = 'l';
					continue;
				}
				else if (direction == 'd' && b == 10)
				{
					hit = 4;
					direction = 'u';
					continue;
				}
				else if (direction == 'l' && a == 1)
				{
					hit = 4;
					direction = 'r';
					continue;
				}
			
			switch (direction)
			{
			case 'u':
				y = b - 1;
				x = a;
				break;
			case 'r':
				y = b;
				x = a + 1;
				break;
			case 'd':
				y = b + 1;
				x = a;
				break;
			case 'l':
				y = b;
				x = a - 1;
				break;
			default:
				throw "  Enemy's ships are defective";
				break;

			}
		break;
		}

		else if (hit == 4)
		{
		checker++;
			switch (direction)
			{
			case 'u':
				y = b - checker;
				x = a;
				break;
			case 'r':
				y = b;
				x = a + checker;
				break;
			case 'd':
				y = b + checker;
				x = a;
				break;
			case 'l':
				y = b;
				x = a - checker;
				break;
			default:
				direction = 'o';
				break;
			}

			break;
		}

		else
		{
			y = rand() % 10 + 1;
			x = rand() % 10 + 1;
			direction = 'o';
			hit = 0;
			break;
		}
	}
}

//metodas hit laukui nustatyti
void Bot::SetHitValue(int h)
{
	hit = h;
}

//metodas a ir b laukams nustatyti
void Bot::SetAB(int x, int y)
{
	a = x;
	b = y;
}

//metodas saudimo krypties laukui nustatyti
void Bot::SetShootingDirection(char d)
{
	direction = d;
}

//metodas hit lauko reiksmes padavimui
int Bot::GetHitValue()
{
	return hit;
}

//metodas saudimo krypties lauko reiksmes padavimui
char Bot::GetShootingDirection()
{
	return direction;
}

//metodas botui suviams gauti
void Bot::GetShot(int x, int y, Bot &clone, bool& one_more)
{
	if (field[y][x] == "#")
	{
		one_more = 1;
		if (field[y - 1][x] != "#" &&
			field[y + 1][x] != "#" &&
			field[y][x - 1] != "#" &&
			field[y][x + 1] != "#" &&
			field[y - 1][x] != "+" &&
			field[y + 1][x] != "+" &&
			field[y][x - 1] != "+" &&
			field[y][x + 1] != "+")
		{
			field[y][x] = "X";
			clone.field[y][x] = "X";
		}
		else
		{
			field[y][x] = "+";
			clone.field[y][x] = "+";
		}

		ship_points--;
		cout << "  Good shot! Shoot again!" << endl;
		Sleep(after_shot_sleep_time);
	}

	else
	{
		one_more = 0;
		field[y][x] = "O";
		clone.field[y][x] = "O";
		cout << "  You missed..." << endl;
		Sleep(after_shot_sleep_time);
	}
}

//metodas patikrinimui ar zaidejas i atinkama vieta jau saude
bool Bot::RepeatedShot(int x, int y)
{
	if (field[y][x] == "+" || field[y][x] == "X" || field[y][x] == "O")
	{
		cout << "  You already shoot here, choose another position!" << endl;
		return true;
	}
	return false;
}

void Bot::ReverseDirection(int x, int y)
{
	switch (direction)
	{
	case 'u':
		a = x;
		b = y + 1;
		direction = 'd';
		break;
	case 'r':
		a = x - 1;
		b = y;
		direction = 'l';
		break;
	case 'd':
		a = x;
		b = y - 1;
		direction = 'u';
		break;
	case 'l':
		a = x + 1;
		b = y;
		direction = 'r';
		break;
	default:
		a = x;
		b = y;
		direction = 'o';
		throw "  Enemy's ships are defective";
		break;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//isvestine, zaidejo Player klase, kuri paveldi bazine Entity klase
class Player : public Entity
{
public:
	void Shoot(int& x, int& y);
	void GetShot(int x, int y, Bot& hit, bool& one_more);
	bool UselessShot(int x, int y, Bot& hit);
	bool NotSmartShot(int x, int y, Bot& hit);
};

//metodas zaidejo saudymui
void Player::Shoot(int& x, int& y)
{
	cout << "  Your turn to shoot!" << endl;
	cout << x_y_coordinates;
	cin >> x >> y;
}

//metodas zaidejui suviams gauti
void Player::GetShot(int x, int y,Bot& hit,bool& one_more)
{
	if (field[y][x] == "#")
	{
		one_more = 1;
		if (field[y - 1][x] != "#" &&
			field[y + 1][x] != "#" &&
			field[y][x - 1] != "#" &&
			field[y][x + 1] != "#" &&
			field[y - 1][x] != "+" &&
			field[y + 1][x] != "+" &&
			field[y][x - 1] != "+" &&
			field[y][x + 1] != "+")
		{
			field[y][x] = "X";
			hit.SetHitValue(0);
			hit.SetAB(0, 0);
		}

		else
		{
			field[y][x] = "+";

			if (hit.GetHitValue() == 0)
			{
				hit.SetHitValue(1);
				hit.SetAB(x,y);
			}

			else if (hit.GetHitValue() == 1)
			{
				hit.SetHitValue(3);
				hit.SetAB(x, y);
			}

			else if (hit.GetHitValue() == 3)
			{
				if (hit.GetShootingDirection() == 'u' && (field[y - 1][x] == "O" || field[y - 1][x] == "+"))
				{
					hit.SetShootingDirection('d');
					hit.SetHitValue(4);
					hit.SetAB(x, y);
				}

				else if (hit.GetShootingDirection() == 'r' && (field[y][x + 1] == "O" || field[y][x + 1] == "+"))
				{
					hit.SetShootingDirection('l');
					hit.SetHitValue(4);
					hit.SetAB(x, y);
				}

				else if (hit.GetShootingDirection() == 'd' && (field[y + 1][x] == "O" || field[y + 1][x] == "+"))
				{
					hit.SetShootingDirection('u');
					hit.SetHitValue(4);
					hit.SetAB(x, y);
				}

				else if (hit.GetShootingDirection() == 'l' && (field[y][x - 1] == "O" || field[y][x - 1] == "+"))
				{
					hit.SetShootingDirection('r');
					hit.SetHitValue(4);
					hit.SetAB(x, y);
				}

				else
				{
					hit.SetAB(x, y);
				}
				
			}

			else if(hit.GetHitValue()==4)
			{
				hit.SetHitValue(3);
				hit.SetAB(x, y);
			}

			else
			{
				hit.SetHitValue(0);
				hit.SetAB(0, 0);
				hit.SetShootingDirection('o');
			}
			
		}

		ship_points--;
		cout << "  You got hit by the enemy!" << endl;
		Sleep(after_shot_sleep_time);
	}

	else
	{
		if (hit.GetHitValue() == 4)
		{
			one_more = 1;
			hit.SetHitValue(0);
			hit.SetAB(0, 0);
			hit.SetShootingDirection('o');
		}

		else
		{
			one_more = 0;
			field[y][x] = "O";

			if (hit.GetHitValue() == 1)
			{
				hit.SetHitValue(2);
			}
			else if (hit.GetHitValue() == 3)
			{
				hit.SetHitValue(4);
				hit.ReverseDirection(x, y);
			}

			cout << "  Enemy missed" << endl;
			Sleep(after_shot_sleep_time);
		}
	}
}

//metodas patikrinti ar botas jau saude i atitinkama vieta ir ar jam verta i konkrecia vieta sauti
bool Player::UselessShot(int x, int y, Bot& hit)
{
	if (field[y][x] == "+" || field[y][x] == "X" || field[y][x] == "O")
	{
		if (hit.GetHitValue() == 3 && field[y][x] == "O")
		{
			hit.SetHitValue(4);
			hit.ReverseDirection(x, y);
		}

		else if (hit.GetHitValue() == 4 && field[y][x] == "O")
		{
			hit.SetHitValue(0);
			hit.SetAB(0, 0);
			hit.SetShootingDirection('o');
		}

		return true;
	}

	if (hit.GetHitValue() == 0)
	{
		for (int j = -1; j < 2; j++)
		{
			for (int i = -1; i < 2; i++)
			{
				if ((field[y + i][x + j] == "+" || field[y + i][x + j] == "X") && hit.GetHitValue() == 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}



