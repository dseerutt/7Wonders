#include "MCTSImplementation.h"

#define set(bitboard, col, row) (bitboard |= (1LL << (((col) << 3) + (row))))

namespace game
{
	static std::vector<std::vector<uint64_t>> create_hash_values()
	{
		std::default_random_engine generator;
		std::uniform_int_distribution<uint64_t> distribution;
		std::vector<std::vector<uint64_t>> res(7, std::vector<uint64_t>(6, 0));
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				res[i][j] = distribution(generator);
			}
		}
		return res;
	}

	std::vector<std::vector<uint64_t>> MCTSImplementation::cross_hash_values = create_hash_values();
	std::vector<std::vector<uint64_t>> MCTSImplementation::circle_hash_values = create_hash_values();

	MCTSImplementation::MCTSImplementation() : game()
	{
		state.world = new World(1, 2);
		/*Card Picture Testing
		world->startAge();
		world->m_display.test(world->m_deck);
		world->startAge();
		world->m_display.test(world->m_deck);
		world->startAge();
		world->m_display.test(world->m_deck);
		getchar();*/
	}
	MCTSImplementation::MCTSImplementation(World* w) : game()
	{
		state.world = w;
	}


	MCTSImplementation::~MCTSImplementation()
	{
	}

	void MCTSImplementation::set_state(const GameState& s)
	{
		state = s;
		state.world->m_players.clear();
		for (HumanPlayer h : state.hp)
		{
			state.world->m_players.push_back(&h);
		}
		for (ComputerPlayer c : state.cp)
		{
			state.world->m_players.push_back(&c);
		}
		for (int i = 0; i < state.marvels.size(); i++)
		{
			state.world->m_players.at(i)->marvel = &state.marvels.at(i);
		}
	}

	/*void MCTSImplementation::playout(std::mt19937& engine, int max_depth)
	{
	while (!end_of_game())
	{
	std::uniform_int_distribution<uint16_t> distribution(0, number_of_moves() - 1);
	uint16_t move = distribution(engine);
	play(move);
	}
	}*/

	bool MCTSImplementation::end_of_game() const
	{
		//return state.first_player_win || state.second_player_win || state.total_moves == 42;
		return state.world->gameOver();
	}

	bool MCTSImplementation::won(uint8_t player) const
	{
		if (player == 0)
		{
			return state.world->hasWon(*state.world->m_players.at(0));
		}
		else
		{
			for (unsigned int i = 1; i < state.world->m_players.size(); i++)
			{
				if (state.world->hasWon(*state.world->m_players.at(i)))
					return true;
			}
			return false;
		}
	}

	bool MCTSImplementation::lost(uint8_t player) const
	{
		return !won(player);
	}

	bool MCTSImplementation::draw(uint8_t player) const
	{
		return state.world->draw();
	}

	uint8_t MCTSImplementation::current_player() const
	{
		return state.current_player;
	}

	int MCTSImplementation::value(uint8_t player) const
	{
		if (draw(player))
		{
			return 0;
		}
		else if (won(player))
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}

	uint16_t MCTSImplementation::number_of_moves() const
	{
		uint16_t res;
		uint8_t player = current_player();
		if (player == 0)
		{
			res = numberOfMoves(0);
		}
		else
		{
			unsigned int n = 1;
			for (unsigned int i = 1; i < state.world->m_players.size(); i++)
			{
				n *= numberOfMoves(i);
			}
			res = n;
		}
		return res;
	}

	std::set<int> MCTSImplementation::to_input_vector() const
	{
		std::set<int> res;
		return res;
	}

	void MCTSImplementation::from_input_vector(const std::set<int>& input)
	{
	}

	void MCTSImplementation::play(uint16_t m)
	{
		if (state.world->m_players.at(0)->getHand().size() == 0)
		{
			state.world->startAge();
		}

		uint8_t p = current_player();
		Player& pl = *state.world->m_players[0];
		std::cout << pl.m_hand.size() << " ; ";
		if (pl.m_hand.size() > 100)
		{
			state.world->m_gameOver = true;
			state.current_player = 1 - state.current_player;
			return;
		}
		if (p == 0)
		{
			if (m > 500) m = 0;
			playerMove(0, m);
		}
		else
		{
			player2Move(m);

			state.world->endTurn();
		}

		state.current_player = 1 - state.current_player;
	}

	void MCTSImplementation::playerMove(int i, uint16_t m)
	{
		Player& p = *state.world->m_players.at(i);
		CardSet hand = p.getHand();
		CardSet playableHand = p.getPlayableCards();
		unsigned int nbMoves = 0;

		nbMoves += playableHand.size();
		nbMoves += hand.size();
		if (p.getMarvel()->canUpgrade(p.getResources()))
		{
			nbMoves += hand.size();
		}

		if (m < playableHand.size())
		{
			p.playCard(hand.at(m), false, false);
		}
		else if (m < playableHand.size() + hand.size())
		{
			p.playCard(hand.at(m - playableHand.size()), true, false);
		}
		else
		{
			p.playCard(hand.at(m - playableHand.size() - hand.size()), true, true);
		}
	}

	void MCTSImplementation::player2Move(uint16_t m)
	{
		/*for (unsigned int i = 1; i < state.world->m_players.size(); i++)
		{
			uint16_t move = 0;
			playerMove(i, move);
		}*/
		unsigned int nbMoves = numberOfMoves(1);
		uint16_t move_p2 = m % nbMoves;
		uint16_t move_p3 = m / nbMoves;
		playerMove(1, move_p2);
		playerMove(2, move_p3);
	}

	std::uint64_t MCTSImplementation::hash() const
	{
		return 0;// state.hash_value;
	}

	std::uint64_t MCTSImplementation::hash(std::uint16_t m) const
	{
		/*uint8_t position = ((state.moves   (m * 3)) & 7);
		uint8_t p = position * 3;
		uint8_t f = (state.free >> p) & 7;
		return state.hash_value ^ (current_player() == CIRCLE ? circle_hash_values[position][f] : cross_hash_values[position][f]);*/
		return 0;
	}

	GameState MCTSImplementation::get_state()
	{
		state.hp.clear();
		state.cp.clear();
		state.hp.push_back(*((HumanPlayer*)state.world->m_players.at(0)));
		for (unsigned int i = 1; i < state.world->m_players.size(); i++)
		{
			state.cp.push_back(*((ComputerPlayer*)state.world->m_players.at(i)));
		}
		state.marvels.clear();
		for (int i = 0; i < state.world->m_players.size(); i++)
		{
			state.marvels.push_back(*(DefaultMarvel*) state.world->m_players.at(i)->marvel);
		}
		return state;
	}

	std::shared_ptr<game<GameState>> MCTSImplementation::do_copy() const
	{
		return std::shared_ptr<MCTSImplementation>(new MCTSImplementation(*this));
	}

	std::string MCTSImplementation::to_string() const
	{
		return "[TOSTRING]";
	}

	std::string MCTSImplementation::to_string_before() const
	{
		unsigned int nbPlays = 0;
		unsigned int nbDiscard = 0;
		unsigned int nbWonder = 0;
		Player& p = *state.world->m_players.at(0);
		nbPlays = p.getPlayableCards().size();
		nbDiscard = p.getHand().size();
		if (p.getMarvel()->canUpgrade(p.getResources()))
		{
			nbWonder = p.getHand().size();
		}

		std::string res = "";

		if (nbPlays == 0)
			res += "Moves []";
		else
			res += "Moves [0-" + std::to_string(nbPlays - 1) + "]";
		res += " [" + std::to_string(nbPlays) + "-" + std::to_string(nbPlays + nbDiscard - 1) + "]";
		if (nbWonder == 0)
			res += " []";
		else
			res += " [" + std::to_string(nbPlays + nbDiscard) + "-" + std::to_string(nbPlays + nbDiscard + nbWonder - 1) + "]";
		return res;
	}

	std::string MCTSImplementation::to_string_after() const
	{
		std::string res = "";
		res += "Age " + std::to_string(state.world->m_age);
		res += ", board : " + std::to_string(state.world->m_players.at(0)->getBoard().size());

		return res;
	}

	void MCTSImplementation::displayResults() const
	{
		state.world->displayScores();
#ifndef TESTING
		state.world->getDisplay().drawScores(state.world->m_scores);
#endif // !TESTING
	}

	void MCTSImplementation::display() const
	{
		state.world->getDisplay().draw();
	}

	std::string MCTSImplementation::player_to_string(uint8_t player) const
	{
		//return player == CROSS ? "X" : (player == CIRCLE ? "O" : " ");
		if (player == 0)
			return "Human Player";
		else
			return "Computer Player";
	}

	std::string MCTSImplementation::move_to_string(uint16_t m) const
	{
		/*uint8_t position = ((state.moves >> (m * 3)) & 7);
		return std::to_string(position);*/
		return std::to_string(m);
	}

	unsigned int MCTSImplementation::numberOfMoves(unsigned int player) const
	{
		unsigned int nbMoves = 0;
		Player& p = *state.world->m_players.at(player);
		nbMoves = 0;
		nbMoves += p.getPlayableCards().size();
		nbMoves += p.getHand().size();
		if (p.getMarvel()->canUpgrade(p.getResources()))
		{
			nbMoves += p.getHand().size();
		}

		return nbMoves;
	}

	std::ostream& operator<<(std::ostream& os, const MCTSImplementation& c4)
	{
		os << c4.to_string() << std::endl;
		return os;
	}
}
