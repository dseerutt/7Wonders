#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(CardSet* discard) : Player(discard)//, m_mcts(*this)
{
}

ComputerPlayer::~ComputerPlayer()
{
}

void ComputerPlayer::pickCard()
{
	const CardSet cards = getPlayableCards();
	/*std::mt19937 mt;
	std::vector<int> moves;

	game::GameState state = m_mcts.get_state();
	for (unsigned int i = 0; i < MCTS_ITERATIONS_NUMBER; i++)
	{
		m_mcts.playout(mt);
		//moves
		m_mcts.set_state(state);
	}*/

	m_cardToPlay = cards.at(0);
}
