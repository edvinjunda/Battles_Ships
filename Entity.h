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
public:
	void Shoot(int& x, int& y);
	void GetShot(int x, int y, Bot &clone);
	bool RepeatedShot(int x, int y);

};

void Bot::Shoot(int& x, int& y)
{
	;
}

void Bot::GetShot(int x, int y, Bot &clone)
{
	if (field[y][x] == "#")
	{
		if (field[y - 1][x] != "#" &&
			field[y + 1][x] != "#" &&
			field[y][x - 1] != "#" &&
			field[y][x + 1] != "#")
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

	
};

void Player::Shoot(int& x, int& y)
{
	cout << "Enter x and y coordinations: " << endl;
	cin >> x >> y;
	x++;
	y++;
}