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
public:
	Display(const std::vector<Player*>& players);
	~Display();

	void run();
	void draw();

protected:
	void drawPlayer(const Player& p);
	void drawBoard(const CardSet& board, sf::Vector2f pos);
	void drawCard(const Card& c, sf::Vector2f pos);
};

