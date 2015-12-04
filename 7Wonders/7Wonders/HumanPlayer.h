#pragma once
#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(std::vector<Card>* discard);
	~HumanPlayer();
protected:
	virtual void pickCard();
};

