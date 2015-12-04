#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(std::vector<Card>* discard);
	~ComputerPlayer();
protected:
	virtual void pickCard();
};

