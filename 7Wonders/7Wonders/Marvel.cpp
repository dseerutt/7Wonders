#include "Marvel.h"


Marvel::Marvel(int level)
{
	marvelLevel = 0;
	marvelMaxLevel = level;
	marvelMoney = 0;
	marvelScore = 0;
}


Marvel::~Marvel()
{
}

int Marvel::getMarvelLevel()
{
	return marvelLevel;
}

int Marvel::getMarvelMaxLevel()
{
	return marvelMaxLevel;
}

int Marvel::getMarvelScore()
{
	return marvelScore;
}

int Marvel::getMarvelMoney()
{
	return marvelMoney;
}
