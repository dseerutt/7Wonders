#include "Player.h"
#include "RedCard.h"
#include "YellowCard.h"
#include <string>


Player::Player(CardSet* discard) : m_discard(discard),money(3), military(0), m_hand(), m_board(), m_cardToPlay(nullptr)
{
	std::array<int, RESOURCES_COUNT> resources = { 0, 0, 0, 0, 0, 0, 0 };
	m_resources.push_back(resources);
}

Player::~Player()
{
}

unsigned int Player::getMoney() const
{
	return money;
}

unsigned int Player::getMilitary() const
{
	return military;
}

unsigned int Player::getScore() const
{
	unsigned int score = 0;
	for (unsigned int i = 0; i < m_board.size(); i++)
	{
		score += m_board.at(i)->getPoints();
	}
	return score;
}

const CardSet& Player::getBoard() const
{
	return m_board;
}

void Player::setHand(const CardSet& newHand)
{
	m_hand.clear();
	for (unsigned int i = 0; i < newHand.size(); i++)
	{
		m_hand.push_back(newHand.at(i));
	}
}

const CardSet& Player::getHand() const
{
	return m_hand;
}

const CardSet Player::getPlayableCards() const
{
	CardSet cards = m_hand;
	return cards;
}


string Player::displayResourceManager(string me)
{
	if (me == "You")
	{
		return displayResource(me, m_resources);
	} else
		if (me == "Left Neighbor")
		{
			return displayResource(me, leftNeighbor->getResources());
		}
		else
		{
			return displayResource(me, rightNeighbor->getResources());
		}
}

string Player::displayResource(string txt, std::vector<std::array<int, RESOURCES_COUNT>> rec)
{
	string resul = "";
	for (int j = 0; j < rec.size(); j++)
	{
		if (j != 0)
		{
			resul += "\n";
		}
		resul += txt + " can have: ";
		for (int i = 0; i < RESOURCES_COUNT; i++)
		{
			if (rec.at(j).at(i) != 0)
			{
				resul += std::to_string(rec.at(j).at(i)) + " " + displayResourceType(i) + " ";
			}
		}
		if (resul == txt + " can have: ")
		{
			return "No resource for " + txt;
		}
	}
	return resul;
}

string Player::displayResourceType(int i)
{
	switch (i)
	{
	case 0:
		return "Wood";
		break;
	case 1:
		return "Stone";
		break;
	case 2:
		return "Clay";
		break;
	case 3:
		return "Mineral";
		break;
	case 4:
		return "Papyrus";
		break;
	case 5:
		return "Glass";
		break;
	case 6:
		return "Textile";
		break;
	default:
		throw "error";
	}
}


int Player::identifyResource(char c)
{
	switch (c)
	{
	case('b') :
		return WOOD;
		break;
	case('p') :
		return STONE;
		break;
	case('a') :
		return BRICK;
		break;
	case('m') :
		return MINERAL;
		break;
	case('t') :
		return TEXTILE;
		break;
	case('v') :
		return GLASS;
		break;
	case('q') :
		return PAPYRUS;
		break;
	default:
		throw "char not found in identifyResource";
	}
}

void Player::applyEffects(Card* c)
{
	std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 0, 0, 0 };
	if (c->m_color == BROWN)
	{
		string s = ((BrownCard*)c)->getProduction();
		if (s.length() == 1)
		{
			rec.at(identifyResource(s.at(0))) += 1;
			AddResource(rec);
		}
		else {
			if (s.at(1) == '/')
			{
				//Cas choix ressources
				rec.at(identifyResource(s.at(0))) += 1;
				rec.at(identifyResource(s.at(2))) += 1;
				AddResourceWithChoice(rec);
				return;
			}
			else {
				//Cas classique 2 ressources
				rec.at(identifyResource(s.at(0))) += 1;
				rec.at(identifyResource(s.at(1))) += 1;
				AddResource(rec);
			}
		}
	}
	else if (c->m_color == GRAY)
	{
		std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 0, 0, 0 };
		rec.at(identifyResource(c->m_production.at(0))) += 1;
		AddResource(rec);
		
	}
	else if (c->m_color == RED)
	{
		military += c->getPower();
	}
	else if (c->m_color == BLUE)
	{
		//Pas de traitement en cours de jeu
	}
	else if (c->m_color == GREEN)
	{
		//Pas de traitement en cours de jeu
	}
	else if (c->m_color == YELLOW)
	{
		string s = ((YellowCard*)c)->getProduction();
		if (s.length() == 1)
		{
			if (s.at(0) == 'g')
			{
				//Trade à gauche
				comptoir2 = true;
			} else
				if (s.at(0) == 'd')
				{
				//Trade à droite
				comptoir1 = true;
				}
				else
					if (s.at(0) == 'm')
					{
				//Trade des 2 côtés
				market = 1;
					}
					else {
						money += 5;
					}
		}
	}
}


