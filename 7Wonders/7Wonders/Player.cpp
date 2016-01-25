#include "Player.h"
#include "RedCard.h"
#include "YellowCard.h"
#include "BrownCard.h"
#include "GreenCard.h"
#include <string>
#include "DefaultMarvel.h"


Player::Player(CardSet* discard, int rec) : m_discard(discard), money(3), military(0), m_hand(), m_board(),
m_cardToPlay(nullptr), marvel(new DefaultMarvel())
{
	if (rec >= RESOURCES_COUNT)
	{
		throw "Error in Player constructor, int resource chosen out of bound";
	}
	std::array<int, RESOURCES_COUNT> resources = { 0, 0, 0, 0, 0, 0, 0 };
	resources.at(rec)++;
	switch (rec)
	{
	case 0:
		resourcesDisplay += "b ";
		break;
	case 1:
		resourcesDisplay += "p ";
		break;
	case 2:
		resourcesDisplay += "a ";
		break;
	case 3:
		resourcesDisplay += "m ";
		break;
	case 4:
		resourcesDisplay += "q ";
		break;
	case 5:
		resourcesDisplay += "g ";
		break;
	case 6:
		resourcesDisplay += "t ";
		break;
	default:
		break;
	}
	m_resources.push_back(resources);
}

Player::~Player()
{
}

unsigned int Player::getMoney() const
{
	return money;
}

unsigned int Player::getGuildScore() const
{
	return guildScore;
}

char Player::getScienceGuild() const
{
	return scienceGuild;
}

unsigned int Player::getMilitary() const
{
	return military;
}

unsigned int Player::getMilitaryMalus() const
{
	return militaryMalus;
}

Marvel* Player::getMarvel()
{
	return marvel;
}

