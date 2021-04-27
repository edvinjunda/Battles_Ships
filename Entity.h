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
public:
	Bot() : a(0), b(0), hit(0) {}
	~Bot() {}
public:
	void Shoot(int& x, int& y);
	void GetShot(int x, int y, Bot &clone);
	bool RepeatedShot(int x, int y);

};

void Bot::Shoot(int& x, int& y)
{
	cout << "Now it's enemy's turn to shoot!" << endl;

	Sleep(2000);

	if (a != 0 && b != 0&&hit==1)
	{
		int shot = rand() % 4;

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
			throw "Bot has just passed away, press F for respect.";
			break;
		}
	}

	else
	{
		y = rand() % 10 + 1;
		x = rand() % 10 + 1;
	}

	
}

void Bot::GetShot(int x, int y, Bot &clone)
{
	if (field[y][x] == "#")
	{
		/*int start = y;
		int i = 0;
		while (true)
		{
			i++;
			if (field[y - i][x] != "#" &&
				field[y - i][x] == "+")
				start = y - i;
			else if(field[y - 1][x] == "~" || field[y - 1][x] != "O")
			{
				start = y - i + 1;
				
			}

		
		}*/

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
		
	}

	else
	{
		field[y][x] = "O";
		clone.field[y][x] = "O";
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
	void GetShot(int x, int y);
	
};

void Player::Shoot(int& x, int& y)
{
	cout << "Your turn to shoot!" << endl;
	cout << "Enter x and y coordinates: " << endl;
	cin >> x >> y;
	x++;
	y++;
}

void Player::GetShot(int x, int y)
{
	if (field[y][x] == "#")
	{
		/*int start = y;
		int i = 0;
		while (true)
		{
			i++;
			if (field[y - i][x] != "#" &&
				field[y - i][x] == "+")
				start = y - i;
			else if(field[y - 1][x] == "~" || field[y - 1][x] != "O")
			{
				start = y - i + 1;

			}


		}*/

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
		}
		else
		{
			field[y][x] = "+";
		}

	}

	else
	{
		field[y][x] = "O";
	}
}