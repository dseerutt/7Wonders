#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Card.h"

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600

class Display
{
protected:
	sf::RenderWindow m_window;
	const std::vector<Player*>& m_players;
	int age = 0;
	string RelativePath = "Pictures/";

public:
	Display(const std::vector<Player*>& players);
	~Display();

	void setAge(int age0);
	void run();
	void draw();
	void drawHands();
	void drawScores(std::vector<std::vector<int> > m_scores);
	void init();



protected:
	void testMaximumCapacity(const Player& p0, const Player& p1, const Player& p2);
	void drawStatistics(const Player& p0, const Player& p1, const Player& p2);
	void writeText(string text, sf::Vector2f position, int size);
	void writeTextBlack(string text, sf::Vector2f position, int size);
	void drawSprite(string path, int wherex, int wherey);
	void drawSprite(string path, sf::Vector2f size, int wherex, int wherey);
	void drawSpriteWithScale(string path, sf::Vector2f size, sf::Vector2f scale, int wherex, int wherey);
	void drawCardSprite(string path, sf::Vector2f pos, int wherex, int wherey);
	void drawMiniCardSprite(string path, sf::Vector2f pos, int wherex, int wherey);
	void drawBackground();
	void drawPlayer(const Player& p);
	void drawPlayerDemo(const Player& p, const Player& p1, const Player& p2);
	void drawOldBoard(const CardSet& board, sf::Vector2f pos);
	void drawBoards(const Player& p0, const Player& p1, const Player& p2);
	void drawBoard1(const CardSet& board);
	void drawBoard2(const CardSet& board);
	void drawBoard3(const CardSet& board);
	void drawHand(const Player& p);
	void drawCard(const Card& c, sf::Vector2f pos);
	const static string miniPath;
	const static string cardPath;
};