unsigned int Player::getGeneratedScore() const
{
	return generatedScore;
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

bool Player::alreadyPlayed(string s)
{
	for (unsigned int i = 0; i < m_board.size(); i++)
	{
		if (m_board.at(i)->m_name == s)
		{
			return true;
		}
	}
	return false;
}

const CardSet& Player::getHand() const
{
	return m_hand;
}

CardSet Player::getPlayableCards()
{
	CardSet cards;
	for (unsigned int i = 0; i < m_hand.size(); i++)
	{
		if (canBuyWithNeighbor(m_hand.at(i)) >= 0)
		{
			cards.push_back(m_hand.at(i));
		}
	}
	return cards;
}

void Player::resetResources()
{
	m_resources.clear();
	std::array<int, RESOURCES_COUNT> resources = { 0, 0, 0, 0, 0, 0, 0 };
	m_resources.push_back(resources);
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
	for (unsigned int j = 0; j < rec.size(); j++)
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

int Player::countColor(int color)
{
	int resul = 0;
	for (unsigned int i = 0; i < m_board.size(); i++)
	{
		if (m_board.at(i)->m_color == color)
		{
			resul++;
		}
	}
	return resul;
}

int Player::tradeCountColor(int color)
{
	int resul = 0;
	for (unsigned int i = 0; i < m_board.size(); i++)
	{
		if (m_board.at(i)->m_color == color)
		{
			resul++;
		}
	}

	for (unsigned int i = 0; i < leftNeighbor->m_board.size(); i++)
	{
		if (leftNeighbor->m_board.at(i)->m_color == color)
		{
			resul++;
		}
	}

	for (unsigned int i = 0; i < rightNeighbor->m_board.size(); i++)
	{
		if (rightNeighbor->m_board.at(i)->m_color == color)
		{
			resul++;
		}
	}
	return resul;
}

void Player::applyEndingEffects(Card* c)
{
	if (c->m_color == VIOLET)
	{
		int res = 0;
		switch (c->m_production.at(0))
		{
		case 'a':
			res = leftNeighbor->countColor(BROWN) + rightNeighbor->countColor(BROWN);
			guildScore += res;
			break;
		case 'b':
			res = leftNeighbor->countColor(GRAY) + rightNeighbor->countColor(GRAY);
			guildScore += 2 * res;
			break;
		case 'c':
			res = leftNeighbor->countColor(YELLOW) + rightNeighbor->countColor(YELLOW);
			guildScore += res;
			break;
		case 'd':
			res = leftNeighbor->countColor(GREEN) + rightNeighbor->countColor(GREEN);
			guildScore += res;
			break;
		case 'e':
			res = leftNeighbor->countColor(RED) + rightNeighbor->countColor(RED);
			guildScore += res;
			break;
		case 'f':
			res = leftNeighbor->getMilitaryMalus() + rightNeighbor->getMilitaryMalus();
			guildScore += res;
			break;
		case 'g':
			res = countColor(BROWN) + countColor(GRAY) + countColor(VIOLET);
			guildScore += res;
			break;
		case 'h':
			//Ajouter toutes les combinaisons puis garder la meilleure
			scientistGuildTreatment();
			break;
		case 'i':
			res = leftNeighbor->countColor(BLUE) + rightNeighbor->countColor(BLUE);
			guildScore += res;
			break;
		case 'j':
			res = leftNeighbor->getMarvel()->getMarvelLevel()
				+ rightNeighbor->getMarvel()->getMarvelLevel()
				+ getMarvel()->getMarvelLevel();
			guildScore += res;
			break;
		default:
			break;
		}
	}
	if (c->m_color == YELLOW)
	{
		string s = ((YellowCard*)c)->getProduction();
		if (s.length() == 1)
		{
			std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 1, 1, 1 };
			std::array<int, RESOURCES_COUNT> rec2 = { 1, 1, 1, 1, 0, 0, 0 };
			int res = 0;
			switch (s.at(0))
			{
			case 'p':
				res = countColor(BROWN);
				generatedScore += res;
				break;
			case 'q':
				res = countColor(YELLOW);
				generatedScore += res;
				break;
			case 'r':
				res = 2 * countColor(GRAY);
				generatedScore += res;
				break;
			case 'a':
				res = marvel->getMarvelLevel();
				generatedScore += res;
				break;
			default:
				break;
			}
		}
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
			resourcesDisplay += (s + " ");
		}
		else {
			if (s.at(1) == '/')
			{
				//Cas choix ressources
				rec.at(identifyResource(s.at(0))) += 1;
				rec.at(identifyResource(s.at(2))) += 1;
				AddResourceWithChoice(rec);
				resourcesDisplay += (s + " ");
				return;
			}
			else {
				//Cas classique 2 ressources
				rec.at(identifyResource(s.at(0))) += 1;
				rec.at(identifyResource(s.at(1))) += 1;
				AddResource(rec);
				resourcesDisplay += (s + " ");
			}
		}
	}
	else if (c->m_color == GRAY)
	{
		std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 0, 0, 0 };
		rec.at(identifyResource(c->m_production.at(0))) += 1;
		resourcesDisplay += (c->m_production + " ");
		AddResource(rec);
		
	}
	else if (c->m_color == RED)
	{
		military += c->getPower();
	}
	else if (c->m_color == YELLOW)
	{
		string s = ((YellowCard*)c)->getProduction();
		if (s.length() == 1)
		{
			std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 1, 1, 1 };
			std::array<int, RESOURCES_COUNT> rec2 = { 1, 1, 1, 1, 0, 0, 0 };
			int res = 0;
			switch (s.at(0))
			{
			case 'g':
				//Trade ÅEgauche
				comptoir2 = true;
				break;
			case 'd':
				//Trade ÅEdroite
				comptoir1 = true;
				break;
			case 'm':
				//Trade des 2 cÙtÈs
				market = 1;
				break;
			case 't':
				money += 5;
				break;
			case 'f':
				AddResourceWithChoice(rec);
				resourcesDisplay += (s + " ");
				break;
			case 'c':
				AddResourceWithChoice(rec2);
				resourcesDisplay += (s + " ");
				break;
			case 'v':
				money += tradeCountColor(BROWN);
				break;
			case 'b':
				money += 2 * tradeCountColor(GRAY);
				break;
			case 'p':
				res = countColor(BROWN);
				money += res;
				//generatedScore += res;
				break;
			case 'q':
				res = countColor(YELLOW);
				money += res;
				//generatedScore += res;
				break;
			case 'r':
				res = 2*countColor(GRAY);
				money += res;
				//generatedScore += res;
				break;
			case 'a':
				res = marvel->getMarvelLevel();
				money += 3*res;
				//generatedScore += res;
				break;
			default:
				break;
			}
		}
	}
}

