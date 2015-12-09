#include "HumanPlayer.h"
#include <string>

using namespace std;

HumanPlayer::HumanPlayer(CardSet* discard) : Player(discard)
{
}

HumanPlayer::~HumanPlayer()
{
}

void HumanPlayer::pickCard()
{
	cout << "Pick a card" << endl;
	for (unsigned int i = 0; i < m_hand.size(); i++)
	{
		cout << i << ". " << m_hand.at(i)->m_name << endl;
	}
	unsigned int choice;
	do
	{
		cout << "Select : ";
		cin >> choice;
	}
	while (choice >= m_hand.size());

	m_cardToPlay = m_hand.at(choice);
}