#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(CardSet* discard, int rec) : Player(discard, rec)//, m_mcts(*this)
{
}

ComputerPlayer::~ComputerPlayer()
{
}

void ComputerPlayer::pickCard()
{
	const CardSet cards = getPlayableCards();
	if (cards.empty())
	{
		defausse = true;
		m_cardToPlay = getHand().at(0);
	}
	else {
		m_cardToPlay = cards.at(0);
	}

		
	//To build a wonder -> defausse = true; marvelTreatment = true;

	/*std::mt19937 mt;
	std::vector<int> moves;

	game::GameState state = m_mcts.get_state();
	for (unsigned int i = 0; i < MCTS_ITERATIONS_NUMBER; i++)
	{
	m_mcts.playout(mt);
	//moves
	m_mcts.set_state(state);
	}*/
}
