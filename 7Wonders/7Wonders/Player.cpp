#include "Player.h"


Player::Player(std::vector<Card>* discard) : m_discard(discard), m_hand(), m_board(), m_cardToPlay(nullptr)
{
}

Player::~Player()
{
}

void Player::setHand(const std::vector<Card>& newHand)
{
	m_hand.clear();
	for (unsigned int i = 0; i < newHand.size(); i++)
	{
		m_hand.push_back(newHand.at(i));
	}
}

const std::vector<Card>& Player::getHand() const
{
	return m_hand;
}

void Player::prepareTurn()
{
	if (m_hand.size() <= 1)
	{
		if (m_hand.size() == 0)
		{
			std::cerr << "Attention : un joueur ne possède aucune carte en main au debut du tour." << std::endl;
			return;
		}
		m_discard->push_back(m_hand.at(0));
	}
	else
	{
		pickCard();
	}
}

void Player::playTurn()
{
	m_board.push_back(*m_cardToPlay);

	std::vector<Card>::iterator cardToErase;
	for (auto it = m_hand.begin(); it != m_hand.end(); ++it)
	{
		Card* card = &(*it);
		if (card == m_cardToPlay)
		{
			cardToErase = it;
		}
	}
	m_hand.erase(cardToErase);
}
