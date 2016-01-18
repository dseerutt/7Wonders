#pragma once
class Marvel
{
public:
	int marvelLevel;
	int marvelMaxLevel;
public:
	Marvel(int level);
	~Marvel();
	int getMarvelLevel();
	int getMarvelMaxLevel();
	virtual void upgrade() = 0;
	virtual bool canUpgrade() = 0;
};

