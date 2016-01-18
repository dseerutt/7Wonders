#include "DefaultMarvel.h"


DefaultMarvel::DefaultMarvel() : Marvel(3)
{
}


DefaultMarvel::~DefaultMarvel()
{
}

void DefaultMarvel::upgrade(Player* p)
{
	if (canUpgrade())
	{
		switch (marvelLevel)
		{
		case 0:
			upgrade1(p);
			break;
		case 1:
			upgrade2(p);
			break;
		case 2:
			upgrade3(p);
			break;
		default:
			break;
		}
	}
}

bool DefaultMarvel::canUpgrade()
{
	if (marvelLevel == 3)
	{
		return false;
	}
	return true;
}

void DefaultMarvel::upgrade1(Player* p)
{

}

void DefaultMarvel::upgrade2(Player* p)
{

}

void DefaultMarvel::upgrade3(Player* p)
{

}
