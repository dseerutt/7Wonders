#pragma once
#include <vector>
#include <array>
#include "Card.h"
class Marvel
{
protected:
	int marvelMoney;
	int marvelScore;
public:
	int marvelLevel;
	int marvelMaxLevel;
public:
	Marvel(int level);
	~Marvel();
	int getMarvelLevel();
	int getMarvelMaxLevel();
	int getMarvelMoney();
	int getMarvelScore();
	virtual void upgrade(std::vector<std::array<int, RESOURCES_COUNT> > resources) = 0;
	virtual bool canUpgrade(std::vector<std::array<int, RESOURCES_COUNT> > resources) = 0;
};

