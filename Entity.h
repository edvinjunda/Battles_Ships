#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "Field.h"

using namespace std;


class Entity
{
protected:
	int laivas1, laivas2, laivas3, laivas4;
public:
	Entity();
	virtual ~Entity();
public:
	virtual string GetShot() = 0;
	

};

Entity::Entity() : laivas1(4), laivas2(3), laivas3(2), laivas4(1){}
Entity::~Entity(){}

//class Player : public Entity, public Field {};


class Bot : public Entity, public Field
{
public:
	Bot();
	~Bot();

private:

};

Bot::Bot(){}
Bot::~Bot(){}


class Player : public Entity, public Field
{
public:
	Player();
	~Player();
public:
	string GetShot();
};

Player::Player(){}
Player::~Player(){}

string Player::GetShot()
{
	return "1";
	
}