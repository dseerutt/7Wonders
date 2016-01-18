#pragma once
class Marvel
{
protected:
	int marvelMoney;
	int marvelScore;
public:
	int marvelLevel;
	int marvelMaxLevel;
public:
	Marvel(int level);
	~Marvel();
	int getMarvelLevel();
	int getMarvelMaxLevel();
	int getMarvelMoney();
	int getMarvelScore();
	virtual void upgrade() = 0;
	virtual bool canUpgrade() = 0;
};

