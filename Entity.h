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
	virtual string GiveField() = 0;


};

Entity::Entity() : laivai(10){}
Entity::~Entity(){}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Bot : public Entity//, public Field
{
public:
	Bot();
	~Bot();
public:
	string GiveField();
};

Bot::Bot(){}
Bot::~Bot(){}

string Bot::GiveField()
{
	return **field;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Player : public Entity//, public Field
{
public:
	Player();
	~Player();
public:
	string GiveField();

};

Player::Player(){}
Player::~Player(){}

string Player::GiveField()
{
	return **field;
}