#include "DefaultMarvel.h"


DefaultMarvel::DefaultMarvel() : Marvel(3)
{
}


DefaultMarvel::~DefaultMarvel()
{
}

void DefaultMarvel::upgrade()
{
	if (canUpgrade())
	{
		switch (marvelLevel)
		{
		case 0:
			upgrade1();
			break;
		case 1:
			upgrade2();
			break;
		case 2:
			upgrade3();
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

void DefaultMarvel::upgrade1()
{

}

void DefaultMarvel::upgrade2()
{

}

void DefaultMarvel::upgrade3()
{

}
