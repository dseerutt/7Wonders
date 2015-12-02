#include "World.h"


World::World()
{
}


World::~World()
{
}

void World::run()
{
	const int NUMBER_OF_AGES = 3;

	for (int i = 0; i < NUMBER_OF_AGES; i++)
	{
		generateDeck(i, playerNumber);
		// ...
	}
}

void World::generateDeck(int age, int playerNumber)
{

}

void World::prepareTurn()
{

}

void World::playTurn()
{

}

