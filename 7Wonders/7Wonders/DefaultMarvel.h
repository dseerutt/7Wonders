#pragma once
#include "Marvel.h"
class DefaultMarvel : public Marvel
{
public:
	DefaultMarvel();
	~DefaultMarvel();
	virtual void upgrade();
	virtual bool canUpgrade();
	void upgrade1();
	void upgrade2();
	void upgrade3();
};

