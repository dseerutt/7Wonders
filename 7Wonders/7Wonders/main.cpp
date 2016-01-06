#include <iostream>
#include "World.h"

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

	world.run();

	getchar();
	getchar();

	return 0;
}

//$(SolutionDir)$(Configuration)\

