#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <conio.h>
#include "Field.h"
#include "Constants.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Entity : public Field
{
protected:
	int ship_points;
public:
	Entity();
	virtual ~Entity();
public:
	virtual void Shoot(int& x, int& y)=0;
	int GetShipPoints();
	virtual void GetShot(int x, int y);
};

Entity::Entity() :ship_points(20){}
Entity::~Entity(){}

int Entity::GetShipPoints()
{
	return ship_points;
}

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Bot : public Entity
{
private:
	int a, b, hit, checker;
	char direction;
public:
	Bot() : a(0), b(0), hit(0),checker(0),direction('o') {}
	~Bot() {}
public:
	void Shoot(int& x, int& y);
	void SetHitValue(int h);
	void SetAB(int x, int y);
	void SetShootingDirection(char d);
	int GetHitValue();
	char GetShootingDirection();
	void GetShot(int x, int y, Bot &clone, bool& one_more);
	bool RepeatedShot(int x, int y);
};

void Bot::Shoot(int& x, int& y)
{
	while (true)
	{
		if (hit == 1)	
		{

			/*cout << 1 << endl;//////////////////////////////
			cout << checker << " c" << endl;*/
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
			/*cout << checker << " c" << endl;
			cout << 2 << endl;*/
			checker = 0;
			hit = 1;
			continue;
		}
		else if (hit == 3)		
		{
			/*cout << checker << " c" << endl;
				cout << direction << endl;//////////////////////////////
				Sleep(2000);*/
			checker = 0;
				if (direction == 'u' && b == 1)
				{
					hit=4;//SetHitValue(0);
					direction='d';
					continue;
				}
				else if (direction == 'r' && a == 10)
				{
					hit = 4;//SetHitValue(0);
					direction = 'l';
					continue;
				}
				else if (direction == 'd' && b == 10)
				{
					hit = 4;//SetHitValue(0);
					direction = 'u';
					continue;
				}
				else if (direction == 'l' && a == 1)
				{
					hit = 4;//SetHitValue(0);
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
			//system("pause");
		break;
		}

		else if (hit == 4)
		{
		checker++;
		/*cout << 4 << ' ' << checker << endl;
		system("pause");*/
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
				throw "  Enemy's ships are defective";
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

void Bot::SetHitValue(int h)
{
	hit = h;
}

void Bot::SetAB(int x, int y)
{
	a = x;
	b = y;
}

void Bot::SetShootingDirection(char d)
{
	direction = d;
}

int Bot::GetHitValue()
{
	return hit;
}

char Bot::GetShootingDirection()
{
	return direction;
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

bool Bot::RepeatedShot(int x, int y)
{
	if (field[y][x] == "+" || field[y][x] == "X" || field[y][x] == "O")
	{
		cout << "  You already shoot here, choose another position!" << endl;
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
	bool UselessShot(int x, int y, Bot& hit);
};

void Player::Shoot(int& x, int& y)
{
	cout << "  Your turn to shoot!" << endl;
	cout << x_y_coordinates;
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
					/*cout << "3u" << endl;
					system("pause");*/

					hit.SetShootingDirection('d');
					hit.SetHitValue(4);//hit.SetHitValue(0);
					hit.SetAB(x, y);//hit.SetAB(0, 0);
					
				}

				else if (hit.GetShootingDirection() == 'r' && (field[y][x + 1] == "O" || field[y][ x + 1] == "+"))
				{
					/*cout << "3r" << endl;
					system("pause");*/

					hit.SetShootingDirection('l');
					hit.SetHitValue(4);//hit.SetHitValue(0);
					hit.SetAB(x, y);//hit.SetAB(0, 0);
				}
				else if (hit.GetShootingDirection() == 'd' && (field[y+1][x] == "O" || field[y+1][x] == "+"))
				{
					/*cout << "3d" << endl;
					system("pause");*/

					hit.SetShootingDirection('u');
					hit.SetHitValue(4);//hit.SetHitValue(0);
					hit.SetAB(x, y);//hit.SetAB(0, 0);
				}
				else if (hit.GetShootingDirection() == 'l' && (field[y][x - 1] == "O" || field[y][x - 1] == "+"))
				{
					/*cout << "3l" << endl;
					system("pause");*/

					hit.SetShootingDirection('r');
					hit.SetHitValue(4);//hit.SetHitValue(0);
					hit.SetAB(x, y);//hit.SetAB(0, 0);
				}

				else
				{
					/*cout << "3o" << endl;
					system("pause");*/

					hit.SetAB(x, y);
				}
				
			}
			else if(hit.GetHitValue()==4)
			{
				hit.SetHitValue(3);
			}

			else
			{
				hit.SetHitValue(0);
				hit.SetAB(0, 0);
				hit.SetShootingDirection('o');
				throw "  Enemy's ships are defective";
			}
			
		}

		ship_points--;
		cout << "  You got hit by the enemy!" << endl;
		Sleep(after_shot_sleep_time);
	}

	else //if(field[y][x] == "~")
	{
		one_more = 0;
		field[y][x] = "O";
		if (hit.GetHitValue() == 1)
		{
			hit.SetHitValue(2);
		}
		else if(hit.GetHitValue() == 3)
		{
			hit.SetHitValue(4);//hit.SetHitValue(0);
			switch (hit.GetShootingDirection())
			{
			case 'u':
				hit.SetAB(x, y + 1);
				hit.SetShootingDirection('d');
				break;
			case 'r':
				hit.SetAB(x - 1, y);
				hit.SetShootingDirection('l');
				break;
			case 'd':
				hit.SetAB(x, y - 1);
				hit.SetShootingDirection('u');
				break;
			case 'l':
				hit.SetAB(x + 1, y);
				hit.SetShootingDirection('r');
				break;
			default:
				throw "  Enemy's ships are defective";
				hit.SetAB(x, y);
				hit.SetShootingDirection('o');
				break;
			}
		}

		else if (hit.GetHitValue() == 4)
		{
			/*cout << 4444 << endl;
			system("pause");*/

			field[y][x] = "~";
			hit.SetHitValue(0);
			hit.SetAB(0, 0);
			hit.SetShootingDirection('o');
		}
		cout << "  Enemy missed" << endl;
		Sleep(after_shot_sleep_time);
	}
}

bool Player::UselessShot(int x, int y, Bot& hit)
{
	if (field[y][x] == "+" || field[y][x] == "X" || field[y][x] == "O")
	{
		if (hit.GetHitValue() == 3)
		{
			/*cout << "repeated " << 3 << endl;
			system("pause");*/

			hit.SetHitValue(0);
			hit.SetAB(0, 0);
			hit.SetShootingDirection('o');
		}
		else if (hit.GetHitValue() == 4 && field[y][x] == "O")
		{
			/*cout << "repeated " << 4 << endl;
			system("pause");*/

			hit.SetHitValue(0); 
			hit.SetAB(0, 0);
			hit.SetShootingDirection('o');
		}
		return true;
	}

	for (int j = -1; j < 2; j++)
	{
		for (int i = -1; i < 2; i++)
		{
			if ((field[y + i][x + j] == "+" || field[y + i][x + j] == "X") && hit.GetHitValue()==0)
			{
				return true;
			}
		}
	}

	return false;
}

/*bool Player::UselessShot(int x, int y, Bot hit)
{
	
	

	if (true)
	{

	}

	return false;
}
*/