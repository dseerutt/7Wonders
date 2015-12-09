#include "CardSet.h"
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


CardSet::CardSet()
{
}


CardSet::~CardSet()
{
}

void CardSet::shuffle()
{
	unsigned int seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(begin(), end(), std::default_random_engine(seed));
}