bool Player::canBuy(Card* c)
{
	if (c->m_price > money)
	{
		return false;
	}
	for (int j = 0; j < m_resources.size(); j++)
	{
		for (int i = 0; i < RESOURCES_COUNT; i++)
		{
			if (c->m_Cost[i] > m_resources.at(j).at(i))
			{
				break;
			}
			else if (i == RESOURCES_COUNT - 1)
			{
				return true;
			}
		}
	}
	return false;
}

int Player::canBuyWithNeighbor(Card* c)
{
	int virtualMoney = money;
	if (canBuy(c))
	{
		return 0;
	}

	if (c->m_price > money)
	{
		return -1;
		//Si retourne -1, ne peut pas acheter
	}
	virtualMoney -= c->m_price;
	
	std::vector<std::array<int, RESOURCES_COUNT>> ToBuy;
	for (int j = 0; j < m_resources.size(); j++)
	{
		std::array<int, RESOURCES_COUNT> toBuyarray = { 0, 0, 0, 0, 0, 0, 0 };
		bool found = false;
		for (int i = 0; i < RESOURCES_COUNT; i++)
		{
			if (c->m_Cost[i] > m_resources.at(j).at(i))
			{
				toBuyarray.at(i) = c->m_Cost[i] - m_resources.at(j).at(i);
				found = true;
			}
			if (found && (i == RESOURCES_COUNT - 1))
			{
				ToBuy.push_back(toBuyarray);
			}
		}
	}
	if (!ToBuy.empty())
	{
		for (int i = 0; i < ToBuy.size(); i++)
		{
			if (leftNeighbor->canProvide(ToBuy.at(i)))
			{
				int count = countResourcesL(ToBuy.at(i));
				if (virtualMoney - count < 0)
				{
					return -1;
				}
				else {
					return count;
				}
			}

			if (rightNeighbor->canProvide(ToBuy.at(i)))
			{
				int count = countResourcesR(ToBuy.at(i));
				if (virtualMoney - count < 0)
				{
					return -1;
				}
				else {
					return count;
				}
			}
		}
		return -1;
	}
	else {
		return -1;
	}
}


int Player::countResourcesL(array<int, RESOURCES_COUNT> resource)
{
	int plus = 0;
	if (comptoir1)
	{
		plus = 1;
	}
	int plus2 = 0;
	if (market)
	{
		plus2 = 1;
	}

	int resul = 0;
	for (int i = 0; i < 4; i++)
	{
		if (resource.at(i) != 0)
		{
			resul += (2 * resource.at(i) - plus);
		}
	}

	for (int i = 4; i < resource.size(); i++)
	{
		if (resource.at(i) != 0)
		{
			resul += (2 * resource.at(i) - plus2);
		}
	}
	return resul;
}

int Player::countResourcesR(array<int, RESOURCES_COUNT> resource)
{
	int plus = 0;
	if (comptoir2)
	{
		plus = 1;
	}
	int plus2 = 0;
	if (market)
	{
		plus2 = 1;
	}

	int resul = 0;
	for (int i = 0; i < 4; i++)
	{
		if (resource.at(i) != 0)
		{
			resul += (2 * resource.at(i) - plus);
		}
	}

	for (int i = 4; i < resource.size(); i++)
	{
		if (resource.at(i) != 0)
		{
			resul += (2 * resource.at(i) - plus2);
		}
	}
	return resul;
}

bool Player::canProvide(array<int, RESOURCES_COUNT> resource)
{
	for (int i = 0; i < m_resources.size(); i++)
	{
		for (int j = 0; j < resource.size(); j++)
		{
			if (m_resources.at(i).at(j) < resource.at(j))
			{
				break;
			}
			else if (j == RESOURCES_COUNT - 1)
			{
				return true;
			}
		}
	}
	return false;
}

