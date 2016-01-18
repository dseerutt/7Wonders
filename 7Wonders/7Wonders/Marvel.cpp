#include "Marvel.h"


Marvel::Marvel(int level)
{
	marvelLevel = 0;
	marvelMaxLevel = level;
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
