#include "DefaultMarvel.h"

std::array<int, RESOURCES_COUNT> DefaultMarvel::up1 = { 1, 0, 0, 0, 0, 0, 0 };
std::array<int, RESOURCES_COUNT> DefaultMarvel::up2 = { 2, 0, 0, 0, 0, 0, 0 };
std::array<int, RESOURCES_COUNT> DefaultMarvel::up3 = { 3, 0, 0, 0, 0, 0, 0 };

DefaultMarvel::DefaultMarvel() : Marvel(3)
{
}


DefaultMarvel::~DefaultMarvel()
{
}

void DefaultMarvel::upgrade(std::vector<std::array<int, RESOURCES_COUNT> > resources)
{
	if (canUpgrade(resources))
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

bool DefaultMarvel::canUpgrade(std::vector<std::array<int, RESOURCES_COUNT> > resources)
{
	if (marvelLevel == 3)
	{
		return false;
	}
	switch (marvelLevel)
	{
	case 0:
		return canUpgrade1(resources);
		break;
	case 1:
		return canUpgrade2(resources);
		break;
	case 2:
		return canUpgrade3(resources);
		break;
	default:
		break;
	}
}

void DefaultMarvel::upgrade1()
{
	marvelLevel++;
	marvelMoney = 2;
	marvelScore += 2;
}

void DefaultMarvel::upgrade2()
{
	marvelLevel++;
	marvelMoney = 4;
	marvelScore += 4;
}

void DefaultMarvel::upgrade3()
{
	marvelLevel++;
	marvelMoney = 6;
	marvelScore += 6;
}


bool DefaultMarvel::canUpgrade1(std::vector<std::array<int, RESOURCES_COUNT> > resources)
{
	bool value = true;
	for (int i = 0; i < resources.size(); i++)
	{
		value = true;
		for (int j = 0; j < RESOURCES_COUNT; j++)
		{
			if (up1.at(j) > resources.at(i).at(j))
			{
				value = false;
				break;
			}
		}
		if (value)
		{
			return true;
		}
	}
	return false;
}

bool DefaultMarvel::canUpgrade2(std::vector<std::array<int, RESOURCES_COUNT> > resources)
{
	bool value = true;
	for (int i = 0; i < resources.size(); i++)
	{
		value = true;
		for (int j = 0; j < RESOURCES_COUNT; j++)
		{
			if (up2.at(j) > resources.at(i).at(j))
			{
				value = false;
				break;
			}
		}
		if (value)
		{
			return true;
		}
	}
	return false;
}

bool DefaultMarvel::canUpgrade3(std::vector<std::array<int, RESOURCES_COUNT> > resources)
{
	bool value = true;
	for (int i = 0; i < resources.size(); i++)
	{
		value = true;
		for (int j = 0; j < RESOURCES_COUNT; j++)
		{
			if (up3.at(j) > resources.at(i).at(j))
			{
				value = false;
				break;
			}
		}
		if (value)
		{
			return true;
		}
	}
	return false;
}
