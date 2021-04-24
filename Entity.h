#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "Field.h"

using namespace std;


class Entity
{
protected:
	int laivai;
public:
	Entity();
	virtual ~Entity();
public:
	virtual string GetShot() = 0;
	

};

Entity::Entity() : laivai(10){}
Entity::~Entity(){}


class Bot : public Entity, public Field
{
public:
	Bot();
	~Bot();
public:
	string GetShot();

};

Bot::Bot(){}
Bot::~Bot(){}

string Bot::GetShot()
{
	return "1";

}


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