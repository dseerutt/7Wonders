#pragma once
class World
{
private:
	int playerNumber;

public:
	World();
	~World();

	void run();
	void generateDeck(int age, int playerNumber);
	void prepareTurn();
	void playTurn();
};

