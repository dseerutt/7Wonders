#pragma once
#include "Marvel.h"
class DefaultMarvel : public Marvel
{
public:
	DefaultMarvel();
	~DefaultMarvel();
	virtual void upgrade(Player* p, World* w);
	virtual bool canUpgrade();
	void upgrade1(Player* p, World* w);
	void upgrade2(Player* p, World* w);
	void upgrade3(Player* p, World* w);
};

