#pragma once
#include "Player.h"
//#include "MCTSImplementation.h"

#define MCTS_ITERATIONS_NUMBER 100

class ComputerPlayer : public Player
{
private:
	//game::MCTSImplementation m_mcts;
public:
	ComputerPlayer(CardSet* discard);
	~ComputerPlayer();
protected:
	virtual void pickCard();
};

