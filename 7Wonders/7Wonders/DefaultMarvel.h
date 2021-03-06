#pragma once
#include "Marvel.h"
class DefaultMarvel : public Marvel
{
public:
	DefaultMarvel();
	~DefaultMarvel();
	virtual void upgrade(std::vector<std::array<int, RESOURCES_COUNT> > resources);
	virtual bool canUpgrade(std::vector<std::array<int, RESOURCES_COUNT> > resources);
	void upgrade1();
	void upgrade2();
	void upgrade3();
	bool canUpgrade1(std::vector<std::array<int, RESOURCES_COUNT> > resources);
	bool canUpgrade2(std::vector<std::array<int, RESOURCES_COUNT> > resources);
	bool canUpgrade3(std::vector<std::array<int, RESOURCES_COUNT> > resources);
	static std::array<int, RESOURCES_COUNT> up1;
	static std::array<int, RESOURCES_COUNT> up2;
	static std::array<int, RESOURCES_COUNT> up3;
};

