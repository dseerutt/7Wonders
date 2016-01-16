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
	cout << displayResourceManager("You") << endl;
	cout << displayResourceManager("Left Neighbor") << endl;
	cout << displayResourceManager("Right Neighbor") << endl;
	cout << "You have " << money << " gold coins" << endl;
	cout << "You have " << military << " army unities" << endl;
	cout << "Pick a card" << endl;
	for (unsigned int i = 0; i < m_hand.size(); i++)
	{
		cout << i << ". " << m_hand.at(i)->m_name << endl;
	}
	cout << m_hand.size() << ". " << "Discard a card" << endl;
	unsigned int choice;
	bool continueLoop = false;
	do
	{
		cout << "Select : ";
		cin >> choice;
		continueLoop = false; 
		if (choice == m_hand.size())
		{
			defausse = true;
			continueLoop = true;
			cout << "Select the card to discard" << endl;
		}
		else {
			if (choice >= m_hand.size())
			{
				continueLoop = true;
				cout << "Please select a card into the given range" << endl;
			}
			else
			{
				if (canBuyWithNeighbor(m_hand.at(choice)) == -1)
				{
					continueLoop = true;
					cout << "You can't buy this card, try another one" << endl;;
				}
			}
		}
		
	}
	while (continueLoop);

	m_cardToPlay = m_hand.at(choice);
}