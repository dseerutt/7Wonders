#pragma once
#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(CardSet* discard, int rec);
	~HumanPlayer();
protected:
	virtual void pickCard();
};

