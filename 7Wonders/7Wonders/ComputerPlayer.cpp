#include "ComputerPlayer.h"


ComputerPlayer::ComputerPlayer(std::vector<Card>* discard) : Player(discard)
{
}


ComputerPlayer::~ComputerPlayer()
{
}

void ComputerPlayer::pickCard()
{
	m_cardToPlay = &(m_hand.at(0));
}