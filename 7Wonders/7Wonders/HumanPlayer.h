#pragma once
#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(CardSet* discard);
	~HumanPlayer();
protected:
	virtual void pickCard();
};

