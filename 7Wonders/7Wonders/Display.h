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

protected:
	void testMaximumCapacity();
	void drawSprite(string path, int wherex, int wherey);
	void drawSprite(string path, sf::Vector2f size, int wherex, int wherey);
	void drawSpriteWithScale(string path, sf::Vector2f size, sf::Vector2f scale, int wherex, int wherey);
	void drawBackground();
	void drawPlayer(const Player& p);
	void drawPlayerDemo(const Player& p, const Player& p1, const Player& p2);
	void drawBoard(const CardSet& board, sf::Vector2f pos);
	void drawHand(const Player& p);
	void drawCard(const Card& c, sf::Vector2f pos);
};

