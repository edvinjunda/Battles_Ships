#pragma once
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
	virtual void Sauti() = 0;

};

Entity::Entity() : laivas1(4), laivas2(3), laivas3(2), laivas4(1)
{
}

Entity::~Entity()
{
}


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
};

Player::Player(){}

Player::~Player(){}