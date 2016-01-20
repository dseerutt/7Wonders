#include <iostream>
#include "World.h"
#include "MCTSImplementation.h"
#include "test_mcts_two_players.hpp"
#include "test_two_players_game.hpp"

int main(int argc, char** argv)
{
	/*if (argc != 2)
	{
		std::cerr << "Erreur : 1 argument attendu, " << (argc - 1) << " donné(s)." << std::endl;
		exit(-1);
	}
	int n = atoi(argv[1]);
	if (n < 3 || n > 7)
	{
		std::cerr << "Erreur : le nombre de joueur doit être compris entre 3 et 7" << std::endl;
		exit(-1);
	}*/

	unsigned int nh = 1;// nb de joueurs humains
	unsigned int nc = 4;// nb de joueurs ordinateurs
	World world(nh, nc);

	//world.run();

	game::run_test_two_players_game(game::MCTSImplementation(&world));
	//mcts::run_test_mcts_two_players(game::MCTSImplementation(&world));


	getchar();
	getchar();

	return 0;
}

//$(SolutionDir)$(Configuration)\

