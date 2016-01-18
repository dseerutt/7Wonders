#pragma once
#include "Marvel.h"
class DefaultMarvel : public Marvel
{
public:
	DefaultMarvel();
	~DefaultMarvel();
	virtual void upgrade(Player* p);
	virtual bool canUpgrade();
	void upgrade1(Player* p);
	void upgrade2(Player* p);
	void upgrade3(Player* p);
};