void Player::scientistGuildTreatment()
{
	int v1 = computeScienceScore(0);
	int v2 = computeScienceScore(1);
	int v3 = computeScienceScore(2);
	char cc = '-';
	int value = std::max(std::max(v1, v2),v3);
	if (value == v1)
	{
		scienceGuild = 'c';
	}
	if (value == v2)
	{
		scienceGuild = 'g';
	}
	if (value == v3)
	{
		scienceGuild = 't';
	}
}

bool Player::canBuy(Card* c)
{
	if (defausse)
	{
		return true;
	}
	if (alreadyPlayed(c->m_name))
	{
		return false;
	}
	//Free card
	for (int i = 0; i < m_board.size(); i++)
	{
		if (m_board.at(i)->m_name == c->buyForFreeIf)
		{
			c->m_price = 0;
			return true;
		}
	}
	if (c->m_price > money)
	{
		return false;
	}
	for (unsigned int j = 0; j < m_resources.size(); j++)
	{
		for (unsigned int i = 0; i < RESOURCES_COUNT; i++)
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

unsigned int Player::computeScienceScore(int value) const
{
	unsigned int compass = 0, gear = 0, tablet = 0;
	if (value == 0)
	{
		compass++;
	}
	else if (value == 1)
	{
		gear++;
	}
	else {
		tablet++;
	}
	for (unsigned int i = 0; i < m_board.size(); i++)
	{
		const GreenCard& card = (GreenCard&)(*m_board[i]);
		if (card.m_color == GREEN)
		{
			if (card.getType() == 'c')
				compass++;
			if (card.getType() == 'g')
				gear++;
			if (card.getType() == 't')
				tablet++;
		}
	}
	unsigned int res = compass*compass + gear*gear + tablet*tablet + 7 * std::min(compass, std::min(gear, tablet));
	return res;
}

int Player::canBuyWithNeighbor(Card* c)
{
	if (alreadyPlayed(c->m_name))
	{
		return -1;
	}
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
	for (unsigned int j = 0; j < m_resources.size(); j++)
	{
		std::array<int, RESOURCES_COUNT> toBuyarray = { 0, 0, 0, 0, 0, 0, 0 };
		bool found = false;
		for (unsigned int i = 0; i < RESOURCES_COUNT; i++)
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
		for (unsigned int i = 0; i < ToBuy.size(); i++)
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
	for (unsigned int i = 0; i < 4; i++)
	{
		if (resource.at(i) != 0)
		{
			resul += (2 * resource.at(i) - plus);
		}
	}

	for (unsigned int i = 4; i < resource.size(); i++)
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
	for (unsigned int i = 0; i < 4; i++)
	{
		if (resource.at(i) != 0)
		{
			resul += (2 * resource.at(i) - plus);
		}
	}

	for (unsigned int i = 4; i < resource.size(); i++)
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
	for (unsigned int i = 0; i < m_resources.size(); i++)
	{
		for (unsigned int j = 0; j < resource.size(); j++)
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
	for (int i = 0; i < m_board.size(); i++)
	{
		if (m_board.at(i)->m_name == c->buyForFreeIf)
		{
			return true;
		}
	}
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
		for (unsigned int j = 0; j < m_resources.size(); j++)
		{
			std::array<int, RESOURCES_COUNT> toBuyarray = { 0, 0, 0, 0, 0, 0, 0 };
			bool found = false;
			for (unsigned int i = 0; i < RESOURCES_COUNT; i++)
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
		//Les ÈlÈments sont trouvÈs
		for (unsigned int i = 0; i < ToBuy.size(); i++)
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
							if (money - count2 < 0)
							{
								int s = 0;
								return true;
							}
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
		//Fin de la mÈthode auxiliaire
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
			std::cerr << "Attention : un joueur ne possËde aucune carte en main au debut du tour." << std::endl;
			throw("Un joueur ne possËde aucune carte en main");
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
		throw("Pas de carte ÅEjouer sÈlectionnÈe");
	}

	if (m_hand.size() <= 1)
	{
		throw("Taille de la main non conforme");
	}
	if (defausse && MarvelTreatment)
	{
		defausse = false;
		MarvelTreatment = false;
		marvel->upgrade(m_resources);
		money += marvel->getMarvelMoney();
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
	for (unsigned int i = 0; i < m_resources.size(); i++)
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
		for (unsigned int i = 0; i < RESOURCES_COUNT; i++)
		{
			if (resource.at(i) > 0)
			{
				vector<array<int, RESOURCES_COUNT>> temp(tempResource);
				for (unsigned int j = 0; j < temp.size(); j++)
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

