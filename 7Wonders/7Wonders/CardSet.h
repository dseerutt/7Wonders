#pragma once
#include <vector>
#include "Card.h"

class CardSet : public std::vector<Card*>
{
public:
	CardSet();
	~CardSet();
	void shuffle();
};

