#pragma once
#include <vector>
#include <array>
#include "CardSet.h"
#include "Marvel.h"

using namespace std;

class Player
{
protected:
	char scienceGuild = 'n';
	Marvel* marvel;
	CardSet m_hand;
	CardSet m_board;
	CardSet* m_discard;
	bool comptoir1 = false;
	bool comptoir2 = false;
	bool market = false;
	int generatedScore = 0;
	int guildScore = 0;
	int money;
	int military;
	std::vector<std::array<int, RESOURCES_COUNT> > m_resources;
public:
	Card* m_cardToPlay;
	bool defausse = false;
	bool MarvelTreatment = false;

public:
	void play(Card* card, bool discard, bool marvelTreatment);
	
	std::string resourcesDisplay = "";
	int militaryMalus = 0;
	int militaryBonus = 0;
	Player(CardSet* discard, int rec);
	~Player();
	Marvel* getMarvel()const;
	unsigned int computeScienceScore(int value) const;
	int tradeCountColor(int color);
	int countColor(int color);
	std::vector<std::array<int, RESOURCES_COUNT>> getResources();
	bool alreadyPlayed(string s);
	Player* leftNeighbor;
	Player* rightNeighbor;
	void scientistGuildTreatment();
	string displayResourceManager(string me);
	string displayResource(string me, std::vector<std::array<int, RESOURCES_COUNT>>);
	static string displayResourceType(int i);
	void resetResources();

	unsigned int getMilitary() const;
	char getScienceGuild() const;
	unsigned int getMilitaryMalus() const;
	unsigned int getMilitaryBonus() const;
	unsigned int getGeneratedScore() const;
	unsigned int getScore() const;
	unsigned int getMoney() const;
	unsigned int getGuildScore() const;
	const CardSet& getBoard() const;
	const CardSet& getHand() const;
	static int identifyResource(char c);
	bool canBuy(Card* c);
	bool Buy(Card* c);
	void applyEffects(Card* c);
	void applyEndingEffects(Card* c);
	int canBuyWithNeighbor(Card* c);
	bool canProvide(array<int, RESOURCES_COUNT> resource);
	int countResourcesL(array<int, RESOURCES_COUNT> resource);
	int countResourcesR(array<int, RESOURCES_COUNT> resource);
	void setHand(const CardSet& newHand);
	void prepareTurn();
	void playTurn();
	void AddResource(array<int, RESOURCES_COUNT> resource);
	void AddResourceWithChoice(array<int, RESOURCES_COUNT> resource);
	CardSet getPlayableCards();
protected:
	virtual void pickCard() = 0;
};

