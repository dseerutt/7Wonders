#pragma once
#include "Player.h"
#include "World.h"
class Marvel
{
public:
	int marvelLevel;
	int marvelMaxLevel;
public:
	Marvel(int level);
	~Marvel();
	int getMarvelLevel();
	int getMarvelMaxLevel();
	virtual void upgrade(Player* p, World* w) = 0;
	virtual bool canUpgrade() = 0;
};

