#pragma once
#include "Player.h"

#define MCTS_ITERATIONS_NUMBER 100

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(CardSet* discard, int rec);
	~ComputerPlayer();
protected:
	virtual void pickCard();
};

