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
	//virtual string **GiveField();
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

};

void Bot::Shoot(int& x, int& y)
{
	;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Player : public Entity
{
public:
	void Shoot(int& x, int& y);

	
};

void Player::Shoot(int& x, int& y)
{
	cout << "Ivesti koordinates: " << endl;
	cin >> x >> y;
	x++;
	y++;
}