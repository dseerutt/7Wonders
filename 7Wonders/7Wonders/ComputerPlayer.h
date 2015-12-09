#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(CardSet* discard);
	~ComputerPlayer();
protected:
	virtual void pickCard();
};