bool Player::Buy(Card* c)
{
	if (canBuy(c))
	{
		money -= c->m_price;
		return true;
	}
	else if (canBuyWithNeighbor(c))
	{
		//petites modifications du corps de canBuyWithNeighbor
		money -= c->m_price;

		std::vector<std::array<int, RESOURCES_COUNT>> ToBuy;
		for (int j = 0; j < m_resources.size(); j++)
		{
			std::array<int, RESOURCES_COUNT> toBuyarray = { 0, 0, 0, 0, 0, 0, 0 };
			bool found = false;
			for (int i = 0; i < RESOURCES_COUNT; i++)
			{
				if (c->m_Cost[i] > m_resources.at(j).at(i))
				{
					toBuyarray.at(i) = c->m_Cost[i] - m_resources.at(j).at(i);
					found = true;
				}
				if (found && (i == RESOURCES_COUNT - 1))
				{
					ToBuy.push_back(toBuyarray);
				}
			}
		}
		//Les éléments sont trouvés
			for (int i = 0; i < ToBuy.size(); i++)
			{
				if ((leftNeighbor->canProvide(ToBuy.at(i))) ||
					(rightNeighbor->canProvide(ToBuy.at(i))))
				{
					int count = countResourcesL(ToBuy.at(i));
					int count2 = countResourcesR(ToBuy.at(i));
					if ((leftNeighbor->canProvide(ToBuy.at(i))) &&
						(rightNeighbor->canProvide(ToBuy.at(i))))
					{
						int count = countResourcesL(ToBuy.at(i));
						int count2 = countResourcesR(ToBuy.at(i));
						if (count2 > count)
						{
							rightNeighbor->money += count2;
							money -= count2;
							return true;
						}
						else {
							leftNeighbor->money += count;
							money -= count;
							return true;
						}
					}
					if (leftNeighbor->canProvide(ToBuy.at(i)))
					{
						int count = countResourcesL(ToBuy.at(i));
						leftNeighbor->money += count;
						money -= count;
						return true;
					}
					else {
						int count2 = countResourcesR(ToBuy.at(i));
						rightNeighbor->money += count2;
						money -= count2;
						return true;
					}
				}
			}
			return false;
		//Fin de la méthode auxiliaire
	}
	else {
		return false;
	}
}

void Player::prepareTurn()
{
	if (m_hand.size() <= 1)
	{
		if (m_hand.size() == 0)
		{
			std::cerr << "Attention : un joueur ne possède aucune carte en main au debut du tour." << std::endl;
			throw("Un joueur ne possède aucune carte en main");
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
	if (m_cardToPlay == 0)
	{
		throw("Pas de carte à jouer sélectionnée");
	}

	if (m_hand.size() <= 1)
	{
		throw("Taille de la main non conforme");
	}
	if (defausse)
	{
		defausse = false;
		money += 3;
	}
	else {
		Buy(m_cardToPlay);
		m_board.push_back(m_cardToPlay);
		applyEffects(m_cardToPlay);
	}
	

	CardSet::iterator cardToErase;
	for (auto it = m_hand.begin(); it != m_hand.end(); ++it)
	{
		Card* card = *it;
		if (card == m_cardToPlay)
		{
			cardToErase = it;
			break;
		}
	}
	m_hand.erase(cardToErase);
}

void Player::AddResource(array<int, RESOURCES_COUNT> resource)
{
		for (int i = 0 ; i < m_resources.size() ; i++)
		{
			for (int j = 0; j < RESOURCES_COUNT; j++)
			{
			m_resources.at(i).at(j) += resource.at(j);
			}
		}
}
void Player::AddResourceWithChoice(array<int, RESOURCES_COUNT> resource)
{
		vector<array<int, RESOURCES_COUNT>> tempResource(m_resources);
		m_resources.clear();
		for (int i = 0; i < RESOURCES_COUNT; i++)
		{
			if (resource.at(i) > 0)
			{
				vector<array<int, RESOURCES_COUNT>> temp(tempResource);
				for (int j = 0; j < temp.size(); j++)
				{
					temp.at(j).at(i) += resource.at(i);
					m_resources.push_back(temp.at(j));
				}
			}
		}
}

std::vector<std::array<int, RESOURCES_COUNT>> Player::getResources() {
	return m_resources;
}

