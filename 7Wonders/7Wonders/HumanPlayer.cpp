#include "HumanPlayer.h"
#include <string>

using namespace std;


HumanPlayer::HumanPlayer(CardSet* discard, int rec) : Player(discard, rec)
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
	cout << "You have " << military << " army unities (" << leftNeighbor->getMilitary()
		<< "," << rightNeighbor->getMilitary() << ")" << endl;
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
		while (!(cin >> choice)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input.  Try again: \n";
		}
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
				if (alreadyPlayed(m_hand.at(choice)->m_name))
				{
					continueLoop = true;
					cout << "Sorry, you can't play the same card twice" << endl;
				}
				else {
					if (canBuyWithNeighbor(m_hand.at(choice)) == -1)
					{
						continueLoop = true;
						cout << "You can't buy this card, try another one" << endl;;
					}
				}
				
			}
		}
		
	}
	while (continueLoop);

	m_cardToPlay = m_hand.at(choice);
}