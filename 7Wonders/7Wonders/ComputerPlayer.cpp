#include "ComputerPlayer.h"


ComputerPlayer::ComputerPlayer(CardSet* discard) : Player(discard)
{
}


ComputerPlayer::~ComputerPlayer()
{
}

void ComputerPlayer::pickCard()
{
	m_cardToPlay = m_hand.at(0);
}