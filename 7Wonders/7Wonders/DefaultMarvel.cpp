#include "DefaultMarvel.h"


DefaultMarvel::DefaultMarvel() : Marvel(3)
{
}


DefaultMarvel::~DefaultMarvel()
{
}

void DefaultMarvel::upgrade(Player* p, World* w)
{
	if (canUpgrade())
	{
		switch (marvelLevel)
		{
		case 0:
			upgrade1(p, w);
			break;
		case 1:
			upgrade2(p,w);
			break;
		case 2:
			upgrade3(p,w);
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

void DefaultMarvel::upgrade1(Player* p, World* w)
{
	p->upgradeMarvelMoney(2);
}

void DefaultMarvel::upgrade2(Player* p, World* w)
{
	p->upgradeMarvelMoney(4);

}

void DefaultMarvel::upgrade3(Player* p, World* w)
{
	p->upgradeMarvelMoney(6);

}
