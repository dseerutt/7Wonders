#pragma once
#include "Card.h"

using namespace std;

class GrayCard :
	public Card
{
public:
	GrayCard(const std::string& name, const std::string& production, std::string cardName);
	~GrayCard();

	virtual unsigned int getPoints() const;
	virtual unsigned int getPower() const;
	string getProduction();
};

