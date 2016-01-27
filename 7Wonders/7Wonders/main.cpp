#include <iostream>
#include "test_game.h"
#include "test_mcts_two_players.hpp"
#include "MCTSImplementation.h"

int main(int argc, char** argv)
{

	unsigned int nh = 1;// nb de joueurs humains
	unsigned int nc = 2;// nb de joueurs ordinateurs
	World world(nh, nc);

	world.run();
	//game::test_game();
	//mcts::run_test_mcts_two_players(game::MCTSImplementation(&world));

	getchar();
	getchar();

	return 0;
}

