#pragma once
#include "Card.h"

class GreenCard : public Card
{
private:
	char m_type;
public:
	GreenCard(const std::string& name, char type);
	~GreenCard();

	char getType() const;
	virtual unsigned int getPoints() const;
	virtual unsigned int getPower() const;
};

