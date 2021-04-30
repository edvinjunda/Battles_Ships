#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "Field.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Entity : public Field
{
protected:
	int laivai;
public:
	Entity();
	virtual ~Entity();
public:
	//virtual void Shoot()=0;
	virtual void GetShot(int x, int y);
	//virtual void Shoot(string **f);


};

Entity::Entity() : laivai(10){}
Entity::~Entity(){}

void Entity::GetShot(int x, int y)
{
	//cout << x <<' '<< y << endl;
	if(field[y][x]=="#")
		field[y][x] = "+";
	else
	{
		field[y][x] = "O";
	}
}

/*void Entity::Shoot(string **f)
{
	f[rand() % 10 + 1][rand() % 10 + 1] = "+";
}*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Bot : public Entity
{
private:
	int a, b, hit;
	char direction;
public:
	Bot() : a(0), b(0), hit(0),direction('o') {}
	~Bot() {}
public:
	void Shoot(int& x, int& y);
	void SetHit(int h);
	void SetAB(int x, int y);
	int GetHitValue();
	void GetShot(int x, int y, Bot &clone, bool& one_more);
	bool RepeatedShot(int x, int y);

};

void Bot::Shoot(int& x, int& y)
{
	
	do
	{
		if (hit == 1)		//a != 0 && b != 0 && 
		{
			int shot = 0;

			while (true)
			{
				cout << 1 << endl;
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
				break;
			case 1:
				y = b;
				x = a + 1;
				break;
			case 2:
				y = b + 1;
				x = a;
				break;
			case 3:
				y = b;
				x = a - 1;
				break;
			default:
				//throw "Enemy's ships are defective";
				break;
			}
			break;
		}

		else if (hit == 2)		//a != 0 && b != 0 && 
		{
			hit = 1;
			continue;
		}
		/*
			else if (hit == 3)		//a != 0 && b != 0 &&
			{
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
					//throw "Enemy's ships are defective";
					break;

				}
			}

			else if (hit == 4)
			{
				switch (direction)
				{
				case 'u':
					direction = 'd';
					break;
				case 'r':
					direction = 'l';
					break;
				case 'd':
					direction = 'u';
					break;
				case 'l':
					direction = 'r';
					break;
				default:
					//throw "Enemy's ships are defective";
					break;

				}
			}
		*/
		else
		{
			y = rand() % 10 + 1;
			x = rand() % 10 + 1;
			break;
		}
	} while (true);
	
}

void Bot::SetHit(int h)
{
	hit = h;
}

int Bot::GetHitValue()
{
	return hit;
}

void Bot::SetAB(int x, int y)
{
	a = x;
	b = y;
}

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
		cout << "Good shot! Shoot again!" << endl;
		///////////////////////////////////////////////////////////////////////////////////////////Sleep(3000);
	}

	else
	{
		one_more = 0;
		field[y][x] = "O";
		clone.field[y][x] = "O";
		cout << "You missed..." << endl;
		///////////////////////////////////////////////////////////////////////////////////////////Sleep(3000);
	}
}

bool Bot::RepeatedShot(int x, int y)
{
	if (field[y][x] == "+" || field[y][x] == "X" || field[y][x] == "O")
	{
		cout << "You already shoot here, choose another position!" << endl;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Player : public Entity
{
public:
	void Shoot(int& x, int& y);
	void GetShot(int x, int y, Bot& hit, bool& one_more);
	bool RepeatedShot(int x, int y);
};

void Player::Shoot(int& x, int& y)
{
	cout << "Your turn to shoot!" << endl;
	cout << "Enter x and y coordinates: " << endl;
	cin >> x >> y;
}

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
			hit.SetHit(0);
			hit.SetAB(0, 0);
		}
		else
		{
			field[y][x] = "+";
			if (hit.GetHitValue() == 0)
			{
				hit.SetHit(1);
				hit.SetAB(x,y);
			}
			else if (hit.GetHitValue() == 1)
			{
				hit.SetHit(3);
				hit.SetAB(x, y);
				//hit.SetShootingDirection();
			}
			/*else if (hit.GetHitValue() == 2)
			{
				hit.SetHit(3);
				//hit.SetShootingDirection();
			}*/

		}
		cout << "You got hit by the enemy!" << endl;
		Sleep(2500);
	}

	else
	{
		one_more = 0;
		field[y][x] = "O";
		if (hit.GetHitValue() == 1)
		{
			hit.SetHit(2);
			//hit.SetAB(x, y);
		}
		else if(hit.GetHitValue() == 3)
		{
			hit.SetHit(4);
			//hit.SetShootingDirection();
		}
		cout << "Enemy missed" << endl;
		Sleep(2500);
	}
}

bool Player::RepeatedShot(int x, int y)
{
	if (field[y][x] == "+" || field[y][x] == "X" || field[y][x] == "O")
	{
		return true;
	}
	return false;
}
